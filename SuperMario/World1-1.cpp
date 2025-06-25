#include "world1-1.h"
#include <fstream>
#include <sstream>
#include <string>

std::vector<std::vector<int>> LeerCSV(const char* ruta) {
    std::ifstream archivo(ruta);
    std::vector<std::vector<int>> datos;
    std::string linea;

    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string celda;
        std::vector<int> fila;
        while (std::getline(ss, celda, ',')) {
            fila.push_back(std::stoi(celda));
        }
        datos.push_back(fila);
    }

    return datos;
}

void CargarLevelProperties(const char* ruta, Vector2& playerStart, Vector2& cameraStart, Color& backgroundColor) {
    std::ifstream archivo(ruta);
    std::string linea;

    while (std::getline(archivo, linea)) {
        if (linea.find("PLAYER_START") != std::string::npos) {
            int x, y;
            sscanf_s(linea.c_str(), "PLAYER_START = (%d, %d)", &x, &y);
            playerStart = Vector2{ (float)x * 32, (float)y * 32 };
        }
        if (linea.find("CAMERA_START") != std::string::npos) {
            int x, y;
            sscanf_s(linea.c_str(), "CAMERA_START = (%d, %d)", &x, &y);
            cameraStart = Vector2{ (float)x * 32, (float)y * 32 };
        }
        if (linea.find("BACKGROUND_COLOR") != std::string::npos) {
            if (linea.find("BLUE") != std::string::npos) backgroundColor = BLUE;
            else if (linea.find("BLACK") != std::string::npos) backgroundColor = BLACK;
            else backgroundColor = RAYWHITE;
        }
    }
}

void CargarWorld1_1(
    std::vector<Rectangle>& platforms,
    std::vector<Block>& blocks,
    std::vector<Goomba>& goombas,
    std::vector<Mushroom>& mushrooms,
    std::vector<CoinEffect>& coins,
    Vector2& playerStart,
    Vector2& cameraStart,
    Color& backgroundColor
) {
    int tileSize = 32;

    auto foreground = LeerCSV("C:/Users/OTERLOK/Desktop/mario/assets/data/World1-1/World1-1_Foreground.csv");
    auto enemigos = LeerCSV("C:/Users/OTERLOK/Desktop/mario/assets/data/World1-1/World1-1_Enemies.csv");
    auto items = LeerCSV("C:/Users/OTERLOK/Desktop/mario/assets/data/World1-1/World1-1_Collectibles.csv");

    for (int y = 0; y < foreground.size(); y++) {
        for (int x = 0; x < foreground[y].size(); x++) {
            int id = foreground[y][x];

            // El bloque suelo (floor) (id 384)
            if (id == 384) {
                Block b;
                b.Init(x * tileSize, y * tileSize, FLOOR);
                blocks.push_back(b);
                platforms.push_back(b.rect); // para colisión
            }
        }
    }

    for (int y = 0; y < enemigos.size(); y++) {
        for (int x = 0; x < enemigos[y].size(); x++) {
            if (enemigos[y][x] == 1) {
                Goomba g;
                g.Init(x * tileSize, y * tileSize);
                goombas.push_back(g);
            }
        }
    }

    for (int y = 0; y < items.size(); y++) {
    for (int x = 0; x < items[y].size(); x++) {
        int id = items[y][x];

        Block b;

        if (id == 144) {
            b.Init(x * tileSize, y * tileSize, COIN);
        }
        else if (id == 608) {
            b.Init(x * tileSize, y * tileSize, POWERUP);
        }
        else if (id == 303) {
            b.Init(x * tileSize, y * tileSize, MYSTERY);
        }
        else {
            continue; // si no coincide con ningún tipo conocido, se salta
        }

        blocks.push_back(b);
        platforms.push_back(b.rect); // para que tenga colisión
    }
}

    CargarLevelProperties("C:/Users/OTERLOK/Desktop/mario/assets/data/World1-1/World1-1.levelproperties", playerStart, cameraStart, backgroundColor);
}