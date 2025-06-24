#include "coin.h"

Texture2D CoinEffect::texture = {};
bool CoinEffect::loaded = false;

void CoinEffect::LoadSprite() {
    if (!loaded) {
        texture = LoadTexture("C:/Users/OTERLOK/Desktop/mario/assets/sprites/collectibles/coin.png");
        loaded = true;

        if (texture.id == 0) {
            TraceLog(LOG_ERROR, "No se pudo cargar la textura de la moneda.");
        }
    }
}

void CoinEffect::UnloadSprite() {
    if (loaded) {
        UnloadTexture(texture);
        loaded = false;
    }
}

void CoinEffect::Init(float x, float y) {
    position = { x, y };
    lifetime = 0.5f;
    riseSpeed = 60.0f;
    active = true;
    frame = 0;
    frameTimer = 0.0f;

    LoadSprite(); // Asegura que la textura esté cargada
}

void CoinEffect::Update(float dt) {
    if (!active) return;

    position.y -= riseSpeed * dt;
    lifetime -= dt;

    frameTimer += dt;
    if (frameTimer >= 0.15f) {
        frame = (frame + 1) % 4;
        frameTimer = 0.0f;
    }

    if (lifetime <= 0.0f) {
        active = false;
    }
}

void CoinEffect::Draw() {
    if (!active) return;

    if (loaded) {
        Rectangle source = { 16.0f * frame, 0, 16, 16 };
        Rectangle dest = { position.x, position.y, 16, 16 };
        DrawTexturePro(texture, source, dest, { 0, 0 }, 0.0f, WHITE);
    }
    else {
        DrawCircleV(position, 6, GOLD); // fallback visual
    }
}