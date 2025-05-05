#pragma once
#include "FichaAmarilla.hpp"
#include <vector>
#include "JugadorBase.hpp"

class JugadorAmarillo {
private:
    std::vector<FichaAmarilla> fichas;
    GameResources& recursos;
    const std::vector<std::unique_ptr<Ficha>>& getFichas() const override {
        // Necesitarás cambiar tu vector de FichaAmarilla a unique_ptr<Ficha>
        return;
    }

public:

    JugadorAmarillo(GameResources& resources);
    void inicializarFichas();
    void dibujarFichas(sf::RenderWindow& ventana) const;
    
};
