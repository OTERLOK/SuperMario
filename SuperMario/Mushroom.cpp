#include "mushroom.h"

void Mushroom::Init(float x, float y) {
    rect = { x, y, 28, 28 };
    velocity = { 40.0f, 0.0f };
    active = true;
    emerging = true;
    riseDistance = 0.0f;
}

void Mushroom::Update(float dt, const Rectangle& ground) {
    if (!active) return;

    if (emerging) {
        rect.y -= 40 * dt;
        riseDistance += 40 * dt;
        if (riseDistance >= rect.height) {
            emerging = false;
        }
        return;
    }

    velocity.y += 500 * dt; // gravedad
    rect.x += velocity.x * dt;
    rect.y += velocity.y * dt;

    if (CheckCollisionRecs(rect, ground)) {
        rect.y = ground.y - rect.height;
        velocity.y = 0;
    }
}

void Mushroom::Draw() {
    if (active) {
        DrawRectangleRec(rect, RED);
    }
}