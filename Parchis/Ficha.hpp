#pragma once
#include <SFML/Graphics.hpp>

class Ficha {
public:
    sf::Sprite sprite;
    int id;
    int casillaActual = -1; // -1 = en casa
    bool enMeta = false;

    void mover(int pasos, const std::vector<sf::Vector2f>& camino);
};