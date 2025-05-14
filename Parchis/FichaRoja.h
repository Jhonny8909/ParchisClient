#pragma once
#include <SFML/Graphics.hpp>
#include "resources.h"

class FichaRoja {
protected:
    sf::Sprite sprite;
    int id;
    int casillaActual = -1;  // -1: en casa
    bool enMeta = false;
    GameResources& resources;  // Referencia a recursos

public:
    FichaRoja(int id, const sf::Vector2f& posicionInicial, GameResources& res);
    virtual ~FichaRoja() = default;

    void mover(const sf::Vector2f& nuevaPosicion);
    virtual void dibujar(sf::RenderWindow& ventana) const;
    bool puedeMoverse(int valorDado) const;

    int getCasillaActual() const { return casillaActual; }
    bool estaEnMeta() const { return enMeta; }
};