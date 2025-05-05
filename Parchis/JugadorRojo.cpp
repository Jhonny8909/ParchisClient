#include "JugadorRojo.hpp"

JugadorRojo::JugadorRojo(GameResources& resources) : recursos(resources) {}

void JugadorRojo::inicializarFichas() {
    // Posiciones iniciales para rojo
    std::vector<sf::Vector2f> posiciones = {
        {100, 100}, {100, 150}, {150, 100}, {150, 150}
    };

    for (int i = 0; i < 4; ++i) {
        fichas.emplace_back(i, posiciones[i], recursos);
    }
}

void JugadorRojo::dibujarFichas(sf::RenderWindow& ventana) const {
    for (const auto& ficha : fichas) {
        ficha.dibujar(ventana);
    }
}