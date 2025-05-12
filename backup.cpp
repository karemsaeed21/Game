#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#define STB_IMAGE_IMPLEMENTATION
#include "./dependencies/library/stb_image.h"
#include "./Characters/cat.h"
#include "./Characters/amoungus.h"
#include "./Characters/enemy.h"
#include <list>

struct Projectile
{
    float x;             // Current position X coordinate
    float y;             // Current position Y coordinate
    float direction;     // Direction of movement (1.0f for right, -1.0f for left)
    bool active;         // Whether the projectile is currently active in the game
    float verticalSpeed; // Speed of vertical movement (for downward shots)
};

enum GameState
{
    START_SCREEN,   // Initial screen when game starts
    GAME_RUNNING,   // Main gameplay state
    PAUSED,         // Game is paused
    GAME_OVER,      // Player has lost
    LEVEL_COMPLETE, // Current level is finished
    GAME_WON        // Player has completed all levels
};

// =============== Game Level and Progress ===============
int level = 1;                      // Current game level
int maxLevel = 5;                   // Maximum number of levels
int score = 0;                      // Player's current score
GameState gameState = START_SCREEN; // Current state of the game

// =============== Enemy System ===============
std::list<Enemy> enemies;                      // Container for all active enemies
int enemiesPerLevel[] = {0, 2, 5, 10, 15, 20}; // Number of enemies per level
int enemiesKilled = 0;                         // Counter for killed enemies
int totalEnemiesInLevel = 0;                   // Total enemies in current level
const float enemyGroundY = -0.5f;              // Ground level for enemy
const float COLLISION_RADIUS = 0.2f;           // Collision radius for enemies and projectiles to check for collisions by using the Pythagorean theorem and the distance formula between two points 

// =============== Projectile System ===============
std::list<Projectile> projectiles;    // Container for all active projectiles
const float PROJECTILE_SPEED = 0.05f; // Speed of projectiles
bool canFire = true;                  // Whether player can fire
const int FIRE_COOLDOWN = 500;        // Cooldown between shots (milliseconds)

// =============== Character Movement ===============
float velocityY = 0.0f;           // Vertical velocity for jumping
bool isJumping = false;           // Whether character is jumping
const float gravity = -0.01f;     // Gravity force
const float jumpStrength = 0.15f; // Jump force
// const float MOVEMENT_SPEED = 0.3f; // Base movement speed
float lastFrameTime = 0.0f; // Time tracking for movement ******

// =============== Character Position ===============
const float characterGroundY = -0.5f; // Ground level for character This is a constant that defines the Y-coordinate where the character stands
float translateY = characterGroundY;  // Current Y position Tracks the character's current vertical position Initially set to ground level Changes when character jumps
float currentX = -0.8f;               // Current X position Tracks the character's current horizontal position  Used in: drawCharacter() to position character horizontally updateMovement() to update position Collision detection with enemies Projectile spawning position
float targetX = -0.5f;                // Target X position Defines the target position for character movement Used during character transitions Used in: updateAnimation() for smooth movement Character switching animations Movement calculations
float outgoingX = -0.5f;              //******   // Position for character transition Tracks the position of the outgoing character during transitions Used when switching between characters Used in: drawTransition() for transition animations updateAnimation() for smooth exit animations Character switching logic

// =============== Character State ===============
int characterHealth[] = {2, 5}; // Health for each character
int currentCharacter = 1;       // Currently active character
int nextCharacter = 2;          // Next character to switch to
bool isTransitioning = false;   // Whether character is transitioning
bool isOutgoingDone = false;    // Whether outgoing animation is done
bool isCharacterDead = false;   // Whether character is dead
int lastAliveCharacter = 0;     // Last character that was alive

// =============== Graphics ===============
GLuint backgroundTexture; // Background texture handle convert it to int ****

