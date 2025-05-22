#include "FichaVerde.h"
#include <cmath>

FichaVerde::FichaVerde(int id, const sf::Vector2f& posicionInicial, GameResources& res)
    : id(id), resources(res), sprite(res.fichaRoja) {
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.size / 2.f);
    sprite.setPosition(posicionInicial);
    radio = bounds.size.x / 2.f;
    colorOriginal = sprite.getColor(); // Guardar color original
}


void FichaVerde::moverEnTablero(int nuevoIndice, const std::array<sf::Vector2f, 40>& positions) {
    if (nuevoIndice >= 0 && nuevoIndice < static_cast<int>(positions.size())) {
        indiceTablero = nuevoIndice;
        sprite.setPosition(positions[static_cast<size_t>(nuevoIndice)]);
    }
}

bool FichaVerde::contienePunto(const sf::Vector2i& punto) const {
    sf::Vector2f centro = sprite.getPosition();
    float distancia = std::hypot(punto.x - centro.x, punto.y - centro.y);
    return distancia <= radio;
}


void FichaVerde::dibujar(sf::RenderWindow& ventana, bool resaltar) const {
    // Necesitamos crear una copia modificable del sprite
    sf::Sprite spriteTemp = sprite; // Copia del sprite

    if (resaltar) {
        spriteTemp.setColor(colorOriginal);
        ventana.draw(spriteTemp);

        sf::CircleShape borde(radio + 5);
        borde.setOutlineColor(sf::Color::White);
        // ... resto del código ...
    }
    else {
        sf::Color colorSemi = colorOriginal;
        colorSemi.a = 150;
        spriteTemp.setColor(colorSemi);
        ventana.draw(spriteTemp);
    }
}

void FichaVerde::mover(const sf::Vector2f& nuevaPosicion) {
    sprite.setPosition(nuevaPosicion);
    // Aquí puedes añadir lógica adicional para actualizar casillaActual
}

bool FichaVerde::puedeMoverse(int valorDado) const {
    // Implementa la lógica de movimiento según las reglas del juego
    return true;  // Cambia esto según tus reglas
}

void FichaVerde::seleccionar() {
    seleccionada = true;
    sprite.setColor(sf::Color::White); // Más brillante cuando está seleccionada
}

void FichaVerde::deseleccionar() {
    seleccionada = false;
    sprite.setColor(colorOriginal); // Volver al color original
}

bool FichaVerde::contiene(const sf::Vector2f& punto) const {
    return sprite.getGlobalBounds().contains(punto);
}

void FichaVerde::setPosicionesTablero(const std::array<sf::Vector2f, 44>& posiciones) {
    // Podemos usar esto si necesitamos almacenar las posiciones localmente
}

void FichaVerde::avanzarUnaPosicion(const std::array<sf::Vector2f, 44>& posicionesTablero) {
    if (indiceTablero < static_cast<int>(posicionesTablero.size()) - 1) {
        indiceTablero++;
        sprite.setPosition(posicionesTablero[static_cast<size_t>(indiceTablero)]);
        std::cout << "Ficha Roja " << id << " movida a posición " << indiceTablero + 1
            << " (" << posicionesTablero[static_cast<size_t>(indiceTablero)].x
            << ", " << posicionesTablero[static_cast<size_t>(indiceTablero)].y << ")\n";
    }
    else {
        std::cout << "La ficha ha llegado al final del tablero\n";
    }
}