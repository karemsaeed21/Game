// #define GL_SILENCE_DEPRECATION
// #include <GLUT/glut.h>
// #include <cmath>
// #include <vector>

// #define PI 3.14159265358979323846
// float translateX = -3.5f;
// float translateY = -3.3f;
// int animationActive = true;
// int animationPhase = 0;

// // the Main color of the cat
// float catColorR = 0.6431f;
// float catColorG = 0.6039f;
// float catColorB = 0.5373f;

// // draws a filled trianular area that is bounded on one side by a bezier curve and on the other side by a line
// void drawFilled(float xL0, float yL0, float xL1, float yL1, float xL2, float yL2, float xTip, float yTip, int segments = 100)
// {
//     float t;
//     glBegin(GL_TRIANGLE_STRIP);
//     glColor3f(catColorR, catColorG, catColorB);

//     for (int i = 0; i <= segments; ++i)
//     {
//         t = (float)i / segments;
        
//         float xCurve = (1 - t) * (1 - t) * xL0 + 2 * (1 - t) * t * xL1 + t * t * xL2;
//         float yCurve = (1 - t) * (1 - t) * yL0 + 2 * (1 - t) * t * yL1 + t * t * yL2;
        
//         float xLine = (1 - t) * xL0 + t * xTip;
//         float yLine = (1 - t) * yL0 + t * yTip;
//         glVertex2f(xCurve, yCurve);
//         glVertex2f(xLine, yLine);
//     }
//     glEnd();
// }

// void drawCircle(float centerX, float centerY, float radius, int num_segments)
// {
//     glBegin(GL_POLYGON);
//     for (int i = 0; i < num_segments; i++)
//     {
//         float theta = 2.0f * 3.14159f * i / num_segments;
//         float x = centerX + radius * cosf(theta);
//         float y = centerY + radius * sinf(theta);
//         glVertex2f(x, y);
//     }
//     glEnd();
// }

// void drawQuadraticBezier(float P0_x, float P0_y, float P1_x, float P1_y, float P2_x, float P2_y, int segments)
// {
//     glColor3f(0.0f, 0.0f, 0.0f); // Black color for the curve
//     glBegin(GL_LINE_STRIP);
//     for (int i = 0; i <= segments; i++)
//     {
//         float t = (float)i / segments;
//         float x = (1 - t) * (1 - t) * P0_x + 2 * (1 - t) * t * P1_x + t * t * P2_x;
//         float y = (1 - t) * (1 - t) * P0_y + 2 * (1 - t) * t * P1_y + t * t * P2_y;
//         glVertex2f(x, y);
//     }
//     glEnd();
// }

// void drawArc(float cx, float cy, float r, float start_angle, float end_angle, bool clockwise = false, float red = 1.0f, float green = 1.0f, float blue = 1.0f, bool fill = false)
// {
//     const int segments = 100;
//     float step = (end_angle - start_angle) / segments;
//     if (clockwise)
//         step *= -1;

//     glColor3f(red, green, blue);

//     if (fill)
//     {
//         glBegin(GL_TRIANGLE_FAN);
//         glVertex2f(cx, cy);

//         for (int i = 0; i <= segments; ++i)
//         {
//             float angle = start_angle + step * i;
//             float x = cx + r * cos(angle);
//             float y = cy + r * sin(angle);
//             glVertex2f(x, y);
//         }
//         glEnd();
//     }
//     else
//     {
//         glBegin(GL_LINE_STRIP);
//         for (int i = 0; i <= segments; ++i)
//         {
//             float angle = start_angle + step * i;
//             float x = cx + r * cos(angle);
//             float y = cy + r * sin(angle);
//             glVertex2f(x, y);
//         }
//         glEnd();
//     }
// }

// void drawhead()
// {
//     // 3 arcs for the head
//     // Left head arc
//     drawArc(-0.085f, 0.6f, 0.04f, PI, 2 * PI, false, 0.2549f, 0.2431f, 0.2196f, true);
//     // Center head arc
//     drawArc(0.0f, 0.6f, 0.04f, PI, 2 * PI, false, 0.2549f, 0.2431f, 0.2196f, true);
//     // Right head arc
//     drawArc(0.08f, 0.6f, 0.04f, PI, 2 * PI, false, 0.2549f, 0.2431f, 0.2196f, true);
// }

