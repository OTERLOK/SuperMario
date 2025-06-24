#include "player.h"
#include "raylib.h"
#include "raymath.h"
#include "AudioManager.h"
#include <math.h>

#define MARIO_FRAME_WIDTH 18
#define MARIO_FRAME_HEIGHT 16
#define MARIO_SCALE 2

void Player::LoadAssets() {
    texture = LoadTexture("C:/Users/OTERLOK/Desktop/mario/assets/sprites/characters/mario.png");
    frame = 0;
    frameTime = 0.12f;
    frameTimer = 0.0f;
    facingRight = true;
    isBig = false;

    // Inicializar físicas
    gravity = 1300.0f;
    jumpForce = 500.0f;
    moveSpeed = 200.0f;
    deceleration = 0.0f;
    maxFallSpeed = 900.0f;
    jumpCutFactor = 0.35f;
    jumpHeld = false;
}

void Player::SpawnSobre(Rectangle ground, int screenWidth) {
    LoadAssets();
    rect.width = MARIO_FRAME_WIDTH * MARIO_SCALE;
    rect.height = MARIO_FRAME_HEIGHT * MARIO_SCALE;
    rect.x = screenWidth / 2.0f - rect.width / 2.0f;
    rect.y = ground.y - rect.height;
    velocity = { 0, 0 };
    onGround = true;
}

void Player::Grow() {
    if (!isBig) {
        isBig = true;
        rect.height *= 1.5f;
        rect.y -= rect.height * 0.3f;
    }
}

void Player::Update(float dt, Rectangle ground) {
    // Movimiento horizontal
    if (IsKeyDown(KEY_RIGHT)) {
        velocity.x = moveSpeed;
        facingRight = true;
    }
    else if (IsKeyDown(KEY_LEFT)) {
        velocity.x = -moveSpeed;
        facingRight = false;
    }
    else {velocity.x = 0.0f;
       
    }

    // Salto
   // Salto NES: cuanto más mantienes, más alto sube
    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP)) && onGround) {
        velocity.y = -jumpForce;      // Impulso hacia arriba
        jumpHeld = true;              // Se marcó que está en salto largo
        onGround = false;
        PlayJumpSound();
    }

    // Cortar salto si suelta la tecla mientras sube
    if (!IsKeyDown(KEY_SPACE) && !IsKeyDown(KEY_UP) && jumpHeld && velocity.y < 0) {
        velocity.y *= jumpCutFactor;  // Recorte brusco de altura
        jumpHeld = false;
    }


    // Aplicar gravedad
    velocity.y += gravity * dt;
    if (velocity.y > maxFallSpeed) velocity.y = maxFallSpeed;

    // Actualizar posición
    rect.x += velocity.x * dt;
    rect.y += velocity.y * dt;

    // Colisión con el suelo
    if (rect.y + rect.height >= ground.y) {
        rect.y = ground.y - rect.height;
        velocity.y = 0;
        onGround = true;
    }
    else {
        onGround = false;
    }

    UpdateAnimation(dt);
}

void Player::UpdateAnimation(float dt) {
    if (rect.y > 1000) {
        frame = 4;
        return;
    }

    if (!onGround) {
        frame = 5;
        return;
    }

    if (fabs(velocity.x) > 10.0f) {
        frameTimer += dt;
        if (frameTimer >= frameTime) {
            frame = (frame % 3) + 1;
            frameTimer = 0.0f;
        }
        return;
    }

    frame = 0;
    frameTimer = 0.0f;
}

void Player::Draw() {
    int drawFrame = frame;
    if (drawFrame < 0 || drawFrame > 5) drawFrame = 0;

    Rectangle src = {
        (float)(drawFrame * MARIO_FRAME_WIDTH),
        0,
        (float)(facingRight ? MARIO_FRAME_WIDTH : -MARIO_FRAME_WIDTH),
        (float)MARIO_FRAME_HEIGHT
    };

    if (!facingRight) {
        src.x = (drawFrame + 0) * MARIO_FRAME_WIDTH;
    }

    Rectangle dest = {
        rect.x,
        rect.y,
        rect.width,
        rect.height
    };

    DrawTexturePro(texture, src, dest, Vector2{ 0, 0 }, 0.0f, WHITE);
}