// Pantalla.h
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Pantalla {
public:
    virtual ~Pantalla() = default;
    virtual void handleInput(sf::RenderWindow& window) = 0;
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual std::string nextState() const = 0;
};