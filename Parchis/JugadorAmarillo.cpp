#include "JugadorAmarillo.hpp"

JugadorAmarillo::JugadorAmarillo(GameResources& resources) : recursos(resources) {}

void JugadorAmarillo::inicializarFichas() {
    // Posiciones iniciales para rojo
    std::vector<sf::Vector2f> posiciones = {
        {100, 100}, {100, 150}, {150, 100}, {150, 150}
    };

    for (int i = 0; i < 4; ++i) {
        fichas.emplace_back(i, posiciones[i], recursos);
    }
}

void JugadorAmarillo::dibujarFichas(sf::RenderWindow& ventana) const {
    for (const auto& ficha : fichas) {
        ficha.dibujar(ventana);
    }
}