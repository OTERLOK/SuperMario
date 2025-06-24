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

    static void LoadSprite();    // Carga la textura de la moneda
    static void UnloadSprite();  // Libera la textura al cerrar
private:
    static Texture2D texture;
    static bool loaded;
    int frame;
    float frameTimer;
};

#endif