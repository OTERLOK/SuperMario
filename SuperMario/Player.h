#ifndef PLAYER_H
#define PLAYER_H
#include "audioManager.h"
#include "raylib.h"

class Player {
public:
    Rectangle rect;
    Vector2 velocity;
    bool isOnGround;
    bool isBig;

    void Init(float x, float y, float w = 32, float h = 32);
    void SpawnSobre(const Rectangle& suelo, int screenWidth);
    void Update(float dt, const Rectangle& ground, float gravity, float jumpForce, float moveSpeed);
    void Grow();
    void Shrink();
    void Draw();
};

#endif