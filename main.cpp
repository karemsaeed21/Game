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
#include <algorithm>

bool canFire = true;
const int FIRE_COOLDOWN = 500; // Cooldown in milliseconds (0.5 seconds)
// Add after other global variables
struct Projectile
{
    float x; // Current position
    float y;
    float direction; // Direction of movement (1.0f for right)
    bool active;
    float verticalSpeed; // Added for vertical movement
};

std::list<Projectile> projectiles;
const float PROJECTILE_SPEED = 0.05f;

enum GameState
{
    START_SCREEN,
    GAME_RUNNING,
    PAUSED,
    GAME_OVER,
    LEVEL_COMPLETE,
    GAME_WON // Add this new state
};
GameState gameState = START_SCREEN;
float velocityY = 0.0f;
bool isJumping = false;
const float gravity = -0.01f;         // Reduced gravity
const float jumpStrength = 0.15f;     // Increased jump height
const float characterGroundY = -0.5f; // Ground level for character
const float enemyGroundY = -0.5f;     // Ground level for enemy (0.1 lower)
float translateY = characterGroundY;  // Start character at its ground level
float currentX = -0.8f;               // Move character more to the right

int characterHealth[] = {2, 5};

// Positions
float targetX = -0.5f;   // Match currentX
float outgoingX = -0.5f; // Match currentX

// States
int currentCharacter = 1;
int nextCharacter = 1;
bool isTransitioning = false;
bool isOutgoingDone = false;

GLuint backgroundTexture;

int score = 0;

std::vector<Enemy> enemies;
int level = 1;
int maxLevel = 5;

int enemiesPerLevel[] = {0, 2, 5, 10, 15, 20};

// Add after other global variables
int enemiesKilled = 0;       // Counter for killed enemies
int totalEnemiesInLevel = 0; // Total enemies in current level

// Add after other global variables
float lastFrameTime = 0.0f;
const float MOVEMENT_SPEED = 0.3f; // Base movement speed

// Add after other global variables
const float COLLISION_RADIUS = 0.2f; // Collision radius for characters and enemies

// Add these global variables at the top with other globals
bool isCharacterDead = false;
int lastAliveCharacter = 0;

