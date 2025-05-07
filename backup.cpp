#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <cmath>
#include <vector>

#define PI 3.14159265358979323846
float translateX = -3.5f;
float translateY = -3.3f;
int animationActive = true;
int animationPhase = 0;

// the Main color of the cat
float catColorR = 0.6431f;
float catColorG = 0.6039f;
float catColorB = 0.5373f;

// draws a filled trianular area that is bounded on one side by a bezier curve and on the other side by a line
void drawFilled(float xL0, float yL0, float xL1, float yL1, float xL2, float yL2, float xTip, float yTip, int segments = 100)
{
    float t;
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(catColorR, catColorG, catColorB);

    for (int i = 0; i <= segments; ++i)
    {
        t = (float)i / segments;
        
        float xCurve = (1 - t) * (1 - t) * xL0 + 2 * (1 - t) * t * xL1 + t * t * xL2;
        float yCurve = (1 - t) * (1 - t) * yL0 + 2 * (1 - t) * t * yL1 + t * t * yL2;
        
        float xLine = (1 - t) * xL0 + t * xTip;
        float yLine = (1 - t) * yL0 + t * yTip;
        glVertex2f(xCurve, yCurve);
        glVertex2f(xLine, yLine);
    }
    glEnd();
}

void drawCircle(float centerX, float centerY, float radius, int num_segments)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++)
    {
        float theta = 2.0f * 3.14159f * i / num_segments;
        float x = centerX + radius * cosf(theta);
        float y = centerY + radius * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawQuadraticBezier(float P0_x, float P0_y, float P1_x, float P1_y, float P2_x, float P2_y, int segments)
{
    glColor3f(0.0f, 0.0f, 0.0f); // Black color for the curve
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= segments; i++)
    {
        float t = (float)i / segments;
        float x = (1 - t) * (1 - t) * P0_x + 2 * (1 - t) * t * P1_x + t * t * P2_x;
        float y = (1 - t) * (1 - t) * P0_y + 2 * (1 - t) * t * P1_y + t * t * P2_y;
        glVertex2f(x, y);
    }
    glEnd();
}

void drawArc(float cx, float cy, float r, float start_angle, float end_angle, bool clockwise = false, float red = 1.0f, float green = 1.0f, float blue = 1.0f, bool fill = false)
{
    const int segments = 100;
    float step = (end_angle - start_angle) / segments;
    if (clockwise)
        step *= -1;

    glColor3f(red, green, blue);

    if (fill)
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);

        for (int i = 0; i <= segments; ++i)
        {
            float angle = start_angle + step * i;
            float x = cx + r * cos(angle);
            float y = cy + r * sin(angle);
            glVertex2f(x, y);
        }
        glEnd();
    }
    else
    {
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i <= segments; ++i)
        {
            float angle = start_angle + step * i;
            float x = cx + r * cos(angle);
            float y = cy + r * sin(angle);
            glVertex2f(x, y);
        }
        glEnd();
    }
}

void drawhead()
{
    // 3 arcs for the head
    // Left head arc
    drawArc(-0.085f, 0.6f, 0.04f, PI, 2 * PI, false, 0.2549f, 0.2431f, 0.2196f, true);
    // Center head arc
    drawArc(0.0f, 0.6f, 0.04f, PI, 2 * PI, false, 0.2549f, 0.2431f, 0.2196f, true);
    // Right head arc
    drawArc(0.08f, 0.6f, 0.04f, PI, 2 * PI, false, 0.2549f, 0.2431f, 0.2196f, true);
}

