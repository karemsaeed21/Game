#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <cmath>
#include "enemy.h"

Enemy::Enemy(float x, float y, float speed) : x(x), y(y), speed(speed), rotation(0.0f),
                                              rotationSpeed(50.0f), isActive(true), isFalling(false), hasPassed(false), health(2) {}

void Head()
{
  glBegin(GL_QUADS); // Start drawing quads
  glColor3f(0.447f, 0.651f, 0.400f);
  glVertex2f(-0.1f, 0.2f); // Adjusted y from 0.4f to 0.2f
  glVertex2f(0.1f, 0.2f);  // Adjusted y from 0.4f to 0.2f
  glVertex2f(0.1f, 0.0f);  // Adjusted y from 0.2f to 0.0f
  glVertex2f(-0.1f, 0.0f); // Adjusted y from 0.2f to 0.0f
  glEnd();                 // End drawing quads

  glLineWidth(2.0f);
  glBegin(GL_LINE_LOOP);
  glColor3f(0.247f, 0.251f, 0.100f); // Stroke color (black)
  glVertex2f(-0.1f, 0.2f);           // Adjusted y from 0.4f to 0.2f
  glVertex2f(0.1f, 0.2f);            // Adjusted y from 0.4f to 0.2f
  glVertex2f(0.1f, 0.0f);            // Adjusted y from 0.2f to 0.0f
  glVertex2f(-0.1f, 0.0f);           // Adjusted y from 0.2f to 0.0f
  glEnd();
}
void Face()
{

  glBegin(GL_QUADS);
  // hsl(95, 90%, 12%)
  glColor3f(0.063f, 0.228f, 0.006f); // Green color
  glVertex2f(-0.07f, 0.16f);         // M1
  glVertex2f(-0.02f, 0.16f);         // N1
  glVertex2f(-0.02f, 0.11f);         // O1
  glVertex2f(-0.07f, 0.11f);         // P1
  glEnd();

  glBegin(GL_QUADS);
  glColor3f(0.063f, 0.228f, 0.006f); // Blue color
  glVertex2f(0.02f, 0.16f);          // M
  glVertex2f(0.07f, 0.16f);          // N
  glVertex2f(0.07f, 0.11f);          // O
  glVertex2f(0.02f, 0.11f);          // P
  glEnd();

  glBegin(GL_QUADS);
  glColor3f(0.063f, 0.228f, 0.006f); // Blue color
  glVertex2f(-0.02f, 0.11f);         // O1
  glVertex2f(0.02f, 0.11f);          // P
  glVertex2f(0.02f, 0.07f);          // U
  glVertex2f(-0.02f, 0.07f);         // V

  glEnd();

  glBegin(GL_QUADS);
  glColor3f(0.063f, 0.228f, 0.006f); // Blue color
  glVertex2f(0.02f, 0.09f);          // Q
  glVertex2f(0.04f, 0.09f);          // R
  glVertex2f(0.04f, 0.04f);          // S
  glVertex2f(0.02f, 0.04f);          // T

  glEnd();

  glBegin(GL_QUADS);
  glColor3f(0.063f, 0.228f, 0.006f); // Blue color
  glVertex2f(-0.04f, 0.09f);         // A1
  glVertex2f(-0.02f, 0.09f);         // B1
  glVertex2f(-0.02f, 0.04f);         // W
  glVertex2f(-0.04f, 0.04f);         // Z

  glEnd();
}

void Body()
{
  glBegin(GL_QUADS);
  glColor3f(0.447f, 0.651f, 0.400f);
  glVertex2f(-0.07f, 0.0f);  // Adjusted y from 0.2f to 0.0f
  glVertex2f(0.07f, 0.0f);   // Adjusted y from 0.2f to 0.0f
  glVertex2f(0.07f, -0.4f);  // Adjusted y from -0.2f to -0.4f
  glVertex2f(-0.07f, -0.4f); // Adjusted y from -0.2f to -0.4f
  glEnd();

  glLineWidth(2.0f);
  glBegin(GL_LINE_LOOP);
  glColor3f(0.247f, 0.251f, 0.100f); // Stroke color (black)
  glVertex2f(-0.07f, 0.0f);          // x, y
  glVertex2f(0.07f, 0.0f);
  glVertex2f(0.07f, -0.4f);
  glVertex2f(-0.07f, -0.4f);
  glEnd();
}
void LeftLeg()
{
  glBegin(GL_QUADS);
  glColor3f(0.447f, 0.651f, 0.400f);
  glVertex2f(-0.1f, -0.38f); // Adjusted y from -0.18f to -0.38f
  glVertex2f(0.0f, -0.38f);  // Adjusted y from -0.18f to -0.38f
  glVertex2f(0.0f, -0.54f);  // Adjusted y from -0.34f to -0.54f
  glVertex2f(-0.1f, -0.54f); // Adjusted y from -0.34f to -0.54f

  glEnd();

  glBegin(GL_QUADS);
  glColor3f(0.063f, 0.228f, 0.006f);
  glVertex2f(-0.1f, -0.48f); // Adjusted y from -0.28f to -0.48f
  glVertex2f(-0.08f, -0.48f);
  glVertex2f(-0.08f, -0.54f);
  glVertex2f(-0.1f, -0.54f);
  glEnd();

  glLineWidth(2.0f);
  glBegin(GL_LINE_LOOP);
  glColor3f(0.247f, 0.251f, 0.100f); // Stroke color (black)
  glVertex2f(-0.1f, -0.38f);         // x, y
  glVertex2f(0.0f, -0.38f);
  glVertex2f(0.0f, -0.54f);
  glVertex2f(-0.1f, -0.54f);
  glEnd();
}
void RightLeg()
{
  glBegin(GL_QUADS);
  glColor3f(0.447f, 0.651f, 0.400f);
  glVertex2f(0.1f, -0.38f); // Adjusted y from -0.18f to -0.38f
  glVertex2f(0.0f, -0.38f); // Adjusted y from -0.18f to -0.38f
  glVertex2f(0.0f, -0.54f); // Adjusted y from -0.34f to -0.54f
  glVertex2f(0.1f, -0.54f); // Adjusted y from -0.34f to -0.54f
  glEnd();

  glBegin(GL_QUADS);
  glColor3f(0.063f, 0.228f, 0.006f);
  glVertex2f(0.08f, -0.48f); // Adjusted y from -0.28f to -0.48f
  glVertex2f(0.1f, -0.48f);  // Adjusted y from -0.28f to -0.48f
  glVertex2f(0.1f, -0.54f);  // Adjusted y from -0.34f to -0.54f
  glVertex2f(0.08f, -0.54f); // Adjusted y from -0.34f to -0.54f
  glEnd();

  glLineWidth(2.0f);
  glBegin(GL_LINE_LOOP);
  glColor3f(0.247f, 0.251f, 0.100f); // Stroke color (black)
  glVertex2f(0.1f, -0.38f);          // x, y
  glVertex2f(0.0f, -0.38f);
  glVertex2f(0.0f, -0.54f);
  glVertex2f(0.1f, -0.54f);
  glEnd();
}
void drawCreeper()
{
  Head();
  Face();

  Body();

  RightLeg();
  LeftLeg();
}