// void drawears()
// {
//     // left ear bezier curve control points
//     float xL0 = -0.2f, yL0 = 0.8f;
//     float xL1 = -0.26f, yL1 = 0.62f;
//     float xL2 = -0.26f, yL2 = 0.60f;

//     // line endpoint
//     float xTip = -0.12233f, yTip = 0.59843f;

//     // draw the filled ear using the bezier curve and line
//     drawFilled(xL0, yL0, xL1, yL1, xL2, yL2, xTip, yTip);

//     // right ear bezier curve control points
//     float xR0 = 0.2f, yR0 = 0.8f;
//     float xR1 = 0.26f, yR1 = 0.62f;
//     float xR2 = 0.26f, yR2 = 0.60f;

//     // line endpoint
//     float xTip1 = 0.11565f, yTip1 = 0.59803f;

//     drawFilled(xR0, yR0, xR1, yR1, xR2, yR2, xTip1, yTip1);
// }

// void draweyes()
// {
//     // right eye
//     glBegin(GL_LINE_STRIP);
//     glColor3f(0.0f, 0.0f, 0.0f);
//     glVertex2f(0.16785f, 0.45472f);
//     glVertex2f(0.1f, 0.4f);
//     glVertex2f(0.16216f, 0.37008f);
//     glEnd();
//     // left eye
//     drawCircle(-0.15789f, 0.39961f, 0.03703f, 72);
// }

// void drawbody()
// {
//     const int segments = 100;
//     float t;

//     // contorl points
//     float xL0 = -0.26f, yL0 = 0.6f;
//     float xL1 = -0.36f, yL1 = 0.1f;
//     float xL2 = -0.3f, yL2 = -0.4f;

//     float xR0 = 0.26f, yR0 = 0.6f;
//     float xR1 = 0.36f, yR1 = 0.1f;
//     float xR2 = 0.3f, yR2 = -0.4f;

//     // draw the bottom line of the body
//     glBegin(GL_TRIANGLE_STRIP);
//     glColor3f(catColorR, catColorG, catColorB);

//     for (int i = 0; i <= segments; ++i)
//     {
//         t = (float)i / segments;

//         // left curve point
//         float xL = (1 - t) * (1 - t) * xL0 + 2 * (1 - t) * t * xL1 + t * t * xL2;
//         float yL = (1 - t) * (1 - t) * yL0 + 2 * (1 - t) * t * yL1 + t * t * yL2;

//         // right curve point
//         float xR = (1 - t) * (1 - t) * xR0 + 2 * (1 - t) * t * xR1 + t * t * xR2;
//         float yR = (1 - t) * (1 - t) * yR0 + 2 * (1 - t) * t * yR1 + t * t * yR2;

//         // bottom line points
//         float yBottom = -0.5f;

//         glVertex2f(xL, yL);
//         glVertex2f(xL, yBottom);

//         glVertex2f(xR, yR);
//         glVertex2f(xR, yBottom);
//     }
//     glEnd();
//     drawArc(0.323f, -0.05f, 0.05f, 1.5 * PI, 0.5 * PI, false, .2549f, 0.2431f, 0.2196f, true);
//     drawArc(0.321f, -0.152f, 0.05f, 1.5 * PI, 0.5 * PI, false, .2549f, 0.2431f, 0.2196f, true);
// }

// void drawwiskers()
// {
//     glColor3f(0.0f, 0.0f, 0.0f);
//     glBegin(GL_LINES);
    
//     glVertex2f(-0.25036, 0.32677);
//     glVertex2f(-0.33997, 0.35827);

//     glVertex2f(-0.24751, 0.37205);
//     glVertex2f(-0.33713, 0.41142);

//     glVertex2f(0.25178, 0.32283);
//     glVertex2f(0.34566, 0.3563);

//     glVertex2f(0.25178, 0.37008);
//     glVertex2f(0.33997, 0.39961);
//     glEnd();
// }

