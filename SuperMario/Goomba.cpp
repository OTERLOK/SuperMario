#include "goomba.h"

void Goomba::Init(float x, float y) {
    rect = { x, y, 28, 28 };
    velocity = { -40.0f, 0.0f }; // se mueve a la izquierda por defecto
    active = true;
}

void Goomba::Update(float dt, const Rectangle& ground) {
    if (!active) return;

    velocity.y += 500 * dt; // gravedad
    rect.x += velocity.x * dt;
    rect.y += velocity.y * dt;

    // Colisión con el suelo
    if (CheckCollisionRecs(rect, ground)) {
        rect.y = ground.y - rect.height;
        velocity.y = 0;
    }

    // Rebote en los bordes del suelo
    if (rect.x <= ground.x || rect.x + rect.width >= ground.x + ground.width) {
        velocity.x *= -1;
    }
}

void Goomba::Draw() {
    if (active) {
        DrawRectangleRec(rect, BROWN);
    }
}