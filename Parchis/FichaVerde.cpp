#include "FichaVerde.hpp"

FichaVerde::FichaVerde(int id, const sf::Vector2f& posicionInicial, GameResources& resources)
    : Ficha(id, posicionInicial) {
    sprite.setTexture(resources.fichaRoja); // Textura espec�fica
    sprite.setPosition(posicionInicial);
}

void FichaVerde::dibujar(sf::RenderWindow& ventana) const {
    ventana.draw(sprite); // Puedes a�adir efectos especiales aqu�
}