void drawears()
{
    // left ear bezier curve control points
    float xL0 = -0.2f, yL0 = 0.8f;
    float xL1 = -0.26f, yL1 = 0.62f;
    float xL2 = -0.26f, yL2 = 0.60f;

    // line endpoint
    float xTip = -0.12233f, yTip = 0.59843f;

    // draw the filled ear using the bezier curve and line
    drawFilled(xL0, yL0, xL1, yL1, xL2, yL2, xTip, yTip);

    // right ear bezier curve control points
    float xR0 = 0.2f, yR0 = 0.8f;
    float xR1 = 0.26f, yR1 = 0.62f;
    float xR2 = 0.26f, yR2 = 0.60f;

    // line endpoint
    float xTip1 = 0.11565f, yTip1 = 0.59803f;

    drawFilled(xR0, yR0, xR1, yR1, xR2, yR2, xTip1, yTip1);
}

void draweyes()
{
    // right eye
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.16785f, 0.45472f);
    glVertex2f(0.1f, 0.4f);
    glVertex2f(0.16216f, 0.37008f);
    glEnd();
    // left eye
    drawCircle(-0.15789f, 0.39961f, 0.03703f, 72);
}

void drawbody()
{
    const int segments = 100;
    float t;

    // contorl points
    float xL0 = -0.26f, yL0 = 0.6f;
    float xL1 = -0.36f, yL1 = 0.1f;
    float xL2 = -0.3f, yL2 = -0.4f;

    float xR0 = 0.26f, yR0 = 0.6f;
    float xR1 = 0.36f, yR1 = 0.1f;
    float xR2 = 0.3f, yR2 = -0.4f;

    // draw the bottom line of the body
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(catColorR, catColorG, catColorB);

    for (int i = 0; i <= segments; ++i)
    {
        t = (float)i / segments;

        // left curve point
        float xL = (1 - t) * (1 - t) * xL0 + 2 * (1 - t) * t * xL1 + t * t * xL2;
        float yL = (1 - t) * (1 - t) * yL0 + 2 * (1 - t) * t * yL1 + t * t * yL2;

        // right curve point
        float xR = (1 - t) * (1 - t) * xR0 + 2 * (1 - t) * t * xR1 + t * t * xR2;
        float yR = (1 - t) * (1 - t) * yR0 + 2 * (1 - t) * t * yR1 + t * t * yR2;

        // bottom line points
        float yBottom = -0.5f;

        glVertex2f(xL, yL);
        glVertex2f(xL, yBottom);

        glVertex2f(xR, yR);
        glVertex2f(xR, yBottom);
    }
    glEnd();
    drawArc(0.323f, -0.05f, 0.05f, 1.5 * PI, 0.5 * PI, false, .2549f, 0.2431f, 0.2196f, true);
    drawArc(0.321f, -0.152f, 0.05f, 1.5 * PI, 0.5 * PI, false, .2549f, 0.2431f, 0.2196f, true);
}

void drawwiskers()
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    
    glVertex2f(-0.25036, 0.32677);
    glVertex2f(-0.33997, 0.35827);

    glVertex2f(-0.24751, 0.37205);
    glVertex2f(-0.33713, 0.41142);

    glVertex2f(0.25178, 0.32283);
    glVertex2f(0.34566, 0.3563);

    glVertex2f(0.25178, 0.37008);
    glVertex2f(0.33997, 0.39961);
    glEnd();
}

void drawhands()
{
    // control points for the bezier curve
    float P0_x = 0.17f, P0_y = 0.0f;
    float P1_x = 0.15f, P1_y = 0.05f;
    float P2_x = 0.17f, P2_y = 0.1f;
    drawQuadraticBezier(P0_x, P0_y, P1_x, P1_y, P2_x, P2_y, 100);

    // control points for the bezier curve
    float P0_x1 = -0.23f;
    float P1_x1 = -0.24f;
    float P2_x1 = -0.22f;

    drawQuadraticBezier(P0_x1, P0_y, P1_x1, P1_y, P2_x1, P2_y, 100);

    drawArc(0.19f, 0.1f, 0.04f, 1.2 * PI, 2.2 * PI, true, 0.0f, 0.0f, 0.0f, false); // rightward for the right hand
    drawArc(-0.2f, 0.1f, 0.04f, 1.2 * PI, 2.2 * PI, true, 0.0f, 0.0f, 0.0f, false); // leftward for the left hand
}

