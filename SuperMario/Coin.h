#ifndef COIN_H
#define COIN_H

#include "raylib.h"

class CoinEffect {
public:
    Vector2 position;
    float lifetime;
    float riseSpeed;
    bool active;

    void Init(float x, float y);
    void Update(float dt);
    void Draw();
};

#endif