GLuint loadTexture(const char *filename) // This function loads an image file and creates an OpenGL texture from it. It returns a GLuint representing the texture ID. If it fails at any point, it returns 0.
{
    int width, height, channels; // These variables store the width, height, and number of channels (color channels) in the image.
    // the function converts the image file (like PNG, JPG, etc.) into raw pixel data (i.e. an array of pixel color values), and then sends that pixel data to OpenGL as a texture.
    unsigned char *data = stbi_load(filename, &width, &height, &channels, 0); // Points to the raw pixel data loaded into memory. This function is from the stb_image library. It loads the image file specified by filename.
    if (!data)
    {
        printf("Failed to load image: %s\n", filename);
        return 0; // Return 0 instead of exiting
    } // If the image can't be loaded, print an error and return 0 (indicating failure).

    GLuint textureID;             // GLuint is an unsigned integer type that is used to store the texture ID. textureID is a variable that will store the unique identifier for the texture that OpenGL will use to refer to it.
    glGenTextures(1, &textureID); // Generates a new texture ID. Requests OpenGL to generate one texture object and store its ID in textureID.
    if (textureID == 0)
    {
        stbi_image_free(data);
        printf("Failed to generate texture\n");
        return 0;
    } // If the texture ID can't be generated, print an error and return 0 (indicating failure).

    glBindTexture(GL_TEXTURE_2D, textureID); // Binds the texture to the texture ID. This means that the texture will be associated with the texture ID.

    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB; // if the image has 4 channels (RGBA), use GL_RGBA, otherwise use GL_RGB.

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data); // Specifies the texture image. This function sets up the texture's data and format.

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // **** Specifies the texture minification filter. This function sets the minification filter for the texture.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // **** Specifies the texture magnification filter. This function sets the magnification filter for the texture.

    stbi_image_free(data); // Frees the memory allocated for the image data.
    return textureID;
}

void drawBackground()
{
    glEnable(GL_TEXTURE_2D); // Enable texture mapping for the background Those lines create a rectangle (quad) and map an image (texture) onto it, so the shape can display the image on the screen.
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);

    glBegin(GL_QUADS);        // Draws a quadrilateral (rectangle) to cover the entire screen.
    glTexCoord2f(0, 1);       // Coordinates for the bottom-left corner of the texture
    glVertex2f(-1.0f, -1.0f); // Bottom-left vertex of the quad
    glTexCoord2f(1, 1);       // Coordinates for the bottom-right corner of the texture
    glVertex2f(1.0f, -1.0f);  // Bottom-right vertex of the quad
    glTexCoord2f(1, 0);       // Coordinates for the top-right corner of the texture
    glVertex2f(1.0f, 1.0f);   // Top-right vertex of the quad
    glTexCoord2f(0, 0);       // Coordinates for the top-left corner of the texture
    glVertex2f(-1.0f, 1.0f);  // Top-left vertex of the quad
    glEnd();

    glDisable(GL_TEXTURE_2D); // Disable texture mapping after drawing the background
}

void drawText(const char *text)
{
    void *font = GLUT_BITMAP_HELVETICA_18;

    int textPixelWidth = 0;
    for (const char *c = text; *c; ++c)
        textPixelWidth += glutBitmapWidth(font, *c);
    int textPixelHeight = 18;

    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    float textWidth = (float)textPixelWidth / windowWidth * 2.0f;
    float textHeight = (float)textPixelHeight / windowHeight * 2.0f;

    float paddingX = 0.03f;
    float paddingY = 0.02f;
    float boxWidth = textWidth + 2 * paddingX;
    float boxHeight = textHeight + 2 * paddingY;

    float boxX = -boxWidth / 2.0f;
    float boxY = -boxHeight / 2.0f;

    glColor4f(1.0f, 1.0f, 1.0f, 0.85f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_QUADS);
    glVertex2f(boxX, boxY);
    glVertex2f(boxX + boxWidth, boxY);
    glVertex2f(boxX + boxWidth, boxY + boxHeight);
    glVertex2f(boxX, boxY + boxHeight);
    glEnd();
    glDisable(GL_BLEND);

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(boxX, boxY);
    glVertex2f(boxX + boxWidth, boxY);
    glVertex2f(boxX + boxWidth, boxY + boxHeight);
    glVertex2f(boxX, boxY + boxHeight);
    glEnd();

    float textX = -textWidth / 2.0f;
    float textY = -textHeight / 3.0f;
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(textX, textY);
    while (*text)
        glutBitmapCharacter(font, *text++);
}

