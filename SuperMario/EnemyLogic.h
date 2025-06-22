#ifndef ENEMY_LOGIC_H
#define ENEMY_LOGIC_H

#include <vector>
#include "goomba.h"
#include "raylib.h"

void handleGoombaCollisions(Rectangle& player, Vector2& velocity, bool& isBig, std::vector<Goomba>& goombas, float jumpForce, int& lives, bool& gameOver);

#endif