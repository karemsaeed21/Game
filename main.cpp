
// #define GL_SILENCE_DEPRECATION
// #include <GLUT/glut.h>
// #include <cmath>
// #include <vector>
// #include <cstdio>

// #define STB_IMAGE_IMPLEMENTATION
// #include "./stb_image.h"

// #include "./Characters/cat.h"
// #include "./Characters/amoungus.h"
// #include "./Characters/enemy.h"


// enum GameState
// {
//     START_SCREEN,
//     GAME_RUNNING,
//     GAME_OVER
// };
// GameState gameState = START_SCREEN;

// // Positions
// float translateY = -2.2f;
// float currentX = -3.5f;
// float targetX = -3.5f;
// float outgoingX = -3.5f;

// // States
// int currentCharacter = 1;
// int nextCharacter = 1;
// bool isTransitioning = false;
// bool isOutgoingDone = false;

// GLuint backgroundTexture;

// GLuint loadTexture(const char *filename)
// {
//     int width, height, channels;
//     unsigned char *data = stbi_load(filename, &width, &height, &channels, 0);
//     if (!data)
//     {
//         printf("Failed to load image: %s\n", filename);
//         exit(1);
//     }

//     GLuint textureID;
//     glGenTextures(1, &textureID);
//     glBindTexture(GL_TEXTURE_2D, textureID);

//     GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

//     glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//     stbi_image_free(data);
//     return textureID;
// }

// void drawText(const char *text)
// {
//     void *font = GLUT_BITMAP_HELVETICA_18;

//     // Approximate pixel dimensions
//     int textPixelWidth = 0;
//     for (const char *c = text; *c; ++c)
//         textPixelWidth += glutBitmapWidth(font, *c);
//     int textPixelHeight = 18; // GLUT_BITMAP_HELVETICA_18 is approx 18 pixels tall

//     // Get window size in pixels to convert to normalized coordinates
//     int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
//     int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

//     // Convert text dimensions from pixels to OpenGL coordinates
//     float textWidth = (float)textPixelWidth / windowWidth * 2.0f; // From -1 to 1
//     float textHeight = (float)textPixelHeight / windowHeight * 2.0f;

//     float paddingX = 0.03f;
//     float paddingY = 0.02f;
//     float boxWidth = textWidth + 2 * paddingX;
//     float boxHeight = textHeight + 2 * paddingY;

//     float boxX = -boxWidth / 2.0f;
//     float boxY = -boxHeight / 2.0f;

//     // Draw semi-transparent box
//     glColor4f(1.0f, 1.0f, 1.0f, 0.85f);
//     glEnable(GL_BLEND);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//     glBegin(GL_QUADS);
//     glVertex2f(boxX, boxY);
//     glVertex2f(boxX + boxWidth, boxY);
//     glVertex2f(boxX + boxWidth, boxY + boxHeight);
//     glVertex2f(boxX, boxY + boxHeight);
//     glEnd();
//     glDisable(GL_BLEND);

//     glColor3f(0.0f, 0.0f, 0.0f);
//     glBegin(GL_LINE_LOOP);
//     glVertex2f(boxX, boxY);
//     glVertex2f(boxX + boxWidth, boxY);
//     glVertex2f(boxX + boxWidth, boxY + boxHeight);
//     glVertex2f(boxX, boxY + boxHeight);
//     glEnd();

//     float textX = -textWidth / 2.0f;
//     float textY = -textHeight / 3.0f;
//     glColor3f(0.0f, 0.0f, 0.0f);
//     glRasterPos2f(textX, textY);
//     while (*text)
//         glutBitmapCharacter(font, *text++);
// }

// void drawBackground()
// {
//     glEnable(GL_TEXTURE_2D);
//     glBindTexture(GL_TEXTURE_2D, backgroundTexture);

//     glBegin(GL_QUADS);
//     glTexCoord2f(0, 1);
//     glVertex2f(-1.0f, -1.0f);
//     glTexCoord2f(1, 1);
//     glVertex2f(1.0f, -1.0f);
//     glTexCoord2f(1, 0);
//     glVertex2f(1.0f, 1.0f);
//     glTexCoord2f(0, 0);
//     glVertex2f(-1.0f, 1.0f);
//     glEnd();

//     glDisable(GL_TEXTURE_2D);
// }

// void updateAnimation(int value)
// {
//     if (!isTransitioning)
//         return;

