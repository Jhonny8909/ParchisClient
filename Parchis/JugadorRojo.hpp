#pragma once
#include "FichaRoja.hpp"
#include <vector>
#include "JugadorBase.hpp"

class JugadorRojo {
private:
    std::vector<FichaRoja> fichas;
    GameResources& recursos;

public:
    JugadorRojo(GameResources& resources);
    void inicializarFichas();
    void dibujarFichas(sf::RenderWindow& ventana) const;
};