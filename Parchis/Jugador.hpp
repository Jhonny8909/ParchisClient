#pragma once
#include "Ficha.hpp"
#include <vector>

class Jugador {
public:
    std::vector<Ficha> fichas;
    sf::Color color;
    bool esSuTurno = false;

    bool todasFichasEnMeta() const;
};