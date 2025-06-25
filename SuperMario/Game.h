#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "player.h"
#include "block.h"
#include "coin.h"
#include "mushroom.h"
#include "goomba.h"
#include "audioManager.h"
#include "World1-1.h"
#include <vector>

class Game {
public:
    Game();
    void Init();
    void Run();

private:
    int screenWidth;
    int screenHeight;

    GameState state;
    int lives;
    int previousLives;

    bool damageCooldown;
    float damageTimer;

    float deathTimer;
    bool deathTriggered;

    Camera2D camera;
    Player player;

    std::vector<Rectangle> platforms; // plataformas múltiples
    std::vector<Block> blocks;
    std::vector<CoinEffect> coins;
    std::vector<Mushroom> mushrooms;
    std::vector<Goomba> goombas;

    void HandleInput();
    void Update(float dt);
    void Draw();
};

#endif