void drawTransparentBox(float x, float y, float width, float height) // Draws a transparent box at the specified position and size
{
    glEnable(GL_BLEND); // Enable blending for transparency
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);         // Sets the color of the box to black with full transparency
    glBegin(GL_QUADS);                         // Draws a quadrilateral (rectangle) of that transparent box
    glVertex2f(x - width / 4, y - height / 2); // Bottom-left vertex of the quad
    glVertex2f(x + width / 4, y - height / 2); // Bottom-right vertex of the quad
    glVertex2f(x + width / 4, y + height / 2); // Top-right vertex of the quad
    glVertex2f(x - width / 4, y + height / 2); // Top-left vertex of the quad
    glEnd();

    glDisable(GL_BLEND); // Disable blending after drawing the box
}

void drawCharacter()
{
    glPushMatrix();
    glScalef(0.25f, 0.25f, 1.0f);                           // Scales the character to 25% of its original size
    glTranslatef(currentX * 4.0f, translateY * 4.0f, 0.0f); // we multiply by 4.0f to scale the character to the correct size because we scaled it down by 4 times

    if (currentCharacter == 1) // Draws the character based on the current character
        drawCat();
    else if (currentCharacter == 2)
        DrawCharacter();

    // Draw character collision box with same size as enemy
    drawTransparentBox(0, 0, 1.0f, 1.0f); // Draws the transparent box at the current position

    glPopMatrix();
}

void drawEnemies()
{
    for (const auto &enemy : enemies)
    {
        if (!enemy.isActive)
            continue; // If the enemy is not active, skip the rest of the code

        glPushMatrix();
        glScalef(0.25f, 0.25f, 1.0f);                       // Scales the enemy to 25% of its original size
        glTranslatef(enemy.x * 4.0f, enemy.y * 4.0f, 0.0f); // we multiply by 4.0f to scale the enemy to the correct size because we scaled it down by 4 times
        glRotatef(enemy.rotation, 0.0f, 0.0f, 1.0f);        // Rotates the enemy around the z-axis

        // Draw enemy health bar
        float healthBarWidth = 0.2f;   // Width of the health bar
        float healthBarHeight = 0.02f; // Height of the health bar
        float healthBarY = 0.3f;       // Position above enemy

        // Draw background (gray)
        glColor3f(0.5f, 0.5f, 0.5f);                                   // Sets the color of the health bar to gray
        glBegin(GL_QUADS);                                             // Draws a quadrilateral (rectangle) of the health bar
        glVertex2f(-healthBarWidth / 2, healthBarY);                   // Bottom-left vertex of the quad
        glVertex2f(healthBarWidth / 2, healthBarY);                    // Bottom-right vertex of the quad
        glVertex2f(healthBarWidth / 2, healthBarY + healthBarHeight);  // Top-right vertex of the quad
        glVertex2f(-healthBarWidth / 2, healthBarY + healthBarHeight); // Top-left vertex of the quad
        glEnd();

        // Draw health (green)
        float healthPercentage = enemy.health / 2.0f;                                                        // Since max health is 2
        glColor3f(0.0f, 1.0f, 0.0f);                                                                         // Sets the color of the health bar to green
        glBegin(GL_QUADS);                                                                                   // Draws a quadrilateral (rectangle) of the health bar
        glVertex2f(-healthBarWidth / 2, healthBarY);                                                         // Bottom-left vertex of the quad
        glVertex2f(-healthBarWidth / 2 + (healthBarWidth * healthPercentage), healthBarY);                   // Bottom-right vertex of the quad
        glVertex2f(-healthBarWidth / 2 + (healthBarWidth * healthPercentage), healthBarY + healthBarHeight); // Top-right vertex of the quad
        glVertex2f(-healthBarWidth / 2, healthBarY + healthBarHeight);                                       // Top-left vertex of the quad
        glEnd();

        drawCreeper();                        // Draws the enemy
        drawTransparentBox(0, 0, 1.0f, 1.0f); // Draws the transparent box at the current position
        glPopMatrix();
    }
}

