#ifndef GOOMBA_H
#define GOOMBA_H

#include "raylib.h"

class Goomba {
public:
    Rectangle rect;
    bool active;
    bool crushed;

    void Init(float x, float y);
    void Update(float dt, Rectangle ground);
    void Crush();
    void Draw();

private:
    Texture2D texture;
    Vector2 velocity;

    float gravity;
    float maxFallSpeed;

    int frame;
    float frameTimer;
    float frameTime;
    float crushTimer;
};

#endif