//     float speed = 0.1f;

//     if (!isOutgoingDone)
//     {
//         outgoingX -= speed;
//         if (outgoingX < -4.0f)
//         {
//             isOutgoingDone = true;
//             currentCharacter = nextCharacter;
//             currentX = -4.0f;
//         }
//     }
//     else
//     {
//         currentX += speed;
//         if (currentX >= -3.5f)
//         {
//             currentX = -3.5f;
//             isTransitioning = false;
//         }
//     }

//     glutPostRedisplay();
//     glutTimerFunc(16, updateAnimation, 0);
// }

// void drawCharacter()
// {
//     glPushMatrix();
//     glScalef(0.25f, 0.25f, 1.0f);
//     glTranslatef(currentX, translateY, 0.0f);
//     glColor3f(0.0f, 0.0f, 0.0f);

//     if (currentCharacter == 1)
//         drawCat();
//     else if (currentCharacter == 2)
//         DrawCharacter();

//         glPopMatrix();
// }

// void drawTransition()
// {
//     if (isTransitioning && !isOutgoingDone)
//     {
//         glPushMatrix();
//         glScalef(0.25f, 0.25f, 1.0f);
//         glTranslatef(outgoingX, translateY, 0.0f);
//         glColor3f(0.0f, 0.0f, 0.0f);
//         if (currentCharacter == 1)
//             drawCat();
//         else if (currentCharacter == 2)
//             DrawCharacter();
//         glPopMatrix();
//     }

//     if (isTransitioning && isOutgoingDone)
//         drawCharacter();
// }

// void keyboard(unsigned char key, int x, int y)
// {
//     switch (key)
//     {
//     case 's':
//         if (gameState == START_SCREEN)
//         {
//             gameState = GAME_RUNNING;
//             glutPostRedisplay();
//         }
//         break;
//     case 'r':
//         if (gameState == GAME_OVER)
//         {
//             gameState = START_SCREEN;
//             currentX = -3.5f;
//             currentCharacter = 1;
//             glutPostRedisplay();
//         }
//         break;
//     case 'g':
//         if (gameState == GAME_RUNNING)
//         {
//             gameState = GAME_OVER;
//             glutPostRedisplay();
//         }
//         break;
//     case '1':
//     case '2':
//         if (gameState == GAME_RUNNING && !isTransitioning)
//         {
//             int selected = key - '0';
//             if (currentCharacter != selected)
//             {
//                 nextCharacter = selected;
//                 isTransitioning = true;
//                 isOutgoingDone = false;
//                 outgoingX = currentX;
//                 glutTimerFunc(0, updateAnimation, 0);
//             }
//         }
//         break;
//     case 27:
//         exit(0);
//     }
// }

// void display()
// {
//     glClearColor(1.0, 1.0, 1.0, 1.0);
//     glClear(GL_COLOR_BUFFER_BIT);

//     drawBackground();
//     glDisable(GL_TEXTURE_2D);
//     glPushAttrib(GL_CURRENT_BIT);

//     switch (gameState)
//     {
//     case START_SCREEN:
//         drawText("Press 's' to Start the Game");
//         break;
//     case GAME_RUNNING:
//         glPushAttrib(GL_CURRENT_BIT);
//         drawTransition();
//         if (!isTransitioning)
//             drawCharacter();
//         glPopAttrib();
//         break;
//     case GAME_OVER:
//         drawText("Game Over!");
//         drawText("Press 'r' to Restart or 'Esc' to Quit");
//         break;
//     }
//     glPopAttrib();
//     glFlush();
// }

// int main(int argc, char **argv)
// {
//     glutInit(&argc, argv);
//     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//     glutInitWindowSize(2000, 2000);
//     glutCreateWindow("Game");

//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

//     backgroundTexture = loadTexture("background.jpg");

//     glutDisplayFunc(display);
//     glutKeyboardFunc(keyboard);

//     glutMainLoop();
//     return 0;
// }

#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <cmath>
#include <vector>
#include <cstdio>

#define STB_IMAGE_IMPLEMENTATION
#include "./dependencies/library/stb_image.h"

#include "./Characters/cat.h"
#include "./Characters/amoungus.h"
#include "./Characters/enemy.h"

enum GameState
{
    START_SCREEN,
    GAME_RUNNING,
    GAME_OVER
};
GameState gameState = START_SCREEN;

