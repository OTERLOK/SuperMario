#include "mushroom.h"

Texture2D Mushroom::texture = {};
bool Mushroom::loaded = false;

void Mushroom::LoadSprite() {
    if (!loaded) {
        texture = LoadTexture("C:/Users/OTERLOK/Desktop/mario/assets/sprites/collectibles/super-mushroom.png");
        loaded = true;

        if (texture.id == 0) {
            TraceLog(LOG_ERROR, "No se pudo cargar la textura del hongo.");
        }
    }
}

void Mushroom::UnloadSprite() {
    if (loaded) {
        UnloadTexture(texture);
        loaded = false;
    }
}

void Mushroom::Init(float x, float y) {
    rect = { x, y, 28, 28 };
    velocity = { 40.0f, 0.0f };
    active = true;
    emerging = true;
    riseDistance = 0.0f;

    LoadSprite(); //  se asegura de que la textura esté cargada
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
    if (!active) return;

    if (loaded) {
        DrawTexturePro(
            texture,
            { 0, 0, (float)texture.width, (float)texture.height },
            rect,
            { 0, 0 },
            0.0f,
            WHITE
        );
    }
    else {
        DrawRectangleRec(rect, RED); 
    }
}