void spawnEnemies(int count)
{
    enemies.clear();                       // Clears the list of enemies because we are spawning new enemies for the next level
    enemiesKilled = 0;                     // Resets the counter for killed enemies
    totalEnemiesInLevel = count;           // Sets the total number of enemies in the current level
    srand(static_cast<unsigned>(time(0))); // Seeds the random number generator with the current time

    for (int i = 0; i < count; ++i)
    {
        float x = 1.0f + static_cast<float>(rand() % 100) / 50.0f;       // Generates a random x position for the enemy The formula 1.0f + static_cast<float>(rand() % 100) / 50.0f generates a value between 1.0 and 3.0. The expression rand() % 100 generates a random integer between 0 and 99. Dividing by 50.0f and adding 1.0f maps the result to the range of 1.0 to 3.0,
        float speed = 0.01f + static_cast<float>(rand() % 10) / 1000.0f; // Generates a random speed for the enemy The formula 0.01f + static_cast<float>(rand() % 10) / 1000.0f generates a value between 0.01 and 0.02. The expression rand() % 10 generates a random integer between 0 and 9. Dividing by 1000.0f and adding 0.01f maps the result to the range of 0.01 to 0.02.
        enemies.push_back(Enemy(x, enemyGroundY, speed));                // Adds the enemy to the list of enemies
    }
}

void drawHealthBar()
{
    float healthBarWidth = 0.5f;                        // Width of the health bar
    float healthBarHeight = 0.05f;                      // Height of the health bar
    float healthX = -0.75f;                             // X position of the health bar
    float healthY = 0.9f;                               // Y position of the health bar
    int health = characterHealth[currentCharacter - 1]; // Gets the health of the current character

    glPushMatrix();
    glTranslatef(healthX, healthY, 0.0f); // Translates the health bar to the specified position top left corner

    if (health > 2)                  // Change the color of the health bar based on the health of the character
        glColor3f(0.0f, 1.0f, 0.0f); // Green
    else if (health > 1)
        glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    else
        glColor3f(1.0f, 0.0f, 0.0f); // Red

    // Draw the health bar (rounded rectangle)
    glBegin(GL_QUADS);
    glVertex2f(-healthBarWidth / 2.0f, -healthBarHeight / 2.0f); // Bottom-left vertex of the quad
    glVertex2f(healthBarWidth / 2.0f, -healthBarHeight / 2.0f);  // Bottom-right vertex of the quad
    glVertex2f(healthBarWidth / 2.0f, healthBarHeight / 2.0f);   // Top-right vertex of the quad
    glVertex2f(-healthBarWidth / 2.0f, healthBarHeight / 2.0f);  // Top-left vertex of the quad
    glEnd();

    glPopMatrix();
}

void drawfire()
{
    for (const auto &projectile : projectiles)
    {
        if (!projectile.active)
            continue; // If the projectile is not active, skip the rest of the code

        glPushMatrix();
        glScalef(0.25f, 0.25f, 1.0f); // Apply same scale as character
        glTranslatef(projectile.x * 4.0f, projectile.y * 4.0f, 0.0f); // Translates the projectile to the specified position

        // Draw the fire projectile
        glColor3f(1.0f, 1.0f, 0.0f); // Yellow color for fire
        glBegin(GL_QUADS);
        glVertex2f(-0.02f, -0.02f); // Bottom-left vertex of the quad
        glVertex2f(0.02f, -0.02f);  // Bottom-right vertex of the quad
        glVertex2f(0.02f, 0.02f);   // Top-right vertex of the quad
        glVertex2f(-0.02f, 0.02f); // Top-left vertex of the quad
        glEnd();

        // Draw transparent collision box around fire
        drawTransparentBox(0, 0, 0.2f, 0.2f); // Smaller box for projectile

        glPopMatrix();
    }
}

