#include "FichaRoja.h"

FichaRoja::FichaRoja(int id, const sf::Vector2f& posicionInicial, GameResources& res)
    : id(id),
    casillaActual(-1),
    enMeta(false),
    resources(res),  // Inicializa la referencia a recursos
    sprite(res.fichaRoja) {  // Inicializa el sprite con la textura

    sprite.setPosition(posicionInicial);  // Establece la posición
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