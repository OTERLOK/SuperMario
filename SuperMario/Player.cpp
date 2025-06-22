#include "player.h"
#include "raylib.h"
#include "audioManager.h"

void Player::Init(float x, float y, float w, float h) {
    rect = { x, y, w, h };
    velocity = { 0, 0 };
    isOnGround = true;
    isBig = false;
}

void Player::SpawnSobre(const Rectangle& suelo, int screenWidth) {
    float w = isBig ? 48.0f : 32.0f;
    float h = isBig ? 48.0f : 32.0f;
    float x = screenWidth / 2.0f - w / 2.0f;
    float y = suelo.y - h;
    Init(x, y, w, h);
}

void Player::Update(float dt, const Rectangle& ground, float gravity, float jumpForce, float moveSpeed) {
    velocity.x = 0;
    if (IsKeyDown(KEY_RIGHT)) velocity.x = moveSpeed;
    if (IsKeyDown(KEY_LEFT)) velocity.x = -moveSpeed;

    velocity.y += gravity * dt;

    if (IsKeyPressed(KEY_SPACE) && isOnGround) {
        PlayJumpSound();
        velocity.y = jumpForce;
        isOnGround = false;
    }

    rect.x += velocity.x * dt;
    rect.y += velocity.y * dt;

    if (CheckCollisionRecs(rect, ground)) {
        rect.y = ground.y - rect.height;
        velocity.y = 0;
        isOnGround = true;
    }
    else {
        isOnGround = false;
    }
}

void Player::Grow() {
    if (!isBig) {
        isBig = true;
        rect.y -= 16;
        rect.width = 48.0f;
        rect.height = 48.0f;
        PlayPowerupCollectSound(); // ← ¡Este sonido debe estar aquí!
    }
}


void Player::Shrink() {
    if (isBig) {
        isBig = false;
        rect.y += 16;
        rect.width = 32.0f;
        rect.height = 32.0f;
    }
}

void Player::Draw() {
    DrawRectangleRec(rect, isBig ? BLUE : RED);
}