bool checkCollision(float x1, float y1, float x2, float y2, float radius1, float radius2)
{
    float dx = x1 - x2; // Calculates the difference in x coordinates between the two objects
    float dy = y1 - y2; // Calculates the difference in y coordinates between the two objects
    float distance = std::sqrt(dx * dx + dy * dy); // Calculates the distance between the two objects using the Pythagorean theorem
    return distance < (radius1 + radius2);         // Returns true if the distance is less than the sum of the radii, indicating a collision
}

void updatefire(int value)
{
    if (gameState != GAME_RUNNING)
        return; // If the game is not running, skip the rest of the code

    float fixedSpeed = 0.05f; // Fixed speed of the projectile
    bool needsUpdate = false; // If the projectile needs to be updated

    projectiles.remove_if([](const Projectile &p) { return !p.active; }); // Removes inactive projectiles from the list using a lambda function 

    for (auto &projectile : projectiles)
    {
        if (!projectile.active)
            continue; // If the projectile is not active, skip the rest of the code

        projectile.x += (fixedSpeed * projectile.direction); // Updates the x position of the projectile  // Update horizontal position

        if (projectile.verticalSpeed != 0.0f) // Update vertical position if projectile has vertical speed
        {
            projectile.y += projectile.verticalSpeed; // No gravity for downward shots - they move in a straight line
        }

        if (projectile.x > 4.0f || projectile.x < -4.0f || projectile.y < -5.0f)
        {
            projectile.active = false; // Set the projectile to inactive
            needsUpdate = true;         // Update the projectile
            continue;                   // Skip the rest of the code
        } // If the projectile goes off screen, set it to inactive and update the projectile

        for (auto &enemy : enemies)
        {
            if (enemy.isActive && !enemy.isFalling)
            {
                if (checkCollision(projectile.x, projectile.y, enemy.x, enemy.y, COLLISION_RADIUS * 0.5f, COLLISION_RADIUS))
                {
                    projectile.active = false;
                    if (currentCharacter == 1) // Different damage based on character
                    {
                        enemy.health = 0; // First character (low health) - one shot kill
                    }
                    else
                    {
                        enemy.health--; // Second character (high health) - two shots needed
                    }

                    if (enemy.health <= 0)
                    {
                        enemy.isFalling = true; // Set the enemy to fall
                        enemy.speed = 0.0f;     // Set the speed of the enemy to 0
                        enemiesKilled++;        // Increment the number of enemies killed
                        score += 100;           // Increment the score

                        if (enemiesKilled == totalEnemiesInLevel) // If the number of enemies killed is equal to the total number of enemies in the level
                        {
                            if (level < maxLevel)
                            {
                                gameState = LEVEL_COMPLETE; // Set the game state to level complete
                                glutPostRedisplay();        // Refresh the screen
                            }
                            else
                            {
                                gameState = GAME_WON;
                                score += 1000;
                                glutPostRedisplay();
                            }
                        }
                    }
                    needsUpdate = true; // Update the projectile
                    break;
                }
            }
        }
    }

    if (needsUpdate)
    {
        glutPostRedisplay(); // Refresh the screen for the projectile 
    }

    if (!projectiles.empty())
    {
        glutTimerFunc(16, updatefire, 0);
    } // If the projectile needs to be updated, refresh the screen 
}