// Positions
float translateY = -2.2f;
float currentX = -3.5f;
float targetX = -3.5f;
float outgoingX = -3.5f;

// States
int currentCharacter = 1;
int nextCharacter = 1;
bool isTransitioning = false;
bool isOutgoingDone = false;

GLuint backgroundTexture;

std::vector<Enemy> enemies;
int level = 1;
int maxLevel = 5;

int enemiesPerLevel[] = {0, 2, 5, 10, 15, 20}; // Level 0 unused

GLuint loadTexture(const char *filename)
{
    int width, height, channels;
    unsigned char *data = stbi_load(filename, &width, &height, &channels, 0);
    if (!data)
    {
        printf("Failed to load image: %s\n", filename);
        exit(1);
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    return textureID;
}

void spawnEnemies(int count)
{
    enemies.clear();
    for (int i = 0; i < count; ++i)
    {
        float y = -3.0f;           // or vary if needed
        float x = 5.2f + i * 0.5f; // Staggered entry
        enemies.push_back({x, y});
    }
}

void drawEnemies()
{
    for (const auto &enemy : enemies)
    {
        glPushMatrix();
        glScalef(0.2f, 0.2f, 1.0f);
        glTranslatef(enemy.x, enemy.y, 0.0f);
        drawCreeper();
        glPopMatrix();
    }
}

void updateEnemies(int value)
{
    if (gameState != GAME_RUNNING)
        return;

    float speed = 0.02f;
    for (auto &enemy : enemies)
    {
        enemy.x -= speed;
    }

    glutPostRedisplay();
    glutTimerFunc(30, updateEnemies, 0);
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

    float speed = 0.1f;

    if (!isOutgoingDone)
    {
        outgoingX -= speed;
        if (outgoingX < -4.0f)
        {
            isOutgoingDone = true;
            currentCharacter = nextCharacter;
            currentX = -4.0f;
        }
    }
    else
    {
        currentX += speed;
        if (currentX >= -3.5f)
        {
            currentX = -3.5f;
            isTransitioning = false;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateAnimation, 0);
}

void drawCharacter()
{
    glPushMatrix();
    glScalef(0.25f, 0.25f, 1.0f);
    glTranslatef(currentX, translateY, 0.0f);

    if (currentCharacter == 1)
        drawCat();
    else if (currentCharacter == 2)
        DrawCharacter();

    glPopMatrix();
}

void drawTransition()
{
    if (isTransitioning && !isOutgoingDone)
    {
        glPushMatrix();
        glScalef(0.25f, 0.25f, 1.0f);
        glTranslatef(outgoingX, translateY, 0.0f);
        if (currentCharacter == 1)
            drawCat();
        else if (currentCharacter == 2)
            DrawCharacter();
        glPopMatrix();
    }

    if (isTransitioning && isOutgoingDone)
        drawCharacter();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 's':
        if (gameState == START_SCREEN)
        {
            gameState = GAME_RUNNING;
            spawnEnemies(enemiesPerLevel[level]);
            glutTimerFunc(30, updateEnemies, 0);
            glutPostRedisplay();
        }
        break;
    case 'r':
        if (gameState == GAME_OVER)
        {
            gameState = START_SCREEN;
            currentX = -3.5f;
            currentCharacter = 1;
            level = 1;
            enemies.clear();
            glutPostRedisplay();
        }
        break;
    case 'g':
        if (gameState == GAME_RUNNING)
        {
            gameState = GAME_OVER;
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
            if (currentCharacter != selected)
            {
                nextCharacter = selected;
                isTransitioning = true;
                isOutgoingDone = false;
                outgoingX = currentX;
                glutTimerFunc(0, updateAnimation, 0);
            }
        }
        break;
    case 27:
        exit(0);
    }
}

void display()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    drawBackground();
    glDisable(GL_TEXTURE_2D);
    glPushAttrib(GL_CURRENT_BIT);

    switch (gameState)
    {
    case START_SCREEN:
        drawText("Press 's' to Start the Game");
        break;
    case GAME_RUNNING:
        drawTransition();
        if (!isTransitioning)
            drawCharacter();
        drawEnemies();
        break;
    case GAME_OVER:
        drawText("Game Over!");
        drawText("Press 'r' to Restart or 'Esc' to Quit");
        break;
    }
    glPopAttrib();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(2000, 2000);
    glutCreateWindow("Game");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    backgroundTexture = loadTexture("background.jpg");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
