// FichaRoja.h
#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "resources.h"
#include <iostream>

class FichaAzul {
protected:
    sf::Sprite sprite;
    int id;
    int indiceTablero = -1;  // -1: en casa
    bool enMeta = false;
    bool seleccionada = false;
    float radio;
    GameResources& resources;
    sf::Color colorOriginal; // Nuevo: para guardar el color base

public:
    FichaAzul(int id, const sf::Vector2f& posicionInicial, GameResources& res);

    void mover(const sf::Vector2f& nuevaPosicion);
    void moverEnTablero(int nuevoIndice, const std::array<sf::Vector2f, 40>& positions);
    void dibujar(sf::RenderWindow& ventana, bool resaltar = false) const; // Modificado
    bool puedeMoverse(int valorDado) const;
    bool contienePunto(const sf::Vector2i& punto) const;
    void seleccionar();
    void deseleccionar();
    bool estaSeleccionada() const { return seleccionada; }
    int getIndiceTablero() const { return indiceTablero; }
    void setIndiceTablero(int indice) { indiceTablero = indice; }
    bool estaEnMeta() const { return enMeta; }
    bool contiene(const sf::Vector2f& punto) const;
    void avanzarUnaPosicion(const std::array<sf::Vector2f, 44>& posicionesTablero);
    void setPosicionesTablero(const std::array<sf::Vector2f, 44>& posiciones);
    void resetRecorrido() { indiceTablero = -1; }
    int getIndiceActual() const { return indiceTablero; }
};