void updateAnimation(int value)
{
    if (!isTransitioning)
        return;

    float speed = 0.08f;         // Slightly faster than original 0.05f
    float exitPosition = -1.5f;  // Closer exit position
    float enterPosition = -1.5f; // Start from left side, closer
    float finalPosition = -0.8f; // Final resting position

    if (!isOutgoingDone)
    {
        // Move first character to the left (exit) smoothly
        outgoingX -= speed;
        if (outgoingX < exitPosition)
        {
            isOutgoingDone = true;
            currentCharacter = nextCharacter;
            currentX = enterPosition;      // Start new character from left side
            translateY = characterGroundY; // Maintain ground level
        }
    }
    else
    {
        // Move new character from left to final position smoothly
        currentX += speed;
        if (currentX >= finalPosition)
        {
            currentX = finalPosition;
            isTransitioning = false;
            translateY = characterGroundY; // Maintain ground level
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateAnimation, 0);
}

void handleCharacterDeath()
{
    // If current character dies, switch to the other one immediately
    if (currentCharacter == 1 && characterHealth[0] <= 0)
    {
        if (characterHealth[1] > 0) // Only switch if character 2 is alive
        {
            nextCharacter = 2;
            isTransitioning = true;
            isOutgoingDone = false;
            outgoingX = currentX;
            lastAliveCharacter = 2;
            glutTimerFunc(0, updateAnimation, 0);
            return; // Exit immediately after starting transition
        }
    }
    else if (currentCharacter == 2 && characterHealth[1] <= 0)
    {
        if (characterHealth[0] > 0) // Only switch if character 1 is alive
        {
            nextCharacter = 1;
            isTransitioning = true;
            isOutgoingDone = false;
            outgoingX = currentX;
            lastAliveCharacter = 1;
            glutTimerFunc(0, updateAnimation, 0);
            return; // Exit immediately after starting transition
        }
    }

    // Only set game over if both characters are actually dead
    if (characterHealth[0] <= 0 && characterHealth[1] <= 0)
    {
        gameState = GAME_OVER;
    }
}

void updateEnemies(int value) // Update updateEnemies collision check
{
    if (gameState != GAME_RUNNING)
        return;

    bool needsUpdate = false;

    for (auto &enemy : enemies)
    {
        if (!enemy.isActive)
            continue;

        if (enemy.isFalling)
        {
            enemy.rotationSpeed = std::max(0.0f, enemy.rotationSpeed - 0.8f);
            enemy.rotation += enemy.rotationSpeed;
            enemy.y -= 0.05f; // Reduced from 0.2f to 0.05f for slower falling
            if (enemy.y < -5.0f)
            {
                enemy.isActive = false;
            }
        }
        else
        {
            enemy.x -= enemy.speed;

            if (enemy.x < currentX - 0.5f && !enemy.hasPassed)
            {
                enemy.hasPassed = true;
                float newX = 1.0f + static_cast<float>(rand() % 100) / 50.0f;
                float newSpeed = 0.01f + static_cast<float>(rand() % 10) / 1000.0f;
                enemies.push_back(Enemy(newX, enemyGroundY, newSpeed));
            }

            if (!isTransitioning && characterHealth[currentCharacter - 1] > 0) // Only check collision if not transitioning and character is alive
            {
                if (std::abs(enemy.x - currentX) < 0.2f && std::abs(enemy.y - translateY) < 0.1f)
                {
                    characterHealth[currentCharacter - 1] = std::max(0, characterHealth[currentCharacter - 1] - 1);
                    enemy.isFalling = true;
                    enemy.speed = 0.0f;
                    enemy.rotationSpeed = 50.0f; // Reset rotation speed when starting to fall
                    enemiesKilled++;

                    if (characterHealth[currentCharacter - 1] <= 0) // If current character dies, handle the switch immediately
                    {
                        handleCharacterDeath();
                    }

                    if (enemiesKilled >= totalEnemiesInLevel && characterHealth[0] > 0 && characterHealth[1] > 0) // Check level completion separately from character death
                    {
                        if (level < maxLevel)
                        {
                            gameState = LEVEL_COMPLETE;
                            score += 500;
                            glutPostRedisplay();
                        }
                        else
                        {
                            gameState = GAME_WON;
                            score += 1000;
                            glutPostRedisplay();
                        }
                    }
                    needsUpdate = true;
                }
            }
        }
        needsUpdate = true;
    }

    enemies.erase( std::remove_if(enemies.begin(), enemies.end(), [](const Enemy &e) { return !e.isActive; }), enemies.end());
    if (needsUpdate)
    {
        glutPostRedisplay();
    }

    if (gameState == GAME_RUNNING)
    {
        glutTimerFunc(30, updateEnemies, 0);
    }
}

void updateJump()
{
    if (!isJumping)
        return;

    velocityY += gravity;
    translateY += velocityY;
    if (translateY <= characterGroundY) // Use character ground level
    {
        translateY = characterGroundY;
        velocityY = 0.0f;
        isJumping = false;
    }

    else
    {
        glutTimerFunc(16, [](int)
                      { updateJump(); }, 0); // Continue jump update
    }

    glutPostRedisplay();
}

void updateMovement(float deltaTime)
{
    if (gameState != GAME_RUNNING || isTransitioning)
        return;

    // Update character position based on delta time
    if (currentX < -1.0f)
        currentX = -1.0f;
    if (currentX > 1.0f)
        currentX = 1.0f; 
} // if the character arrived to the end or start of the screen go back again to the condition limits

void drawTransition()
{
    if (isTransitioning && !isOutgoingDone)
    {
        // Draw outgoing character
        glPushMatrix();
        glScalef(0.25f, 0.25f, 1.0f);                            // Scales the character to 25% of its original size
        glTranslatef(outgoingX * 4.0f, translateY * 4.0f, 0.0f); // Translates the character to the specified position
        if (currentCharacter == 1)                               // Draws the character based on the current character
            drawCat();
        else if (currentCharacter == 2) // Draws the character based on the current character
            DrawCharacter();
        glPopMatrix();
    }

    if (isTransitioning && isOutgoingDone)
    {
        // Draw incoming character
        glPushMatrix();
        glScalef(0.25f, 0.25f, 1.0f);                           // Scales the character to 25% of its original size
        glTranslatef(currentX * 4.0f, translateY * 4.0f, 0.0f); // Translates the character to the specified position
        if (currentCharacter == 1)                              // Draws the character based on the current character
            drawCat();
        else if (currentCharacter == 2) // Draws the character based on the current character
            DrawCharacter();
        glPopMatrix();
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'e':
        if (gameState == START_SCREEN)
        {
            gameState = GAME_RUNNING;
            spawnEnemies(enemiesPerLevel[level]);
            glutTimerFunc(30, updateEnemies, 0);
            glutPostRedisplay();
        }
        break;
    case 'r':
        if (gameState == GAME_OVER || gameState == GAME_WON)
        {
            gameState = START_SCREEN;
            currentX = -0.8f;
            translateY = characterGroundY;
            currentCharacter = 1;
            level = 1;
            score = 0;
            enemies.clear();
            characterHealth[0] = 2;
            characterHealth[1] = 5;
            targetX = -0.8f;
            outgoingX = -0.8f;
            isTransitioning = false;
            isOutgoingDone = false;
            projectiles.clear();
            canFire = true; // Reset firing cooldown
            glutPostRedisplay();
        }
        break;

    case 'n':
        if (gameState == GAME_RUNNING && level < maxLevel)
        {
            level++;
            spawnEnemies(enemiesPerLevel[level]);
        }
        break;
    case '1':
    case '2':
        if (gameState == GAME_RUNNING && !isTransitioning)
        {
            int selected = key - '0';
            // Only switch if the selected character is alive and different from current
            if (currentCharacter != selected && characterHealth[selected - 1] > 0)
            {
                nextCharacter = selected;
                isTransitioning = true;
                isOutgoingDone = false;
                outgoingX = currentX;
                lastAliveCharacter = selected;
                glutTimerFunc(0, updateAnimation, 0);
            }
        }
        break;
    case 'a':
    case 'A':
        if (gameState == GAME_RUNNING && !isTransitioning)
            currentX -= 0.15f;
        break;
    case 'd':
    case 'D':
        if (gameState == GAME_RUNNING && !isTransitioning)
            currentX += 0.15f;
        break;
    case ' ':
    case 'w':
        if (gameState == GAME_RUNNING && !isJumping)
        {
            isJumping = true;
            velocityY = jumpStrength;
            glutTimerFunc(16, [](int)
                          { updateJump(); }, 0);
        }
        break;
    case 'p':
    case 'P':
        if (gameState == GAME_RUNNING)
        {
            gameState = PAUSED;
        }
        else if (gameState == PAUSED)
        {
            gameState = GAME_RUNNING;
            glutTimerFunc(30, updateEnemies, 0);
        }
        glutPostRedisplay();
        break;

    case 'u':
    case 'U':
        if (gameState == GAME_RUNNING && canFire)
        {
            Projectile newProjectile;
            newProjectile.x = currentX;
            newProjectile.y = translateY;
            newProjectile.direction = 1.0f;
            newProjectile.verticalSpeed = isJumping ? -0.05f : 0.0f; // Negative value for downward movement
            newProjectile.active = true;
            projectiles.push_back(newProjectile);

            canFire = false;
            glutTimerFunc(FIRE_COOLDOWN, [](int)
                          { canFire = true; }, 0);

            if (projectiles.size() == 1)
            {
                glutTimerFunc(16, updatefire, 0);
            }
        }
        break;

    case 'k':
    case 'K':
        if (gameState == LEVEL_COMPLETE)
        {
            level++;
            gameState = GAME_RUNNING;
            enemies.clear();
            enemiesKilled = 0;
            projectiles.clear(); // Clear any remaining projectiles
            spawnEnemies(enemiesPerLevel[level]);
            glutTimerFunc(30, updateEnemies, 0);
            glutPostRedisplay();
        }
        break;

    case 27:
        exit(0);
    }
}

void display()
{
    // Calculate delta time
    float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    float deltaTime = currentTime - lastFrameTime;
    lastFrameTime = currentTime;

    // Update movement
    updateMovement(deltaTime);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    drawBackground();
    glDisable(GL_TEXTURE_2D);
    glPushAttrib(GL_CURRENT_BIT);

    switch (gameState)
    {
    case START_SCREEN:
        drawText("Press 'e' to Start the Game");
        break;
    case GAME_RUNNING:
        drawTransition();
        if (!isTransitioning)
            drawCharacter();
        drawEnemies();
        drawHealthBar();
        drawfire();

        // Draw score and level info
        char scoreText[100];
        snprintf(scoreText, sizeof(scoreText), "Level: %d  Enemies: %d/%d  Score: %d",
                 level, enemiesKilled, totalEnemiesInLevel, score);
        glColor3f(0.0f, 0.0f, 0.0f);
        glRasterPos2f(-0.9f, 0.9f);
        for (const char *c = scoreText; *c; c++)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }
        break;
    case PAUSED:
        drawText("Game Paused Press 'p' to Resume");
        break;
    case GAME_OVER:
        snprintf(scoreText, sizeof(scoreText), "Game Over! Final Score: %d Press 'r' to Restart or 'Esc' to Quit", score);
        drawText(scoreText);
        break;
    case LEVEL_COMPLETE:
        drawCharacter();
        char levelText[100];
        snprintf(levelText, sizeof(levelText), "Level %d Complete! Score: %d Press 'k' to continue", level, score);
        drawText(levelText);
        break;
    case GAME_WON:
        snprintf(scoreText, sizeof(scoreText), "Congratulations! Final Score: %d Press 'r' to Restart or 'Esc' to Quit", score);
        drawText(scoreText);
        break;
    }
    glPopAttrib();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(2000, 2000); // Use 2000 if you want ultra-HD
    glutCreateWindow("OpenGL Character Game");

    backgroundTexture = loadTexture("2_21.png"); // Load background texture

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
