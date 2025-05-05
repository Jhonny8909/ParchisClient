#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "resources.h"

class Dado {

public:
    Dado(GameResources& resources);
    void lanzar();
    void actualizar(float deltaTime);
    void dibujar(sf::RenderWindow& ventana) const;

    int getValor() const { return valorActual; }
    bool estaRodando() const { return estaAnimando; }

private:
    std::vector<sf::Sprite> spritesDado;
    int valorActual = 1;
    bool estaAnimando = false;
    sf::Clock relojAnimacion;
    sf::Sprite* spriteActual;
};