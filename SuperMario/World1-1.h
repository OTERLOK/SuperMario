#ifndef WORLD1_1_H
#define WORLD1_1_H

#include "goomba.h"
#include "block.h"
#include "mushroom.h"
#include "coin.h"
#include <vector>
#include "raylib.h"

// Carga todo el contenido del mundo 1-1
void CargarWorld1_1(
    std::vector<Rectangle>& platforms,
    std::vector<Block>& blocks,
    std::vector<Goomba>& goombas,
    std::vector<Mushroom>& mushrooms,
    std::vector<CoinEffect>& coins,
    Vector2& playerStart,
    Vector2& cameraStart,
    Color& backgroundColor
);

#endif