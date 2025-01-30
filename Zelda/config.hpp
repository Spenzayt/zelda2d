#ifndef CONFIG_H
#define CONFIG_H

#include <SFML/Graphics.hpp>

namespace Config {
    const float TILE_SIZE = 32.f;

    const float TREE_SIZE_X = 64.f;
    const float TREE_SIZE_Y = 128.f;

    const unsigned int WINDOW_WIDTH = 1920;
    const unsigned int WINDOW_HEIGHT = 1080;

    const float PLAYER_SPEED = 200.f;

    const std::string TEXTURE_PATH = "assets/map/textures/";
}

#endif // CONFIG_H