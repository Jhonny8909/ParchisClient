#include "FichaRoja.h"

FichaRoja::FichaRoja(int id, const sf::Vector2f& posicionInicial, GameResources& res)
    : id(id),
    casillaActual(-1),
    enMeta(false),
    resources(res),  // Inicializa la referencia a recursos
    sprite(res.fichaRoja) {  // Inicializa el sprite con la textura

    sprite.setPosition(posicionInicial);  // Establece la posici�n
}

void FichaRoja::dibujar(sf::RenderWindow& ventana) const {
    ventana.draw(sprite);
}

void FichaRoja::mover(const sf::Vector2f& nuevaPosicion) {
    sprite.setPosition(nuevaPosicion);
    // Aqu� puedes a�adir l�gica adicional para actualizar casillaActual
}

bool FichaRoja::puedeMoverse(int valorDado) const {
    // Implementa la l�gica de movimiento seg�n las reglas del juego
    return true;  // Cambia esto seg�n tus reglas
}