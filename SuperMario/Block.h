#ifndef BLOCK_H
#define BLOCK_H

#include "raylib.h"
#include "coin.h"
#include "mushroom.h"
#include <vector>

enum BlockType { EMPTY, COIN, POWERUP };

class Block {
public:
    Rectangle rect;
    BlockType type;
    bool active;
    bool hit;

    float bounceOffset;
    float bounceSpeed;
    float originalY;

    void Init(float x, float y, BlockType t);
    void OnHit(std::vector<CoinEffect>& coins, std::vector<Mushroom>& mushrooms);
    void Update(float dt);
    void Draw();
};

#endif