GLuint loadTexture(const char *filename)
{
    int width, height, channels;
    unsigned char *data = stbi_load(filename, &width, &height, &channels, 0);
    if (!data)
    {
        printf("Failed to load image: %s\n", filename);
        return 0; // Return 0 instead of exiting
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    if (textureID == 0)
    {
        stbi_image_free(data);
        printf("Failed to generate texture\n");
        return 0;
    }

    glBindTexture(GL_TEXTURE_2D, textureID);

    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    return textureID;
}

// Add after other function declarations, before the implementation functions
void updateAnimation(int value); // Add this forward declaration

// Add after other forward declarations
void updateEnemies(int value);
void updateAnimation(int value);

// Add this helper function to draw transparent boxes
void drawTransparentBox(float x, float y, float width, float height)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(0.0f, 0.0f, 0.0f, 0.0f); // Red with 30% opacity
    glBegin(GL_QUADS);
    glVertex2f(x - width / 2, y - height / 2);
    glVertex2f(x + width / 2, y - height / 2);
    glVertex2f(x + width / 2, y + height / 2);
    glVertex2f(x - width / 2, y + height / 2);
    glEnd();

    glDisable(GL_BLEND);
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

// Update spawnEnemies function to match character scale
void spawnEnemies(int count)
{
    enemies.clear();
    enemiesKilled = 0;
    totalEnemiesInLevel = count;
    srand(static_cast<unsigned>(time(0)));

    for (int i = 0; i < count; ++i)
    {
        float x = 1.0f + static_cast<float>(rand() % 100) / 50.0f;
        float speed = 0.01f + static_cast<float>(rand() % 10) / 1000.0f;
        enemies.push_back(Enemy(x, enemyGroundY, speed));
    }
}

// Update drawEnemies function for parallel positioning
void drawEnemies()
{
    for (const auto &enemy : enemies)
    {
        if (!enemy.isActive)
            continue;

        glPushMatrix();
        glScalef(0.25f, 0.25f, 1.0f);
        glTranslatef(enemy.x * 4.0f, enemy.y * 4.0f, 0.0f);
        glRotatef(enemy.rotation, 0.0f, 0.0f, 1.0f);

        // Draw enemy health bar
        float healthBarWidth = 0.2f;
        float healthBarHeight = 0.02f;
        float healthBarY = 0.3f; // Position above enemy

        // Draw background (gray)
        glColor3f(0.5f, 0.5f, 0.5f);
        glBegin(GL_QUADS);
        glVertex2f(-healthBarWidth / 2, healthBarY);
        glVertex2f(healthBarWidth / 2, healthBarY);
        glVertex2f(healthBarWidth / 2, healthBarY + healthBarHeight);
        glVertex2f(-healthBarWidth / 2, healthBarY + healthBarHeight);
        glEnd();

        // Draw health (green)
        float healthPercentage = enemy.health / 2.0f; // Since max health is 2
        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(-healthBarWidth / 2, healthBarY);
        glVertex2f(-healthBarWidth / 2 + (healthBarWidth * healthPercentage), healthBarY);
        glVertex2f(-healthBarWidth / 2 + (healthBarWidth * healthPercentage), healthBarY + healthBarHeight);
        glVertex2f(-healthBarWidth / 2, healthBarY + healthBarHeight);
        glEnd();

        // Draw enemy
        drawCreeper();

        // Draw enemy collision box with same size as character
        drawTransparentBox(0, 0, 1.0f, 1.0f);

        glPopMatrix();
    }
}

// Update collision detection for parallel positioning
bool checkCharacterEnemyCollision(float charX, float charY, float enemyX, float enemyY)
{
    float dx = (charX * 4.0f) - (enemyX * 4.0f);
    float dy = (charY * 4.0f) - (enemyY * 4.0f);
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance < 0.5f;
}

// Update updateEnemies collision check
void updateEnemies(int value)
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
            // Gradually decrease rotation speed very slowly
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

            // Only check collision if not transitioning and character is alive
            if (!isTransitioning && characterHealth[currentCharacter - 1] > 0)
            {
                if (std::abs(enemy.x - currentX) < 0.2f &&
                    std::abs(enemy.y - translateY) < 0.1f)
                {
                    characterHealth[currentCharacter - 1] = std::max(0, characterHealth[currentCharacter - 1] - 1);
                    enemy.isFalling = true;
                    enemy.speed = 0.0f;
                    enemy.rotationSpeed = 50.0f; // Reset rotation speed when starting to fall
                    enemiesKilled++;

                    // If current character dies, handle the switch immediately
                    if (characterHealth[currentCharacter - 1] <= 0)
                    {
                        handleCharacterDeath();
                    }

                    // Check level completion separately from character death
                    if (enemiesKilled >= totalEnemiesInLevel && characterHealth[0] > 0 && characterHealth[1] > 0)
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

    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
                       [](const Enemy &e)
                       { return !e.isActive; }),
        enemies.end());

    if (needsUpdate)
    {
        glutPostRedisplay();
    }

    if (gameState == GAME_RUNNING)
    {
        glutTimerFunc(30, updateEnemies, 0);
    }
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

void drawBackground()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1, 1);
    glVertex2f(1.0f, -1.0f);
    glTexCoord2f(1, 0);
    glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0, 0);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
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

// Update drawCharacter function for correct positioning
void drawCharacter()
{
    glPushMatrix();
    glScalef(0.25f, 0.25f, 1.0f);
    glTranslatef(currentX * 4.0f, translateY * 4.0f, 0.0f);

    if (currentCharacter == 1)
        drawCat();
    else if (currentCharacter == 2)
        DrawCharacter();

    // Draw character collision box with same size as enemy
    drawTransparentBox(0, 0, 1.0f, 1.0f);

    glPopMatrix();
}

void drawTransition()
{
    if (isTransitioning && !isOutgoingDone)
    {
        // Draw outgoing character
        glPushMatrix();
        glScalef(0.25f, 0.25f, 1.0f);
        glTranslatef(outgoingX * 4.0f, translateY * 4.0f, 0.0f);
        if (currentCharacter == 1)
            drawCat();
        else if (currentCharacter == 2)
            DrawCharacter();
        glPopMatrix();
    }

    if (isTransitioning && isOutgoingDone)
    {
        // Draw incoming character
        glPushMatrix();
        glScalef(0.25f, 0.25f, 1.0f);
        glTranslatef(currentX * 4.0f, translateY * 4.0f, 0.0f);
        if (currentCharacter == 1)
            drawCat();
        else if (currentCharacter == 2)
            DrawCharacter();
        glPopMatrix();
    }
}