// void drawhands()
// {
//     // control points for the bezier curve
//     float P0_x = 0.17f, P0_y = 0.0f;
//     float P1_x = 0.15f, P1_y = 0.05f;
//     float P2_x = 0.17f, P2_y = 0.1f;
//     drawQuadraticBezier(P0_x, P0_y, P1_x, P1_y, P2_x, P2_y, 100);

//     // control points for the bezier curve
//     float P0_x1 = -0.23f;
//     float P1_x1 = -0.24f;
//     float P2_x1 = -0.22f;

//     drawQuadraticBezier(P0_x1, P0_y, P1_x1, P1_y, P2_x1, P2_y, 100);

//     drawArc(0.19f, 0.1f, 0.04f, 1.2 * PI, 2.2 * PI, true, 0.0f, 0.0f, 0.0f, false); // rightward for the right hand
//     drawArc(-0.2f, 0.1f, 0.04f, 1.2 * PI, 2.2 * PI, true, 0.0f, 0.0f, 0.0f, false); // leftward for the left hand
// }

// void drawtail()
// {
//     const int segments = 100;
//     float t;

//     // control points for the bezier curve (top of the tail)
//     float P0_x = 0.3f, P0_y = -0.4f;
//     float P1_x = 0.45f, P1_y = -0.35f;
//     float P2_x = 0.6f, P2_y = -0.4f;

//     // bottom of the tail
//     float L0_x = 0.3f, L0_y = -0.5f;
//     float L1_x = 0.6f, L1_y = -0.5f;

//     glBegin(GL_TRIANGLE_STRIP);
//     glColor3f(catColorR, catColorG, catColorB);

//     for (int i = 0; i <= segments; ++i)
//     {
//         t = (float)i / segments;

//         // point on the bezier curve
//         float xBezier = (1 - t) * (1 - t) * P0_x + 2 * (1 - t) * t * P1_x + t * t * P2_x;
//         float yBezier = (1 - t) * (1 - t) * P0_y + 2 * (1 - t) * t * P1_y + t * t * P2_y;

//         //the bottom line
//         float xLine = (1 - t) * L0_x + t * L1_x;
//         float yLine = (1 - t) * L0_y + t * L1_y;

//         glVertex2f(xBezier, yBezier); 
//         glVertex2f(xLine, yLine);
//     }

//     glEnd();
//     drawArc(0.6f, -0.45f, 0.05f, 0.5 * PI, 1.5 * PI, true, .2549f, 0.2431f, 0.2196f, true);
// }

// void drawmouth()
// {
//     drawArc(0.05f, 0.27f, 0.05f, PI, 2 * PI, false, 0.2549f, 0.2431f, 0.2196f, false);
//     drawArc(-0.05f, 0.27f, 0.05f, PI, 2 * PI, false, 0.2549f, 0.2431f, 0.2196f, false);
// }

// void drawfeet()
// {
//     drawArc(-0.31f, -0.451f, 0.05f, 1.5 * PI, 0.5 * PI, false, catColorR, catColorG, catColorB, true);
//     drawArc(-0.31f, -0.451f, 0.05f, 1.5 * PI, 0.5 * PI, false, 0.0f, 0.0f, 0.0f, false); // to add stroke
//     drawArc(0.15f, -0.46f, 0.06f, 1.2 * PI, 2.1 * PI, true, 0.0f, 0.0f, 0.0f, false);   
// }

// void drawCat()
// {
//     drawbody();
//     drawhead();
//     drawears();
//     draweyes();
//     drawmouth();
//     drawwiskers();
//     drawtail();
//     drawhands();
//     drawfeet();
//     glFlush();
// }

// void animation(int value)
// {
//     if (animationPhase == 0)
//     {
//         translateY += 0.1f;
//         if (translateY >= 3.0f)
//         {
//             translateY = 3.0f;
//             animationPhase = 1; // Switch to up-right phase
//         }
//     }
//     else if (animationPhase == 1)
//     {
//         translateY -= 0.024f;
//         translateX += 0.014f;
//         if (translateY <= -2.9f && translateX >= -0.07f)
//         {
//             translateY = -2.9f;
//             translateX = -0.07f;
//             animationPhase = 2;
//         }
//     }
//     else if (animationPhase == 2)
//     {
//         translateY += 0.023f;
//         translateX += 0.013f;
//         if (translateY >= 3.0f && translateX >= 3.3f)
//         {
//             translateY = 3.0f;
//             translateX = 3.3f;
//             animationPhase = 3;
//         }
//     }
//     else if (animationPhase == 3)
//     {
//         translateY -= 0.1f;
//         if (translateY <= -3.3f)
//         {
//             translateY = -3.3f;
//             animationPhase = 4;
//         }
//     }
//     else if (animationPhase == 4)
//     {
//         translateX -= 0.05f;

