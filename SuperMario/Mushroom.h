#pragma once
#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "raylib.h"
#include <vector>

class Mushroom {
public:
    Rectangle rect;
    Vector2 velocity;
    bool active;
    bool emerging;
    float riseDistance;

    void Init(float x, float y);
    void Update(float dt, std::vector<Rectangle>& platforms);
    void Draw();

    static void LoadSprite();    // Carga la textura (una sola vez)
    static void UnloadSprite();  // Libera la textura al cerrar
private:
    static Texture2D texture;
    static bool loaded;
};

#endif