#include "goomba.h"
#include "raylib.h"

#define GOOMBA_FRAME_WIDTH 16
#define GOOMBA_FRAME_HEIGHT 16
#define GOOMBA_SCALE 2

void Goomba::Init(float x, float y) {
    texture = LoadTexture("C:/Users/OTERLOK/Desktop/mario/assets/sprites/characters/overworld/goomba.png");

    rect = {
        x,
        y,
        GOOMBA_FRAME_WIDTH * GOOMBA_SCALE,
        GOOMBA_FRAME_HEIGHT * GOOMBA_SCALE
    };

    velocity = { -40.0f, 0.0f }; // Comienza caminando a la izquierda
    gravity = 900.0f;
    maxFallSpeed = 700.0f;

    active = true;
    crushed = false;

    frame = 0;
    frameTime = 0.25f;
    frameTimer = 0.0f;
    crushTimer = 0.0f;
}

void Goomba::Update(float dt, Rectangle ground) {
    if (!active) return;

    if (crushed) {
        frame = 2;
        velocity.x = 0;
        crushTimer += dt;
        if (crushTimer >= 10.2f) active = false; // Dura más tiempo visible
        return;
    }

    // Movimiento horizontal
    rect.x += velocity.x * dt;

    // Cambia de dirección si choca con los bordes (opcional)
    // if (rect.x <= 0 || rect.x + rect.width >= GetScreenWidth()) {
    //     velocity.x *= -1;
    // }

    // Actualiza frame según dirección
    frameTimer += dt;
    if (frameTimer >= frameTime) {
        frame = (velocity.x < 0) ? 0 : 1;
        frameTimer = 0.0f;
    }

    // Gravedad
    velocity.y += gravity * dt;
    if (velocity.y > maxFallSpeed) velocity.y = maxFallSpeed;
    rect.y += velocity.y * dt;

    // Colisión con el suelo
    if (rect.y + rect.height >= ground.y) {
        rect.y = ground.y - rect.height;
        velocity.y = 0;
    }
}

void Goomba::Draw() {
    if (!active) return;

    Rectangle src = {
        (float)(frame * GOOMBA_FRAME_WIDTH),
        0,
        (float)GOOMBA_FRAME_WIDTH,
        (float)GOOMBA_FRAME_HEIGHT
    };

    Rectangle dest = {
        rect.x,
        rect.y,
        rect.width,
        rect.height
    };

    if (crushed && frame == 2) {
        dest.height *= 0.5f;
        dest.y += rect.height * 0.5f;
    }

    DrawTexturePro(texture, src, dest, Vector2{ 0, 0 }, 0.0f, WHITE);
}