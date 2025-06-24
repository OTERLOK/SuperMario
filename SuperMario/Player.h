#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player {
public:
    Rectangle rect;
    Vector2 velocity;
    Vector2 acceleration;

    bool isBig;
    bool onGround;
    bool isDead; // Estado de muerte

    void LoadAssets();
    void SpawnSobre(Rectangle ground, int screenWidth);
    void Update(float dt, Rectangle ground);
    void Draw();
    void Grow();
    void Die(); // Ejecuta animación de muerte
    void Shrink();



private:
    Texture2D texture;
    int frame;
    float frameTime;
    float frameTimer;
    bool facingRight;

    // Físicas
    float gravity;
    float jumpForce;
    float moveSpeed;
    float deceleration;
    float maxFallSpeed;

    // Salto variable
    bool jumpHeld;
    float jumpCutFactor;

    void UpdateAnimation(float dt);
};

#endif