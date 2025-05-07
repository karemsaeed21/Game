// character.h
#ifndef ENEMY_H
#define ENEMY_H

void Head();
void Face();
void Body();

void RightLeg();
void LeftLeg();
void drawCreeper();
struct Enemy
{
    float x, y;
    bool isVisible;
    Enemy(float startX, float startY) : x(startX), y(startY), isVisible(true) {}
};
#endif