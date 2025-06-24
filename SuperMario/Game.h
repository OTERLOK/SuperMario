#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "player.h"
#include "block.h"
#include "coin.h"
#include "mushroom.h"
#include "goomba.h"
#include "audioManager.h"
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

    Rectangle ground;

    Player player;
    Camera2D camera;

    std::vector<Block> blocks;
    std::vector<CoinEffect> coins;
    std::vector<Mushroom> mushrooms;
    std::vector<Goomba> goombas;

    void HandleInput();
    void Update(float dt);
    void Draw();
};

#endif