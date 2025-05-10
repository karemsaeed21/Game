// // character.h
// #ifndef ENEMY_H
// #define ENEMY_H

// void Head();
// void Face();
// void Body();

// void RightLeg();
// void LeftLeg();
// void drawCreeper();
// // struct Enemy
// // {
// //     float x, y;
// //     bool isVisible;
// //     Enemy(float startX, float startY) : x(startX), y(startY), isVisible(true) {}
// // };
// struct Enemy
// {
//     float x, y;
//     float speed;
// };
// #endif
// character.h
#ifndef ENEMY_H
#define ENEMY_H

void Head();
void Face();
void Body();

void RightLeg();
void LeftLeg();
void drawCreeper();

class Enemy
{
public:
    float x;
    float y;
    float speed;
    float rotation;
    float rotationSpeed; // Add rotation speed
    bool isActive;
    bool isFalling;
    bool hasPassed;

    Enemy(float x, float y, float speed);
};

#endif