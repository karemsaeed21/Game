#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <cmath>
#include <vector>
#include "./cat.h"

#define PI 3.14159265358979323846

// the Main color of the cat
float catColorR = 0.6431f;
float catColorG = 0.6039f;
float catColorB = 0.5373f;

// draws a filled trianular area that is bounded on one side by a Bézier curve and on the other side by a line
// xL0, yL0: start point of the Bézier curve
// xL1, yL1: control point of the Bézier curve
// xL2, yL2: end point of the Bézier curve
// xTip, yTip: tip of the ear
// segments: number of segments to approximate the Bézier curve
void drawFilled(float xL0, float yL0, float xL1, float yL1, float xL2, float yL2, float xTip, float yTip, int segments = 100)
{
    float t; // Parameter for Bézier curve
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(catColorR, catColorG, catColorB); // Ear fill color (same as body)

    for (int i = 0; i <= segments; ++i)
    {
        t = (float)i / segments;
        // Bézier point on left curve
        // computes the position of the point on the curve at a specific t. This ensures the curve follows the shape defined by the points.
        float xCurve = (1 - t) * (1 - t) * xL0 + 2 * (1 - t) * t * xL1 + t * t * xL2;
        float yCurve = (1 - t) * (1 - t) * yL0 + 2 * (1 - t) * t * yL1 + t * t * yL2;
        // Line point between curve start and tip
        // computes the position of the point on the line between the start and tip points. This ensures the line follows a straight path.
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
        glVertex2f(cx, cy); // center of the circle

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
    // Left ear Bézier curve control points
    float xL0 = -0.2f, yL0 = 0.8f;
    float xL1 = -0.26f, yL1 = 0.62f;
    float xL2 = -0.26f, yL2 = 0.60f;

    // Line endpoint (tip of ear)
    float xTip = -0.12233f, yTip = 0.59843f;

    // Draw the filled ear using the Bézier curve and line
    // The function drawFilled is used to create the filled area between the Bézier curve and the line.
    drawFilled(xL0, yL0, xL1, yL1, xL2, yL2, xTip, yTip);

    // Right ear Bézier curve control points
    float xR0 = 0.2f, yR0 = 0.8f;
    float xR1 = 0.26f, yR1 = 0.62f;
    float xR2 = 0.26f, yR2 = 0.60f;

    // Line endpoint (tip of right ear)
    float xTip1 = 0.11565f, yTip1 = 0.59803f;

    drawFilled(xR0, yR0, xR1, yR1, xR2, yR2, xTip1, yTip1);
}

void draweyes()
{
    // Right Eye
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.16785f, 0.45472f);
    glVertex2f(0.1f, 0.4f);
    glVertex2f(0.16216f, 0.37008f);
    glEnd();
    // Left Eye
    drawCircle(-0.15789f, 0.39961f, 0.03703f, 72);
}

void drawFilledBody()
{
    const int segments = 100;
    float t;

    // Control points
    float xL0 = -0.26f, yL0 = 0.6f;
    float xL1 = -0.36f, yL1 = 0.1f;
    float xL2 = -0.3f, yL2 = -0.4f;

    float xR0 = 0.26f, yR0 = 0.6f;
    float xR1 = 0.36f, yR1 = 0.1f;
    float xR2 = 0.3f, yR2 = -0.4f;

    // Draw the bottom line of the body
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(catColorR, catColorG, catColorB); // Same color for the space

    for (int i = 0; i <= segments; ++i)
    {
        t = (float)i / segments;

        // Left curve point (same as before)
        float xL = (1 - t) * (1 - t) * xL0 + 2 * (1 - t) * t * xL1 + t * t * xL2;
        float yL = (1 - t) * (1 - t) * yL0 + 2 * (1 - t) * t * yL1 + t * t * yL2;

        // Right curve point (same as before)
        float xR = (1 - t) * (1 - t) * xR0 + 2 * (1 - t) * t * xR1 + t * t * xR2;
        float yR = (1 - t) * (1 - t) * yR0 + 2 * (1 - t) * t * yR1 + t * t * yR2;

        // Bottom line points
        float yBottom = -0.5f; // Bottom line y-coordinate

        // Add points in strip order, adding the bottom line coordinates
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
    // Line 1
    glVertex2f(-0.25036, 0.32677);
    glVertex2f(-0.33997, 0.35827);
    // Line 2
    glVertex2f(-0.24751, 0.37205);
    glVertex2f(-0.33713, 0.41142);
    // Line 3
    glVertex2f(0.25178, 0.32283);
    glVertex2f(0.34566, 0.3563);
    // Line 4
    glVertex2f(0.25178, 0.37008);
    glVertex2f(0.33997, 0.39961);
    glEnd();
}

void drawhands()
{
    int segments = 100; // number of line segments

    // Control points for the Bézier curve
    float P0_x = 0.17f, P0_y = 0.0f;
    float P1_x = 0.15f, P1_y = 0.05f;
    float P2_x = 0.17f, P2_y = 0.1f;
    drawQuadraticBezier(P0_x, P0_y, P1_x, P1_y, P2_x, P2_y, 100);

    // Control points for the Bézier curve
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

    // Control points for the Bézier curve (top of the tail)
    float P0_x = 0.3f, P0_y = -0.4f;
    float P1_x = 0.45f, P1_y = -0.35f;
    float P2_x = 0.6f, P2_y = -0.4f;

    // Line points (bottom of the tail)
    float L0_x = 0.3f, L0_y = -0.5f;
    float L1_x = 0.6f, L1_y = -0.5f;

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(catColorR, catColorG, catColorB); // Same as body color

    for (int i = 0; i <= segments; ++i)
    {
        t = (float)i / segments;

        // Point on the Bézier curve
        float xBezier = (1 - t) * (1 - t) * P0_x + 2 * (1 - t) * t * P1_x + t * t * P2_x;
        float yBezier = (1 - t) * (1 - t) * P0_y + 2 * (1 - t) * t * P1_y + t * t * P2_y;

        // Corresponding point on the bottom line
        float xLine = (1 - t) * L0_x + t * L1_x;
        float yLine = (1 - t) * L0_y + t * L1_y;

        glVertex2f(xBezier, yBezier); // Top point (curve)
        glVertex2f(xLine, yLine);     // Bottom point (line)
    }

    glEnd();
    drawArc(0.6f, -0.45f, 0.05f, 0.5 * PI, 1.5 * PI, true, .2549f, 0.2431f, 0.2196f, true); // leftward tail
}

void drawmouth()
{
    drawArc(0.05f, 0.27f, 0.05f, PI, 2 * PI, false, 0.2549f, 0.2431f, 0.2196f, false);
    drawArc(-0.05f, 0.27f, 0.05f, PI, 2 * PI, false, 0.2549f, 0.2431f, 0.2196f, false);
}

void drawfeet()
{
    drawArc(-0.31f, -0.451f, 0.05f, 1.5 * PI, 0.5 * PI, false, catColorR, catColorG, catColorB, true);
    drawArc(-0.31f, -0.451f, 0.05f, 1.5 * PI, 0.5 * PI, false, 0.0f, 0.0f, 0.0f, false); // rightward to add stroke
    drawArc(0.15f, -0.46f, 0.06f, 1.2 * PI, 2.1 * PI, true, 0.0f, 0.0f, 0.0f, false);    // leftward
}

void drawCat()
{
    drawFilledBody();
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
