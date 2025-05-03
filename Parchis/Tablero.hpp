#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Tablero {
public:
    std::vector<sf::Vector2f> camino;
    std::vector<std::vector<int>> ocupadas; // [casilla][info jugador/ficha]

    bool esCasillaSegura(int casilla) const;
    void ocuparCasilla(int casilla, int jugadorId, int fichaId);
};