//         if (translateX <= -3.5f)
//         {
//             translateX = -3.5f;
//             animationPhase = 0;
//             // animationActive = false; // Uncomment to stop animation
//         }
//     }

//     glutPostRedisplay();
//     if (animationActive)
//         glutTimerFunc(16, animation, 0);
// }

// void display()
// {
//     glClearColor(1.0, 1.0, 1.0, 1.0);
//     glClear(GL_COLOR_BUFFER_BIT);
//     glPushMatrix();
//     glScalef(0.25f, 0.25f, 1.0f);
//     glTranslatef(translateX, translateY, 0.0f);
//     drawCat();
//     glPopMatrix();
//     glFlush();
// }

// int main(int argc, char **argv)

// {
//     glutInit(&argc, argv);
//     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//     glutInitWindowSize(2000, 2000);
//     glutCreateWindow("Cat");
//     glutDisplayFunc(display);
//     glutTimerFunc(0, animation, 0);
//     glutMainLoop();
//     return 0;
// }

// // #define GL_SILENCE_DEPRECATION
// // #include <GLUT/glut.h>
// // #include <cmath>
// // #include <vector>
// // #include "./Characters/cat.h"
// // #include "./Characters/amoungus.h"

// // float translateX = -3.5f;
// // float translateY = -3.3f;
// // int animationActive = true;
// // int animationPhase = 0;
// // int currentCharacter = 1; // 1 for Cat, 2 for another character (add more as needed)

// // void keyboard(unsigned char key, int x, int y)
// // {
// //     switch (key)
// //     {
// //     case '1':
// //         currentCharacter = 1;
// //         break;
// //     case '2':
// //         currentCharacter = 2;
// //         break;
// //     case 27:
// //         exit(0);
// //     }

// //     glutPostRedisplay();
// // }

// // void display()
// // {
// //     glClearColor(1.0, 1.0, 1.0, 1.0);
// //     glClear(GL_COLOR_BUFFER_BIT);
// //     glPushMatrix();
// //     glScalef(0.25f, 0.25f, 1.0f);
// //     glTranslatef(translateX, translateY, 0.0f);
// //     if (currentCharacter == 1)
// //     {
// //         drawCat();
// //     }
// //     else if (currentCharacter == 2)
// //     {
// //         DrawCharacter();
// //     }
// //     glPopMatrix();
// //     glFlush();
// // }

// // int main(int argc, char **argv)

// // {
// //     glutInit(&argc, argv);
// //     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
// //     glutInitWindowSize(2000, 2000);

// //     glutCreateWindow("Game");
// //     glMatrixMode(GL_PROJECTION);
// //     glLoadIdentity();
// //     gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

// //     glutDisplayFunc(display);
// //     glutKeyboardFunc(keyboard);

// //     glutMainLoop();
// //     return 0;
// // }

// // #define GL_SILENCE_DEPRECATION
// // #include <GLUT/glut.h>
// // #include <cmath>
// // #include <vector>
// // #include <cstdio>

// // #define STB_IMAGE_IMPLEMENTATION
// // #include "./stb_image.h"

// // #include "./Characters/cat.h"
// // #include "./Characters/amoungus.h"
// // // Game States
// // enum GameState
// // {
// //     START_SCREEN,
// //     GAME_RUNNING,
// //     GAME_OVER
// // };
// // GameState gameState = START_SCREEN;

// // // Positions
// // float translateY = -2.2f;
// // float currentX = -3.5f;
// // float targetX = -3.5f;
// // float outgoingX = -3.5f;

// // // States
// // int currentCharacter = 1; // 1 = Cat, 2 = Among Us
// // int nextCharacter = 1;
// // bool isTransitioning = false;
// // bool isOutgoingDone = false;

