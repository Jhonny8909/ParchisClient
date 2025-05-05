#pragma once
#include <SFML/Graphics.hpp>

class Ficha {
protected:
    sf::Sprite sprite;
    int id;
    int casillaActual = -1;  // -1: en casa
    bool enMeta = false;

public:
    Ficha(int id, const sf::Vector2f& posicionInicial);
    virtual ~Ficha() = default;

    // Métodos comunes
    void mover(const sf::Vector2f& nuevaPosicion);
    virtual void dibujar(sf::RenderWindow& ventana) const;
    bool puedeMoverse(int valorDado) const;

    // Getters
    int getCasillaActual() const { return casillaActual; }
    bool estaEnMeta() const { return enMeta; }
};