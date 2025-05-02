#pragma once
// resources.h
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

struct GameResources {
    sf::Texture texture;
    sf::Texture texture2;
    sf::Texture texture3;
    sf::Font font;

    bool loadAllResources();
};