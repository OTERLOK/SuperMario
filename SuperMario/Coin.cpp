#include "coin.h"

void CoinEffect::Init(float x, float y) {
    position = { x, y };
    lifetime = 0.5f;
    riseSpeed = 60.0f;
    active = true;
}

void CoinEffect::Update(float dt) {
    if (!active) return;

    position.y -= riseSpeed * dt;
    lifetime -= dt;

    if (lifetime <= 0.0f) {
        active = false;
    }
}

void CoinEffect::Draw() {
    if (active) {
        DrawCircleV(position, 6, GOLD);
    }
}