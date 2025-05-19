#include "FichaRoja.h"
#include <cmath>

FichaRoja::FichaRoja(int id, const sf::Vector2f& posicionInicial, GameResources& res)
    : id(id), resources(res), sprite(res.fichaRoja) {
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.size / 2.f);
    sprite.setPosition(posicionInicial);
    radio = bounds.size.x / 2.f;
}

void FichaRoja::moverEnTablero(int nuevoIndice, const std::array<sf::Vector2f, 40>& positions) {
    if (nuevoIndice >= 0 && nuevoIndice < static_cast<int>(positions.size())) {
        indiceTablero = nuevoIndice;
        sprite.setPosition(positions[static_cast<size_t>(nuevoIndice)]);
    }
}

bool FichaRoja::contienePunto(const sf::Vector2i& punto) const {
    sf::Vector2f centro = sprite.getPosition();
    float distancia = std::hypot(punto.x - centro.x, punto.y - centro.y);
    return distancia <= radio;
}


void FichaRoja::dibujar(sf::RenderWindow& ventana) const {
    ventana.draw(sprite);
}

void FichaRoja::mover(const sf::Vector2f& nuevaPosicion) {
    sprite.setPosition(nuevaPosicion);
    // Aquí puedes añadir lógica adicional para actualizar casillaActual
}

bool FichaRoja::puedeMoverse(int valorDado) const {
    // Implementa la lógica de movimiento según las reglas del juego
    return true;  // Cambia esto según tus reglas
}