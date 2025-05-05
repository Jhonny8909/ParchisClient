#pragma once
#include "FichaVerde.hpp"
#include <vector>
#include "JugadorBase.hpp"

class JugadorVerde {
private:
    std::vector<FichaVerde> fichas;
    GameResources& recursos;

public:
    JugadorVerde(GameResources& resources);
    void inicializarFichas();
    void dibujarFichas(sf::RenderWindow& ventana) const;
};