void drawtail()
{
    const int segments = 100;
    float t;

    // control points for the bezier curve (top of the tail)
    float P0_x = 0.3f, P0_y = -0.4f;
    float P1_x = 0.45f, P1_y = -0.35f;
    float P2_x = 0.6f, P2_y = -0.4f;

    // bottom of the tail
    float L0_x = 0.3f, L0_y = -0.5f;
    float L1_x = 0.6f, L1_y = -0.5f;

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(catColorR, catColorG, catColorB);

    for (int i = 0; i <= segments; ++i)
    {
        t = (float)i / segments;

        // point on the bezier curve
        float xBezier = (1 - t) * (1 - t) * P0_x + 2 * (1 - t) * t * P1_x + t * t * P2_x;
        float yBezier = (1 - t) * (1 - t) * P0_y + 2 * (1 - t) * t * P1_y + t * t * P2_y;

        //the bottom line
        float xLine = (1 - t) * L0_x + t * L1_x;
        float yLine = (1 - t) * L0_y + t * L1_y;

        glVertex2f(xBezier, yBezier); 
        glVertex2f(xLine, yLine);
    }

    glEnd();
    drawArc(0.6f, -0.45f, 0.05f, 0.5 * PI, 1.5 * PI, true, .2549f, 0.2431f, 0.2196f, true);
}

void drawmouth()
{
    drawArc(0.05f, 0.27f, 0.05f, PI, 2 * PI, false, 0.2549f, 0.2431f, 0.2196f, false);
    drawArc(-0.05f, 0.27f, 0.05f, PI, 2 * PI, false, 0.2549f, 0.2431f, 0.2196f, false);
}

void drawfeet()
{
    drawArc(-0.31f, -0.451f, 0.05f, 1.5 * PI, 0.5 * PI, false, catColorR, catColorG, catColorB, true);
    drawArc(-0.31f, -0.451f, 0.05f, 1.5 * PI, 0.5 * PI, false, 0.0f, 0.0f, 0.0f, false); // to add stroke
    drawArc(0.15f, -0.46f, 0.06f, 1.2 * PI, 2.1 * PI, true, 0.0f, 0.0f, 0.0f, false);   
}

void drawCat()
{
    drawbody();
    drawhead();
    drawears();
    draweyes();
    drawmouth();
    drawwiskers();
    drawtail();
    drawhands();
    drawfeet();
    glFlush();
}

void animation(int value)
{
    if (animationPhase == 0)
    {
        translateY += 0.1f;
        if (translateY >= 3.0f)
        {
            translateY = 3.0f;
            animationPhase = 1; // Switch to up-right phase
        }
    }
    else if (animationPhase == 1)
    {
        translateY -= 0.024f;
        translateX += 0.014f;
        if (translateY <= -2.9f && translateX >= -0.07f)
        {
            translateY = -2.9f;
            translateX = -0.07f;
            animationPhase = 2;
        }
    }
    else if (animationPhase == 2)
    {
        translateY += 0.023f;
        translateX += 0.013f;
        if (translateY >= 3.0f && translateX >= 3.3f)
        {
            translateY = 3.0f;
            translateX = 3.3f;
            animationPhase = 3;
        }
    }
    else if (animationPhase == 3)
    {
        translateY -= 0.1f;
        if (translateY <= -3.3f)
        {
            translateY = -3.3f;
            animationPhase = 4;
        }
    }
    else if (animationPhase == 4)
    {
        translateX -= 0.05f;

        if (translateX <= -3.5f)
        {
            translateX = -3.5f;
            animationPhase = 0;
            // animationActive = false; // Uncomment to stop animation
        }
    }

    glutPostRedisplay();
    if (animationActive)
        glutTimerFunc(16, animation, 0);
}

