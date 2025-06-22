#include "block.h"

void Block::Init(float x, float y, BlockType t) {
    rect = { x, y, 32, 32 };
    originalY = y;
    type = t;
    active = true;
    hit = false;
    bounceOffset = 0.0f;
    bounceSpeed = 0.0f;
}

void Block::OnHit(std::vector<CoinEffect>& coins, std::vector<Mushroom>& mushrooms) {
    if (!hit && active) {
        hit = true;
        bounceSpeed = -100.0f;

        if (type == COIN) {
            CoinEffect c;
            c.Init(rect.x + rect.width / 2, rect.y);
            coins.push_back(c);
        }

        if (type == POWERUP) {
            Mushroom m;
            m.Init(rect.x + rect.width / 2 - 14, rect.y);
            mushrooms.push_back(m);
        }
    }
}

void Block::Update(float dt) {
    if (hit && bounceOffset < 8.0f) {
        bounceOffset += bounceSpeed * dt;
        rect.y += bounceSpeed * dt;

        if (bounceOffset <= -8.0f) bounceSpeed = 100.0f;
        if (bounceOffset >= 0.0f) {
            rect.y = originalY;
            bounceOffset = 0.0f;
            bounceSpeed = 0.0f;
        }
    }
}

void Block::Draw() {
    Color color = (type == COIN) ? YELLOW : ORANGE;
    if (hit) color = LIGHTGRAY;
    DrawRectangleRec(rect, color);
}