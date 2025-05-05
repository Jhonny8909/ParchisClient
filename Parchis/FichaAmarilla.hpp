#pragma once
#include "Ficha.hpp"
#include "resources.h"

class FichaAmarilla : public Ficha {
public:
    FichaAmarilla(int id, const sf::Vector2f& posicionInicial, GameResources& resources);
    void dibujar(sf::RenderWindow& ventana) const override;
};