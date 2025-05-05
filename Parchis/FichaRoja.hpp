#pragma once
#include "Ficha.hpp"
#include "resources.h"

class FichaRoja : public Ficha {
public:
    FichaRoja(int id, const sf::Vector2f& posicionInicial, GameResources& resources);
    void dibujar(sf::RenderWindow& ventana) const override;
};