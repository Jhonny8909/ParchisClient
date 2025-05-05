#pragma once
#include "FichaAzul.hpp"
#include <vector>
#include "JugadorBase.hpp"

class JugadorAzul {
private:
    std::vector<FichaAzul> fichas;
    GameResources& recursos;

public:
    JugadorAzul(GameResources& resources);
    void inicializarFichas();
    void dibujarFichas(sf::RenderWindow& ventana) const;
};