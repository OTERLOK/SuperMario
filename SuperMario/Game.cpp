#include "Game.h"

Game::Game() {
    screenWidth = 800;
    screenHeight = 450;
    state = MENU;
    deathTimer = 0.0f;
    deathTriggered = false;
}

void Game::Init() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Super Mario - Modular");
    InitAudioManager();
    SetMusicState(state);
    SetTargetFPS(60);

    ground = { 0, 400, 1600, 50 };

    player.isBig = false;
    player.SpawnSobre(ground, screenWidth);

    camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
    camera.zoom = 1.0f;

    lives = 3;
    previousLives = lives;
    damageCooldown = false;
    damageTimer = 0.0f;

    blocks.push_back(Block()); blocks.back().Init(250, 280, COIN);
    blocks.push_back(Block()); blocks.back().Init(300, 280, POWERUP);
    blocks.push_back(Block()); blocks.back().Init(350, 280, MYSTERY);

    goombas.push_back(Goomba()); goombas.back().Init(500, ground.y - 28);
}

void Game::Run() {
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        UpdateMusic();
        HandleInput();
        Update(dt);
        Draw();
    }

    UnloadAudioManager();
    CloseWindow();
}

void Game::HandleInput() {
    if (state == MENU && IsKeyPressed(KEY_ENTER)) {
        state = PLAYING;
        SetMusicState(state);
    }
    else if (state == PLAYING && IsKeyPressed(KEY_P)) {
        state = PAUSED;
    }
    else if (state == PAUSED && IsKeyPressed(KEY_P)) {
        state = PLAYING;
    }
}

void Game::Update(float dt) {
    if (state != PLAYING) return;

    if (player.isDead) {
        deathTimer += dt;
        player.Update(dt, ground);

        if (deathTimer >= 2.0f && !deathTriggered) {
            state = GAME_OVER;
            SetMusicState(state);
            deathTriggered = true;
        }
        return;
    }

    player.Update(dt, ground);

    for (Block& b : blocks) {
        b.Update(dt);
        if (!b.hit && CheckCollisionRecs(player.rect, b.rect)) {
            if (player.velocity.y < 0 && player.rect.y < b.rect.y + b.rect.height) {
                b.OnHit(coins, mushrooms);
                (b.type == COIN) ? PlayCoinSound() : PlayPowerupAppearSound();
                player.velocity.y = 0;
            }
        }
    }

    for (CoinEffect& c : coins) c.Update(dt);
    for (Mushroom& m : mushrooms) {
        m.Update(dt, ground);
        if (m.active && CheckCollisionRecs(player.rect, m.rect)) {
            m.active = false;
            player.Grow();
            PlayPowerupCollectSound();
        }
    }

    for (Goomba& g : goombas) g.Update(dt, ground);

    if (!damageCooldown) {
        for (Goomba& g : goombas) {
            if (!g.active) continue;

            if (CheckCollisionRecs(player.rect, g.rect)) {
                if (player.velocity.y > 0 &&
                    player.rect.y + player.rect.height <= g.rect.y + 10) {
                    player.velocity.y = -300;
                    g.active = false;
                    PlayKickSound();
                }
                else {
                    if (player.isBig) {
                        player.Shrink();

                    }
                    else {
                        lives--;
                        if (lives == 0) {
                            player.Die();
                            deathTimer = 0.0f;
                            deathTriggered = false;
                        }
                    }
                    damageCooldown = true;
                    damageTimer = 0.0f;
                }
                break;
            }
        }
    }
    else {
        damageTimer += dt;
        if (damageTimer > 1.0f) {
            damageCooldown = false;
            damageTimer = 0.0f;
        }
    }

    if (lives > 0 && lives < previousLives) {
        player.SpawnSobre(ground, screenWidth);
    }

    previousLives = lives;

    Vector2 target = {
        player.rect.x + player.rect.width / 2,
        player.rect.y + player.rect.height / 2
    };
    camera.target.x += (target.x - camera.target.x) * 0.1f;
    camera.target.y += (target.y - camera.target.y) * 0.1f;
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (state == MENU) {
        DrawText("SUPER MARIO BROS", 180, 140, 40, RED);
        DrawText("Presiona ENTER para comenzar", 200, 220, 20, DARKGRAY);
    }
    else {
        BeginMode2D(camera);
        DrawRectangleRec(ground, DARKGRAY);
        player.Draw();
        for (Block& b : blocks) b.Draw();
        for (CoinEffect& c : coins) c.Draw();
        for (Mushroom& m : mushrooms) m.Draw();
        for (Goomba& g : goombas) g.Draw();
        EndMode2D();

        DrawText(TextFormat("Vidas: %d", lives), 20, 20, 20, DARKGRAY);
        if (state == PAUSED)    DrawText("PAUSA", 340, 180, 40, GRAY);
        if (state == GAME_OVER) DrawText("GAME OVER", 250, 200, 50, RED);
    }

    EndDrawing();
}