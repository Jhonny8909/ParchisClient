#pragma once
#include "Ficha.hpp"
#include "resources.h"

class FichaVerde : public Ficha {
public:
    FichaVerde(int id, const sf::Vector2f& posicionInicial, GameResources& resources);
    void dibujar(sf::RenderWindow& ventana) const override;
};