// // GLuint backgroundTexture;

// // GLuint loadTexture(const char *filename)
// // {
// //     int width, height, channels;
// //     unsigned char *data = stbi_load(filename, &width, &height, &channels, 0);
// //     if (!data)
// //     {
// //         printf("Failed to load image: %s\n", filename);
// //         exit(1);
// //     }

// //     GLuint textureID;
// //     glGenTextures(1, &textureID);
// //     glBindTexture(GL_TEXTURE_2D, textureID);

// //     GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

// //     glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

// //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

// //     stbi_image_free(data);
// //     return textureID;
// // }

// // void drawBackground()
// // {
// //     glEnable(GL_TEXTURE_2D);
// //     glBindTexture(GL_TEXTURE_2D, backgroundTexture);

// //     glBegin(GL_QUADS);
// //     glTexCoord2f(0, 1);
// //     glVertex2f(-1.0f, -1.0f);
// //     glTexCoord2f(1, 1);
// //     glVertex2f(1.0f, -1.0f);
// //     glTexCoord2f(1, 0);
// //     glVertex2f(1.0f, 1.0f);
// //     glTexCoord2f(0, 0);
// //     glVertex2f(-1.0f, 1.0f);
// //     glEnd();

// //     glDisable(GL_TEXTURE_2D);
// // }

// // void updateAnimation(int value)
// // {
// //     if (!isTransitioning)
// //         return;

// //     float speed = 0.1f;

// //     if (!isOutgoingDone)
// //     {
// //         outgoingX -= speed;
// //         if (outgoingX < -4.0f)
// //         {
// //             isOutgoingDone = true;
// //             currentCharacter = nextCharacter;
// //             currentX = -4.0f; // New character starts offscreen left
// //         }
// //     }
// //     else
// //     {
// //         currentX += speed;
// //         if (currentX >= -3.5f)
// //         {
// //             currentX = -3.5f;
// //             isTransitioning = false;
// //         }
// //     }

// //     glutPostRedisplay();
// //     glutTimerFunc(16, updateAnimation, 0); // ~60 FPS
// // }

// // void keyboard(unsigned char key, int x, int y)
// // {
// //     switch (key)
// //     {
// //     case '1':
// //         if (currentCharacter != 1 && !isTransitioning)
// //         {
// //             nextCharacter = 1;
// //             isTransitioning = true;
// //             isOutgoingDone = false;
// //             outgoingX = currentX;
// //             glutTimerFunc(0, updateAnimation, 0);
// //         }
// //         break;
// //     case '2':
// //         if (currentCharacter != 2 && !isTransitioning)
// //         {
// //             nextCharacter = 2;
// //             isTransitioning = true;
// //             isOutgoingDone = false;
// //             outgoingX = currentX;
// //             glutTimerFunc(0, updateAnimation, 0);
// //         }
// //         break;
// //     case 27:
// //         exit(0);
// //     }
// // }

// // void display()
// // {
// //     glClearColor(1.0, 1.0, 1.0, 1.0);
// //     glClear(GL_COLOR_BUFFER_BIT);

// //     drawBackground();

// //     glDisable(GL_TEXTURE_2D);
// //     glPushAttrib(GL_CURRENT_BIT);

// //     if (isTransitioning && !isOutgoingDone)
// //     {
// //         glPushMatrix();
// //         glScalef(0.25f, 0.25f, 1.0f);
// //         glTranslatef(outgoingX, translateY, 0.0f);
// //         glColor3f(0.0f, 0.0f, 0.0f);

// //         if (currentCharacter == 1)
// //             drawCat();
// //         else if (currentCharacter == 2)
// //             DrawCharacter();

// //         glPopMatrix();
// //     }

// //     if (isTransitioning && isOutgoingDone)
// //     {
// //         glPushMatrix();
// //         glScalef(0.25f, 0.25f, 1.0f);
// //         glTranslatef(currentX, translateY, 0.0f);
// //         glColor3f(0.0f, 0.0f, 0.0f);

// //         if (currentCharacter == 1)
// //             drawCat();
// //         else if (currentCharacter == 2)
// //             DrawCharacter();

// //         glPopMatrix();
// //     }

