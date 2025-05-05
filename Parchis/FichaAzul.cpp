#include "FichaAzul.hpp"

FichaAzul::FichaAzul(int id, const sf::Vector2f& posicionInicial, GameResources& resources)
    : Ficha(id, posicionInicial) {
    sprite.setTexture(resources.fichaRoja); // Textura específica
    sprite.setPosition(posicionInicial);
}

void FichaAzul::dibujar(sf::RenderWindow& ventana) const {
    ventana.draw(sprite); // Puedes añadir efectos especiales aquí
}