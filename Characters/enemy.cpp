#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

void Head()
{
  glBegin(GL_QUADS); // Start drawing quads
  glColor3f(0.447f, 0.651f, 0.400f);
  glVertex2f(-0.1f, 0.6f); // x, y
  glVertex2f(0.1f, 0.6f);
  glVertex2f(0.1f, 0.4f);
  glVertex2f(-0.1f, 0.4f);
  glEnd(); // End drawing quads

  glLineWidth(2.0f);
  glBegin(GL_LINE_LOOP);
  glColor3f(0.247f, 0.251f, 0.100f); // Stroke color (black)
  glVertex2f(-0.1f, 0.6f);           // x, y
  glVertex2f(0.1f, 0.6f);
  glVertex2f(0.1f, 0.4f);
  glVertex2f(-0.1f, 0.4f);
  glEnd();
}
void Face()
{

  glBegin(GL_QUADS);
  // hsl(95, 90%, 12%)
  glColor3f(0.063f, 0.228f, 0.006f); // Green color
  glVertex2f(-0.07f, 0.56f);         // M1
  glVertex2f(-0.02f, 0.56f);         // N1
  glVertex2f(-0.02f, 0.51f);         // O1
  glVertex2f(-0.07f, 0.51f);         // P1
  glEnd();

  glBegin(GL_QUADS);
  glColor3f(0.063f, 0.228f, 0.006f); // Blue color
  glVertex2f(0.02f, 0.56f);          // M
  glVertex2f(0.07f, 0.56f);          // N
  glVertex2f(0.07f, 0.51f);          // O
  glVertex2f(0.02f, 0.51f);          // P
  glEnd();

  glBegin(GL_QUADS);
  glColor3f(0.063f, 0.228f, 0.006f); // Blue color
  glVertex2f(-0.02f, 0.51f);         // O1
  glVertex2f(0.02f, 0.51f);          // P
  glVertex2f(0.02f, 0.47f);          // U
  glVertex2f(-0.02f, 0.47f);         // V

  glEnd();

  glBegin(GL_QUADS);
  glColor3f(0.063f, 0.228f, 0.006f); // Blue color
  glVertex2f(0.02f, 0.49f);          // Q
  glVertex2f(0.04f, 0.49f);          // R
  glVertex2f(0.04f, 0.44f);          // S
  glVertex2f(0.02f, 0.44f);          // T

  glEnd();

  glBegin(GL_QUADS);
  glColor3f(0.063f, 0.228f, 0.006f); // Blue color
  glVertex2f(-0.04f, 0.49f);         // A1
  glVertex2f(-0.02f, 0.49f);         // B1
  glVertex2f(-0.02f, 0.44f);         // W
  glVertex2f(-0.04f, 0.44f);         // Z

  glEnd();
}

void Body()
{
  glBegin(GL_QUADS);
  glColor3f(0.447f, 0.651f, 0.400f);
  glVertex2f(-0.07f, 0.4f); // x, y
  glVertex2f(0.07f, 0.4f);
  glVertex2f(0.07f, 0.0f);
  glVertex2f(-0.07f, 0.0f);
  glEnd();

  glLineWidth(2.0f);
  glBegin(GL_LINE_LOOP);
  glColor3f(0.247f, 0.251f, 0.100f); // Stroke color (black)
  glVertex2f(-0.07f, 0.4f);          // x, y
  glVertex2f(0.07f, 0.4f);
  glVertex2f(0.07f, 0.0f);
  glVertex2f(-0.07f, 0.0f);
  glEnd();
}
void LeftLeg()
{
  glBegin(GL_QUADS);
  glColor3f(0.447f, 0.651f, 0.400f);
  glVertex2f(-0.1f, 0.02f); // x, y
  glVertex2f(0.0f, 0.02f);
  glVertex2f(0.0f, -0.14f);
  glVertex2f(-0.1f, -0.14f);

  glEnd();

  glBegin(GL_QUADS);
  glColor3f(0.063f, 0.228f, 0.006f);
  glVertex2f(-0.1f, -0.08f); // x, y
  glVertex2f(-0.08f, -0.08f);
  glVertex2f(-0.08f, -0.14f);
  glVertex2f(-0.1f, -0.14f);
  glEnd();

  glLineWidth(2.0f);
  glBegin(GL_LINE_LOOP);
  glColor3f(0.247f, 0.251f, 0.100f); // Stroke color (black)
  glVertex2f(-0.1f, 0.02f);          // x, y
  glVertex2f(0.0f, 0.02f);
  glVertex2f(0.0f, -0.14f);
  glVertex2f(-0.1f, -0.14f);
  glEnd();
}
void RightLeg()
{
  glBegin(GL_QUADS);
  glColor3f(0.447f, 0.651f, 0.400f);
  glVertex2f(0.1f, 0.02f); // x, y
  glVertex2f(0.0f, 0.02f);
  glVertex2f(0.0f, -0.14f);
  glVertex2f(0.1f, -0.14f);
  glEnd();

  glBegin(GL_QUADS);
  glColor3f(0.063f, 0.228f, 0.006f);
  glVertex2f(0.08f, -0.08f); // x, y
  glVertex2f(0.1f, -0.08f);
  glVertex2f(0.1f, -0.14f);
  glVertex2f(0.08f, -0.14f);
  glEnd();

  glLineWidth(2.0f);
  glBegin(GL_LINE_LOOP);
  glColor3f(0.247f, 0.251f, 0.100f); // Stroke color (black)
  glVertex2f(0.1f, 0.02f);           // x, y
  glVertex2f(0.0f, 0.02f);
  glVertex2f(0.0f, -0.14f);
  glVertex2f(0.1f, -0.14f);
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


