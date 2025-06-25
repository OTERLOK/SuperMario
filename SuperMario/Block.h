#ifndef BLOCK_H
#define BLOCK_H

#include "raylib.h"
#include "coin.h"
#include "mushroom.h"
#include <vector>

enum BlockType { EMPTY, COIN, POWERUP, MYSTERY ,FLOOR };

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

    static void LoadMysteryTexture();
    static void UnloadMysteryTexture();

private:
    static Texture2D mysteryTexture;
    static Texture2D emptyTexture;     
    static bool textureLoaded;
    static bool emptyLoaded;   
    static Texture2D floorTexture;
    static bool floorLoaded;

    int animFrame = 0;
    float animTimer = 0.0f;
};

#endif