// //     if (!isTransitioning)
// //     {
// //         glPushMatrix();
// //         glScalef(0.25f, 0.25f, 1.0f);
// //         glTranslatef(currentX, translateY, 0.0f);
// //         glColor3f(0.0f, 0.0f, 0.0f);

// //         if (currentCharacter == 1)
// //             drawCat();
// //         else if (currentCharacter == 2)
// //             DrawCharacter();

// //         glPopMatrix();
// //     }

// //     glPopAttrib();
// //     glFlush();
// // }

// // int main(int argc, char **argv)
// // {
// //     glutInit(&argc, argv);
// //     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
// //     glutInitWindowSize(2000, 2000);
// //     glutCreateWindow("Game");

// //     glMatrixMode(GL_PROJECTION);
// //     glLoadIdentity();
// //     gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

// //     backgroundTexture = loadTexture("background.jpg");

// //     glutDisplayFunc(display);
// //     glutKeyboardFunc(keyboard);

// //     glutMainLoop();
// //     return 0;
// // }

// #define GL_SILENCE_DEPRECATION
// #include <GLUT/glut.h>
// #include <cmath>
// #include <vector>
// #include <cstdio>
// #include <cstdlib>
// #include <ctime>

// #define STB_IMAGE_IMPLEMENTATION
// #include "./dependencies/library/stb_image.h"

// #include "./Characters/cat.h"
// #include "./Characters/amoungus.h"
// #include "./Characters/enemy.h"

// enum GameState
// {
//     START_SCREEN,
//     GAME_RUNNING,
//     PAUSED,
//     GAME_OVER
// };
// GameState gameState = START_SCREEN;
// float velocityY = 0.0f;
// bool isJumping = false;
// const float gravity = -0.01f;
// const float jumpStrength = 0.2f;
// const float groundY = -2.05f;

// int characterHealth[] = {3, 3};

// // Positions
// float translateY = -2.05f;
// float currentX = -3.5f;
// float targetX = -3.5f;
// float outgoingX = -3.5f;

// // States
// int currentCharacter = 1;
// int nextCharacter = 1;
// bool isTransitioning = false;
// bool isOutgoingDone = false;

// GLuint backgroundTexture;

// int score = 0;

// std::vector<Enemy> enemies;
// int level = 1;
// int maxLevel = 5;

// int enemiesPerLevel[] = {0, 2, 5, 10, 15, 20};

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

// void spawnEnemies(int count)
// {
//     enemies.clear();
//     srand(static_cast<unsigned>(time(0))); // Seed random generator

//     for (int i = 0; i < count; ++i)
//     {
//         float y = -3.0f;
//         float x = 4.0f + static_cast<float>(rand() % 100) / 10.0f;
//         float speed = 0.01f + static_cast<float>(rand() % 10) / 1000.0f;
//         enemies.push_back({x, y, speed});
//     }
// }

// void drawEnemies()
// {
//     for (const auto &enemy : enemies)
//     {
//         glPushMatrix();
//         glScalef(0.2f, 0.2f, 1.0f);
//         glTranslatef(enemy.x, enemy.y, 0.0f);
//         drawCreeper();
//         glPopMatrix();
//     }
// }

// void updateEnemies(int value)
// {
//     if (gameState != GAME_RUNNING)
//         return;

//     for (auto &enemy : enemies)
//     {
//         enemy.x -= enemy.speed;
//     }

//     glutPostRedisplay();
//     glutTimerFunc(30, updateEnemies, 0);
// }

// void drawText(const char *text)
// {
//     void *font = GLUT_BITMAP_HELVETICA_18;

//     int textPixelWidth = 0;
//     for (const char *c = text; *c; ++c)
//         textPixelWidth += glutBitmapWidth(font, *c);
//     int textPixelHeight = 18;

//     int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
//     int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

//     float textWidth = (float)textPixelWidth / windowWidth * 2.0f;
//     float textHeight = (float)textPixelHeight / windowHeight * 2.0f;

//     float paddingX = 0.03f;
//     float paddingY = 0.02f;
//     float boxWidth = textWidth + 2 * paddingX;
//     float boxHeight = textHeight + 2 * paddingY;