void drawHealthBar()
{
    float healthBarWidth = 0.5f;
    float healthBarHeight = 0.05f;
    float healthX = -0.75f;
    float healthY = 0.9f;

    // Get the health of the current character
    int health = characterHealth[currentCharacter - 1];

    glPushMatrix();
    glTranslatef(healthX, healthY, 0.0f);

    // Change the color of the health bar based on the health of the character
    if (health > 2)
        glColor3f(0.0f, 1.0f, 0.0f); // Green
    else if (health > 1)
        glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    else
        glColor3f(1.0f, 0.0f, 0.0f); // Red

    // Draw the health bar (rounded rectangle)
    glBegin(GL_QUADS);
    glVertex2f(-healthBarWidth / 2.0f, -healthBarHeight / 2.0f);
    glVertex2f(healthBarWidth / 2.0f, -healthBarHeight / 2.0f);
    glVertex2f(healthBarWidth / 2.0f, healthBarHeight / 2.0f);
    glVertex2f(-healthBarWidth / 2.0f, healthBarHeight / 2.0f);
    glEnd();

    glPopMatrix();
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

// Add these new functions before the keyboard function
void drawfire()
{
    for (const auto &projectile : projectiles)
    {
        if (!projectile.active)
            continue;

        glPushMatrix();
        glScalef(0.25f, 0.25f, 1.0f); // Apply same scale as character
        glTranslatef(projectile.x * 4.0f, projectile.y * 4.0f, 0.0f);

        // Draw the fire projectile
        glColor3f(1.0f, 1.0f, 0.0f); // Yellow color for fire
        glBegin(GL_QUADS);
        glVertex2f(-0.02f, -0.02f);
        glVertex2f(0.02f, -0.02f);
        glVertex2f(0.02f, 0.02f);
        glVertex2f(-0.02f, 0.02f);
        glEnd();

        // Draw transparent collision box around fire
        drawTransparentBox(0, 0, 0.2f, 0.2f); // Smaller box for projectile

        glPopMatrix();
    }
}

bool checkCollision(float x1, float y1, float x2, float y2, float radius1, float radius2)
{
    float dx = x1 - x2;
    float dy = y1 - y2;
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance < (radius1 + radius2);
}

void updatefire(int value)
{
    if (gameState != GAME_RUNNING)
        return;

    float fixedSpeed = 0.05f;
    bool needsUpdate = false;

    projectiles.remove_if([](const Projectile &p)
                          { return !p.active; });

    for (auto &projectile : projectiles)
    {
        if (!projectile.active)
            continue;

        // Update horizontal position
        projectile.x += (fixedSpeed * projectile.direction);

        // Update vertical position if projectile has vertical speed
        if (projectile.verticalSpeed != 0.0f)
        {
            projectile.y += projectile.verticalSpeed;
            // No gravity for downward shots - they move in a straight line
        }

        // Remove projectiles that go off screen
        if (projectile.x > 4.0f || projectile.x < -4.0f || projectile.y < -5.0f)
        {
            projectile.active = false;
            needsUpdate = true;
            continue;
        }

        for (auto &enemy : enemies)
        {
            if (enemy.isActive && !enemy.isFalling)
            {
                if (checkCollision(projectile.x, projectile.y, enemy.x, enemy.y,
                                   COLLISION_RADIUS * 0.5f, COLLISION_RADIUS))
                {
                    projectile.active = false;

                    // Different damage based on character
                    if (currentCharacter == 1)
                    {
                        // First character (low health) - one shot kill
                        enemy.health = 0;
                    }
                    else
                    {
                        // Second character (high health) - two shots needed
                        enemy.health--;
                    }

                    if (enemy.health <= 0)
                    {
                        enemy.isFalling = true;
                        enemy.speed = 0.0f;
                        enemiesKilled++;
                        score += 100;

                        if (enemiesKilled >= totalEnemiesInLevel)
                        {
                            if (level < maxLevel)
                            {
                                gameState = LEVEL_COMPLETE;
                                glutPostRedisplay();
                            }
                            else
                            {
                                gameState = GAME_WON;
                                score += 1000;
                                glutPostRedisplay();
                            }
                        }
                    }
                    needsUpdate = true;
                    break;
                }
            }
        }
    }

    if (needsUpdate)
    {
        glutPostRedisplay();
    }

    if (!projectiles.empty())
    {
        glutTimerFunc(16, updatefire, 0);
    }
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
            currentX -= 0.1f;
        break;
    case 'd':
    case 'D':
        if (gameState == GAME_RUNNING && !isTransitioning)
            currentX += 0.1f;
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

    // Load background texture
    backgroundTexture = loadTexture("2_21.png");

    // Set up orthographic projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Register callbacks
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    // Start main loop
    glutMainLoop();

    return 0;
}