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

    // Cargar el mundo 1-1 desde CSVs
    platforms.clear();
    blocks.clear();
    goombas.clear();
    mushrooms.clear();
    coins.clear();

    Vector2 playerStart;
    Vector2 cameraStart;
    Color backgroundColor;

    CargarWorld1_1(platforms, blocks, goombas, mushrooms, coins, playerStart, cameraStart, backgroundColor);

    player.isBig = false;
    player.SpawnSobre({ 0, playerStart.y + player.rect.height, 0, 0 }, screenWidth);

    camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
    camera.target = cameraStart;
    camera.zoom = 1.0f;

    lives = 3;
    previousLives = lives;
    damageCooldown = false;
    damageTimer = 0.0f;
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
        player.Update(dt, platforms);
        if (deathTimer >= 2.0f && !deathTriggered) {
            state = GAME_OVER;
            SetMusicState(state);
            deathTriggered = true;
        }
        return;
    }

    player.Update(dt, platforms);

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
        m.Update(dt, platforms);
        if (m.active && CheckCollisionRecs(player.rect, m.rect)) {
            m.active = false;
            player.Grow();
            PlayPowerupCollectSound();
        }
    }

    for (Goomba& g : goombas) g.Update(dt, platforms);

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
        player.SpawnSobre(platforms[0], screenWidth);
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
        for (const Rectangle& p : platforms) DrawRectangleRec(p, DARKGRAY);
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