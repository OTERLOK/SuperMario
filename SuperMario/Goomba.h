#pragma once
#ifndef GOOMBA_H
#define GOOMBA_H

#include "raylib.h"

class Goomba {
public:
    Rectangle rect;
    Vector2 velocity;
    bool active;

    void Init(float x, float y);
    void Update(float dt, const Rectangle& ground);
    void Draw();
};

#endif