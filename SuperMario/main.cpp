#include "raylib.h"
#include "block.h"
#include "coin.h"
#include "mushroom.h"
#include "goomba.h"
#include "enemyLogic.h"
#include "player.h"
#include "audioManager.h"
#include <vector>

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Super Mario - Con Audio");
    InitAudioManager();
    SetTargetFPS(60);

    const float gravity = 500.0f;
    const float jumpForce = -300.0f;
    const float moveSpeed = 200.0f;

    Rectangle ground = { 0, 400, 1600, 50 };

    Player player;
    player.isBig = false;
    player.SpawnSobre(ground, screenWidth);

    Camera2D camera = { 0 };
    camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
    camera.zoom = 1.0f;

    int lives = 3;
    bool gameOver = false;

    // Cooldown de daño
    bool damageCooldownActive = false;
    float damageTimer = 0.0f;

    std::vector<Block> blocks;
    std::vector<CoinEffect> coins;
    std::vector<Mushroom> mushrooms;
    std::vector<Goomba> goombas;

    Block b1;
    b1.Init(250, 280, COIN);
    blocks.push_back(b1);

    Block b2;
    b2.Init(300, 280, POWERUP);
    blocks.push_back(b2);

    Goomba g;
    g.Init(500, ground.y - 28);
    goombas.push_back(g);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (!gameOver) {
            player.Update(dt, ground, gravity, jumpForce, moveSpeed);

            for (Block& b : blocks) {
                b.Update(dt);
                if (!b.hit && CheckCollisionRecs(player.rect, b.rect)) {
                    if (player.velocity.y < 0 && player.rect.y < b.rect.y + b.rect.height) {
                        b.OnHit(coins, mushrooms);
                        if (b.type == COIN) {
                            PlayCoinSound();
                        }
                        else if (b.type == POWERUP) {
                            PlayPowerupAppearSound();
                        }
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
                }
            }

            for (Goomba& g : goombas) g.Update(dt, ground);

            // Colisiones con Goomba con cooldown
            if (!damageCooldownActive) {
                for (Goomba& g : goombas) {
                    if (!g.active) continue;

                    if (CheckCollisionRecs(player.rect, g.rect)) {
                        if (player.velocity.y > 0 && player.rect.y + player.rect.height <= g.rect.y + 10) {
                            player.velocity.y = jumpForce;
                            g.active = false;
                        }
                        else {
                            if (player.isBig) {
                                player.isBig = false;
                            }
                            else {
                                lives--;
                                if (lives == 0) PlayDeathSound();
                            }
                            damageCooldownActive = true;
                            damageTimer = 0.0f;
                        }
                        break;
                    }
                }
            }
            else {
                damageTimer += dt;
                if (damageTimer > 1.0f) {
                    damageCooldownActive = false;
                    damageTimer = 0.0f;
                }
            }

            if (lives <= 0 && !gameOver) {
                gameOver = true;
            }
            static int previousLives = lives;

            if (lives <= 0 && !gameOver) {
                gameOver = true;
            }
            else if (lives < previousLives) {
                player.SpawnSobre(ground, screenWidth); // solo si perdió una vida completa
            }

            previousLives = lives;


        }

        Vector2 target = { player.rect.x + player.rect.width / 2, player.rect.y + player.rect.height / 2 };
        camera.target.x += (target.x - camera.target.x) * 0.1f;
        camera.target.y += (target.y - camera.target.y) * 0.1f;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);
        DrawRectangleRec(ground, DARKGRAY);
        player.Draw();

        for (Block& b : blocks) b.Draw();
        for (CoinEffect& c : coins) c.Draw();
        for (Mushroom& m : mushrooms) m.Draw();
        for (Goomba& g : goombas) g.Draw();
        EndMode2D();

        DrawText(TextFormat("Vidas: %d", lives), 20, 20, 20, DARKGRAY);
        if (gameOver) {
            DrawText("GAME OVER", screenWidth / 2 - 130, screenHeight / 2 - 20, 50, RED);
        }

        EndDrawing();
    }

    UnloadAudioManager();
    CloseWindow();
    return 0;
}