//     float boxX = -boxWidth / 2.0f;
//     float boxY = -boxHeight / 2.0f;

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

//     if (currentCharacter == 1)
//         drawCat();
//     else if (currentCharacter == 2)
//         DrawCharacter();

//     glPopMatrix();
// }

// void drawTransition()
// {
//     if (isTransitioning && !isOutgoingDone)
//     {
//         glPushMatrix();
//         glScalef(0.25f, 0.25f, 1.0f);
//         glTranslatef(outgoingX, translateY, 0.0f);
//         if (currentCharacter == 1)
//             drawCat();
//         else if (currentCharacter == 2)
//             DrawCharacter();
//         glPopMatrix();
//     }

//     if (isTransitioning && isOutgoingDone)
//         drawCharacter();
// }

// void drawHealthBar()
// {
//     float healthBarWidth = 0.5f;
//     float healthBarHeight = 0.05f;
//     float healthX = -0.75f;
//     float healthY = 0.9f;

//     // Get the health of the current character
//     int health = characterHealth[currentCharacter - 1];

//     glPushMatrix();
//     glTranslatef(healthX, healthY, 0.0f);

//     // Change the color of the health bar based on the health of the character
//     if (health > 2)
//         glColor3f(0.0f, 1.0f, 0.0f); // Green
//     else if (health > 1)
//         glColor3f(1.0f, 1.0f, 0.0f); // Yellow
//     else
//         glColor3f(1.0f, 0.0f, 0.0f); // Red

//     // Draw the health bar (rounded rectangle)
//     glBegin(GL_QUADS);
//     glVertex2f(-healthBarWidth / 2.0f, -healthBarHeight / 2.0f);
//     glVertex2f(healthBarWidth / 2.0f, -healthBarHeight / 2.0f);
//     glVertex2f(healthBarWidth / 2.0f, healthBarHeight / 2.0f);
//     glVertex2f(-healthBarWidth / 2.0f, healthBarHeight / 2.0f);
//     glEnd();

//     glPopMatrix();
// }

// void updateJump()
// {
//     if (!isJumping)
//         return;

//     velocityY += gravity;
//     translateY += velocityY;

//     if (translateY <= groundY)
//     {
//         translateY = groundY;
//         velocityY = 0.0f;
//         isJumping = false;
//     }

//     else
//     {
//         glutTimerFunc(16, [](int)
//                       { updateJump(); }, 0); // Continue jump update
//     }

//     glutPostRedisplay();
// }

// void keyboard(unsigned char key, int x, int y)
// {
//     switch (key)
//     {
//     case 'e':
//         if (gameState == START_SCREEN)
//         {
//             gameState = GAME_RUNNING;
//             spawnEnemies(enemiesPerLevel[level]);
//             glutTimerFunc(30, updateEnemies, 0);
//             glutPostRedisplay();
//         }
//         break;
//     case 'r':
//         if (gameState == GAME_OVER)
//         {
//             gameState = START_SCREEN;
//             currentX = -3.5f;
//             currentCharacter = 1;
//             level = 1;
//             enemies.clear();
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
//     case 'n':
//         if (gameState == GAME_RUNNING && level < maxLevel)
//         {
//             level++;
//             spawnEnemies(enemiesPerLevel[level]);
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
//     case 'a':
//         if (gameState == GAME_RUNNING && !isTransitioning)
//             currentX -= 0.1f;
//         break;
//     case 'd':
//         if (gameState == GAME_RUNNING && !isTransitioning)
//             currentX += 0.1f;
//         break;
//     case ' ':
//         if (gameState == GAME_RUNNING && !isJumping)
//         {
//             isJumping = true;
//             velocityY = jumpStrength;
//             glutTimerFunc(16, [](int)
//                           { updateJump(); }, 0);
//         }
//         break;
//     case 'p':
//         if (gameState == GAME_RUNNING)
//         {
//             gameState = PAUSED;
//         }
//         else if (gameState == PAUSED)
//         {
//             gameState = GAME_RUNNING;
//             glutTimerFunc(30, updateEnemies, 0);
//         }
//         glutPostRedisplay();
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
//         drawText("Press 'e' to Start the Game");
//         break;
//     case GAME_RUNNING:
//         drawTransition();
//         if (!isTransitioning)
//             drawCharacter();
//         drawEnemies();
//         drawHealthBar();
//         break;
//     case PAUSED:
//         drawText("Game Paused");
//         drawText("Press 'p' to Resume");
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
//     glutInitWindowSize(2000, 2000); // Use 2000 if you want ultra-HD
//     glutCreateWindow("OpenGL Character Game");

