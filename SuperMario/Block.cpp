#include "block.h"

Texture2D Block::mysteryTexture = {};
Texture2D Block::emptyTexture = {};
Texture2D Block::floorTexture = {};

bool Block::textureLoaded = false;
bool Block::emptyLoaded = false;
bool Block::floorLoaded = false;

void Block::LoadMysteryTexture() {
    if (!textureLoaded) {
        mysteryTexture = LoadTexture("C:/Users/OTERLOK/Desktop/mario/assets/sprites/blocks/overworld/misteryBlock.png");
        textureLoaded = true;
        if (mysteryTexture.id == 0) TraceLog(LOG_ERROR, "No se pudo cargar misteryBlock.png");
    }

    if (!emptyLoaded) {
        emptyTexture = LoadTexture("C:/Users/OTERLOK/Desktop/mario/assets/sprites/blocks/overworld/emptyBlock.png");
        emptyLoaded = true;
        if (emptyTexture.id == 0) TraceLog(LOG_ERROR, "No se pudo cargar emptyBlock.png");
    }

    if (!floorLoaded) {
        floorTexture = LoadTexture("C:/Users/OTERLOK/Desktop/mario/assets/sprites/scenery/overworld/floorbricks.png");
        floorLoaded = true;
        if (floorTexture.id == 0) TraceLog(LOG_ERROR, "No se pudo cargar block.png");
    }
}

void Block::UnloadMysteryTexture() {
    if (textureLoaded) {
        UnloadTexture(mysteryTexture);
        textureLoaded = false;
    }
    if (emptyLoaded) {
        UnloadTexture(emptyTexture);
        emptyLoaded = false;
    }
    if (floorLoaded) {
        UnloadTexture(floorTexture);
        floorLoaded = false;
    }
}

void Block::Init(float x, float y, BlockType t) {
    rect = { x, y, 32, 32 };
    originalY = y;
    type = t;
    active = true;
    hit = false;
    bounceOffset = 0.0f;
    bounceSpeed = 0.0f;

    animFrame = 0;
    animTimer = 0.0f;

    if (type == MYSTERY || type == COIN || type == POWERUP )
        LoadMysteryTexture();
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

        if (type == POWERUP || type == MYSTERY) {
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

    if ((type == MYSTERY || type == COIN || type == POWERUP) && !hit) {
        animTimer += dt;
        if (animTimer >= 0.2f) {
            animFrame = (animFrame + 1) % 3;
            animTimer = 0.0f;
        }
    }
}

void Block::Draw() {
    Rectangle dest = rect;

    if ((type == MYSTERY || type == COIN || type == POWERUP) && textureLoaded) {
        if (hit && emptyLoaded) {
            Rectangle src = { 0, 0, 16, 16 };
            DrawTexturePro(emptyTexture, src, dest, { 0, 0 }, 0.0f, WHITE);
        }
        else {
            Rectangle src = { 16.0f * animFrame, 0, 16, 16 };
            DrawTexturePro(mysteryTexture, src, dest, { 0, 0 }, 0.0f, WHITE);
        }
    }
    else if (type == FLOOR && floorLoaded) {
        Rectangle src = { 0, 0, 16, 16 };
        DrawTexturePro(floorTexture, src, dest, { 0, 0 }, 0.0f, WHITE);
    }
    else {
        Color color = (type == COIN) ? YELLOW : ORANGE;
        if (hit) color = LIGHTGRAY;
        DrawRectangleRec(dest, color);
    }
}