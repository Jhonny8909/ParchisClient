#include "FichaAmarilla.hpp"

FichaAmarilla::FichaAmarilla(int id, const sf::Vector2f& posicionInicial, GameResources& resources)
    : Ficha(id, posicionInicial) {
    sprite.setTexture(resources.fichaRoja); // Textura específica
    sprite.setPosition(posicionInicial);
}

void FichaAmarilla::dibujar(sf::RenderWindow& ventana) const {
    ventana.draw(sprite); // Puedes añadir efectos especiales aquí
}