//     // Load background texture
//     backgroundTexture = loadTexture("2_21.png");

//     // Set up orthographic projection
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();

//     // Register callbacks
//     glutDisplayFunc(display);
//     glutKeyboardFunc(keyboard);

//     // Start main loop
//     glutMainLoop();

//     return 0;
// }

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
        glRotatef(enemy.rotation, 0.0f, 0.0f, 1.0f); // Add rotation

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

    // Clean up inactive projectiles first
    projectiles.remove_if([](const Projectile &p)
                          { return !p.active; });

    for (auto &projectile : projectiles)
    {
        if (!projectile.active)
            continue;

        projectile.x += (fixedSpeed * projectile.direction);

        // Remove projectiles that go off screen
        if (projectile.x > 4.0f || projectile.x < -4.0f)
        {
            projectile.active = false;
            needsUpdate = true;
            continue;
        }

        // Check collision with enemies using circle collision
        for (auto &enemy : enemies)
        {
            if (enemy.isActive && !enemy.isFalling)
            {
                if (checkCollision(projectile.x, projectile.y, enemy.x, enemy.y,
                                   COLLISION_RADIUS * 0.5f, COLLISION_RADIUS))
                {
                    projectile.active = false;
                    enemy.isFalling = true;
                    enemy.speed = 0.0f;
                    enemiesKilled++;
                    score += 100;

                    if (enemiesKilled >= totalEnemiesInLevel)
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
                    break;
                }
            }
        }
    }

    if (needsUpdate)
    {
        glutPostRedisplay();
    }

    // Only continue timer if there are active projectiles
    if (!projectiles.empty())
    {
        glutTimerFunc(16, updatefire, 0); // Increased update frequency
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
            score = 0; // Reset score
            enemies.clear();
            characterHealth[0] = 2;
            characterHealth[1] = 5;
            targetX = -0.8f;
            outgoingX = -0.8f;
            isTransitioning = false;
            isOutgoingDone = false;
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
        if (gameState == GAME_RUNNING && !isTransitioning)
            currentX -= 0.1f;
        break;
    case 'd':
        if (gameState == GAME_RUNNING && !isTransitioning)
            currentX += 0.1f;
        break;
    case ' ':
        if (gameState == GAME_RUNNING && !isJumping)
        {
            isJumping = true;
            velocityY = jumpStrength;
            glutTimerFunc(16, [](int)
                          { updateJump(); }, 0);
        }
        break;
    case 'p':
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

    case 'z':
        if (gameState == GAME_RUNNING && canFire)
        {
            Projectile newProjectile;
            newProjectile.x = currentX;
            newProjectile.y = translateY;
            newProjectile.direction = 1.0f;
            newProjectile.active = true;
            projectiles.push_back(newProjectile);

            canFire = false;
            glutTimerFunc(FIRE_COOLDOWN, [](int)
                          { canFire = true; }, 0);

            // Start projectile updates if not already running
            if (projectiles.size() == 1)
            {
                glutTimerFunc(16, updatefire, 0); // Increased update frequency
            }
        }
        break;

    case 'k':
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
        drawText("Game Paused");
        drawText("Press 'p' to Resume");
        break;
    case GAME_OVER:
        drawText("Game Over!");
        snprintf(scoreText, sizeof(scoreText), "Final Score: %d", score);
        drawText(scoreText);
        drawText("Press 'r' to Restart or 'Esc' to Quit");
        break;
    case LEVEL_COMPLETE:
        drawCharacter();
        char levelText[100];
        snprintf(levelText, sizeof(levelText), "Level %d Complete! Score: %d", level, score);
        drawText(levelText);
        drawText("Press 'k' to continue");
        break;
    case GAME_WON:
        snprintf(scoreText, sizeof(scoreText), "Congratulations! Final Score: %d", score);
        drawText(scoreText);
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