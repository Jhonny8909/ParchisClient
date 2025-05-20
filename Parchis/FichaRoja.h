#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "resources.h"

class FichaRoja {
protected:
    sf::Sprite sprite;
    int id;
    int indiceTablero = -1;  // -1: en casa
    bool enMeta = false;
    bool seleccionada = false;
    float radio;
    GameResources& resources;

public:
    FichaRoja(int id, const sf::Vector2f& posicionInicial, GameResources& res);

    void mover(const sf::Vector2f& nuevaPosicion);
    void moverEnTablero(int nuevoIndice, const std::array<sf::Vector2f, 40>& positions);
    void dibujar(sf::RenderWindow& ventana) const;
    bool puedeMoverse(int valorDado) const;
    bool contienePunto(const sf::Vector2i& punto) const;
    void seleccionar();
    void deseleccionar();
    bool estaSeleccionada() const { return seleccionada; }
    int getIndiceTablero() const { return indiceTablero; }
    void setIndiceTablero(int indice) { indiceTablero = indice; }
    bool estaEnMeta() const { return enMeta; }
};