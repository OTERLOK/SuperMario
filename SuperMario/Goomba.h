#ifndef GOOMBA_H
#define GOOMBA_H

#include "raylib.h"
#include <vector>

class Goomba {
public:
    Rectangle rect;
    bool active;
    bool crushed;

    void Init(float x, float y);
    void Update(float dt, std::vector<Rectangle>& platforms);
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