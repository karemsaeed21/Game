#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <cmath>
#include <vector>
#include "amoungus.h"

#ifndef M_PI
#endif

void DrawHalfCircle(float cx, float cy, float radius, int num_segments)
{
    glColor3f(0.9373f, 0.1412f, 0.1333f); // Red color
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++)
    {
        float theta = M_PI * (float)i / (float)num_segments;
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void DrawBag()
{
    glColor3f(0.9373f, 0.1412f, 0.1333f); // Red color
    glBegin(GL_POLYGON);
    glVertex2f(-0.3, 0.2);  // Top left
    glVertex2f(-0.2, 0.2);  // Top right
    glVertex2f(-0.2, -0.4); // Bottom right
    glVertex2f(-0.3, -0.4); // Bottom left
    glEnd();
}

void DrawBody()
{
    glColor3f(0.9373f, 0.1412f, 0.1333f); // Red color
    glBegin(GL_POLYGON);
    glVertex2f(-0.2f, 0.4f);
    glVertex2f(-0.2f, -0.6f);
    glVertex2f(-0.1f, -0.6f);
    glVertex2f(-0.1, -0.4);
    glVertex2f(0, -0.4);

    glVertex2f(0.1, -0.4);
    glVertex2f(0.1f, -0.6f);
    glVertex2f(0.2f, -0.6f);
    glVertex2f(0.2, 0.4);
    glEnd();
}

void Drawface()
{
    glColor3f(0.5137f, 0.5451f, 0.5137f);
    glBegin(GL_POLYGON);
    glVertex2f(0.2, 0.2f);
    glVertex2f(-0.06, 0.2);
    glVertex2f(-0.06, 0.4);
    glVertex2f(0.2596132300297, 0.400761584922);
    glVertex2f(0.2596132300297, 0.2004070683514);
    glVertex2f(0.2, 0.2);
    glEnd();
}

void DrawCharacter()
{
    DrawHalfCircle(0.0f, 0.4f, 0.2f, 50);
    DrawBody();
    DrawBag();
    Drawface();
}