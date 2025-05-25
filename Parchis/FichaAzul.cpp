#include "FichaAzul.h"
#include <cmath>

FichaAzul::FichaAzul(int id, const sf::Vector2f& posicionInicial, GameResources& res)
    : id(id), resources(res), sprite(res.fichaAzul) {
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.size / 2.f);
    sprite.setPosition(posicionInicial);
    radio = bounds.size.x / 2.f;
    colorOriginal = sprite.getColor(); // Guardar color original
}


void FichaAzul::moverEnTablero(int nuevoIndice, const std::array<sf::Vector2f, 40>& positions) {
    if (nuevoIndice >= 0 && nuevoIndice < static_cast<int>(positions.size())) {
        indiceTablero = nuevoIndice;
        sprite.setPosition(positions[static_cast<size_t>(nuevoIndice)]);
    }
}

bool FichaAzul::contienePunto(const sf::Vector2i& punto) const {
    sf::Vector2f centro = sprite.getPosition();
    float distancia = std::hypot(punto.x - centro.x, punto.y - centro.y);
    return distancia <= radio;
}


void FichaAzul::dibujar(sf::RenderWindow& ventana, bool resaltar) const {
    // Necesitamos crear una copia modificable del sprite
    sf::Sprite spriteTemp = sprite; // Copia del sprite

    if (resaltar) {
        spriteTemp.setColor(colorOriginal);
        ventana.draw(spriteTemp);

        sf::CircleShape borde(radio + 5);
        borde.setOutlineColor(sf::Color::White);
        // ... resto del c�digo ...
    }
    else {
        sf::Color colorSemi = colorOriginal;
        colorSemi.a = 150;
        spriteTemp.setColor(colorSemi);
        ventana.draw(spriteTemp);
    }
}

void FichaAzul::mover(const sf::Vector2f& nuevaPosicion) {
    sprite.setPosition(nuevaPosicion);
    // Aqu� puedes a�adir l�gica adicional para actualizar casillaActual
}

bool FichaAzul::puedeMoverse(int valorDado) const {
    // Implementa la l�gica de movimiento seg�n las reglas del juego
    return true;  // Cambia esto seg�n tus reglas
}

void FichaAzul::seleccionar() {
    seleccionada = true;
    sprite.setColor(sf::Color::White); // M�s brillante cuando est� seleccionada
}

void FichaAzul::deseleccionar() {
    seleccionada = false;
    sprite.setColor(colorOriginal); // Volver al color original
}

bool FichaAzul::contiene(const sf::Vector2f& punto) const {
    return sprite.getGlobalBounds().contains(punto);
}

void FichaAzul::setPosicionesTablero(const std::array<sf::Vector2f, 44>& posiciones) {
    // Podemos usar esto si necesitamos almacenar las posiciones localmente
}

void FichaAzul::avanzarUnaPosicion(const std::array<sf::Vector2f, 44>& posicionesTablero) {
    if (indiceTablero < static_cast<int>(posicionesTablero.size()) - 1) {
        indiceTablero++;
        sprite.setPosition(posicionesTablero[static_cast<size_t>(indiceTablero)]);
        std::cout << "Ficha Roja " << id << " movida a posici�n " << indiceTablero + 1
            << " (" << posicionesTablero[static_cast<size_t>(indiceTablero)].x
            << ", " << posicionesTablero[static_cast<size_t>(indiceTablero)].y << ")\n";
    }
    else {
        std::cout << "La ficha ha llegado al final del tablero\n";
    }
}