void display()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glScalef(0.25f, 0.25f, 1.0f);
    glTranslatef(translateX, translateY, 0.0f);
    drawCat();
    glPopMatrix();
    glFlush();
}

int main(int argc, char **argv)

{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(2000, 2000);
    glutCreateWindow("Cat");
    glutDisplayFunc(display);
    glutTimerFunc(0, animation, 0);
    glutMainLoop();
    return 0;
}

// #define GL_SILENCE_DEPRECATION
// #include <GLUT/glut.h>
// #include <cmath>
// #include <vector>
// #include "./Characters/cat.h"
// #include "./Characters/amoungus.h"

// float translateX = -3.5f;
// float translateY = -3.3f;
// int animationActive = true;
// int animationPhase = 0;
// int currentCharacter = 1; // 1 for Cat, 2 for another character (add more as needed)

// void keyboard(unsigned char key, int x, int y)
// {
//     switch (key)
//     {
//     case '1':
//         currentCharacter = 1;
//         break;
//     case '2':
//         currentCharacter = 2;
//         break;
//     case 27:
//         exit(0);
//     }

//     glutPostRedisplay();
// }

// void display()
// {
//     glClearColor(1.0, 1.0, 1.0, 1.0);
//     glClear(GL_COLOR_BUFFER_BIT);
//     glPushMatrix();
//     glScalef(0.25f, 0.25f, 1.0f);
//     glTranslatef(translateX, translateY, 0.0f);
//     if (currentCharacter == 1)
//     {
//         drawCat();
//     }
//     else if (currentCharacter == 2)
//     {
//         DrawCharacter();
//     }
//     glPopMatrix();
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

//     glutDisplayFunc(display);
//     glutKeyboardFunc(keyboard);

//     glutMainLoop();
//     return 0;
// }

// #define GL_SILENCE_DEPRECATION
// #include <GLUT/glut.h>
// #include <cmath>
// #include <vector>
// #include <cstdio>

// #define STB_IMAGE_IMPLEMENTATION
// #include "./stb_image.h"

// #include "./Characters/cat.h"
// #include "./Characters/amoungus.h"
// // Game States
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
// int currentCharacter = 1; // 1 = Cat, 2 = Among Us
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
//             currentX = -4.0f; // New character starts offscreen left
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
//     glutTimerFunc(16, updateAnimation, 0); // ~60 FPS
// }

// void keyboard(unsigned char key, int x, int y)
// {
//     switch (key)
//     {
//     case '1':
//         if (currentCharacter != 1 && !isTransitioning)
//         {
//             nextCharacter = 1;
//             isTransitioning = true;
//             isOutgoingDone = false;
//             outgoingX = currentX;
//             glutTimerFunc(0, updateAnimation, 0);
//         }
//         break;
//     case '2':
//         if (currentCharacter != 2 && !isTransitioning)
//         {
//             nextCharacter = 2;
//             isTransitioning = true;
//             isOutgoingDone = false;
//             outgoingX = currentX;
//             glutTimerFunc(0, updateAnimation, 0);
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
//     {
//         glPushMatrix();
//         glScalef(0.25f, 0.25f, 1.0f);
//         glTranslatef(currentX, translateY, 0.0f);
//         glColor3f(0.0f, 0.0f, 0.0f);

//         if (currentCharacter == 1)
//             drawCat();
//         else if (currentCharacter == 2)
//             DrawCharacter();

//         glPopMatrix();
//     }

//     if (!isTransitioning)
//     {
//         glPushMatrix();
//         glScalef(0.25f, 0.25f, 1.0f);
//         glTranslatef(currentX, translateY, 0.0f);
//         glColor3f(0.0f, 0.0f, 0.0f);

//         if (currentCharacter == 1)
//             drawCat();
//         else if (currentCharacter == 2)
//             DrawCharacter();

//         glPopMatrix();
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
