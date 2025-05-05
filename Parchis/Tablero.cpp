#include "Tablero.hpp"

Tablero::Tablero() {
    inicializarPosiciones();
}

void Tablero::inicializarPosiciones() {
    // Inicialización explícita de cada Vector2f
    casillas = {
        // Camino principal (0-39)
        sf::Vector2f(880, 130),  sf::Vector2f(880, 190),  sf::Vector2f(880, 250),
        sf::Vector2f(880, 310),  sf::Vector2f(880, 370),  sf::Vector2f(810, 440),
        sf::Vector2f(740, 440),  sf::Vector2f(680, 440),  sf::Vector2f(615, 440),
        sf::Vector2f(545, 440),  sf::Vector2f(545, 580),  sf::Vector2f(615, 580),
        sf::Vector2f(680, 580),  sf::Vector2f(740, 580),  sf::Vector2f(810, 580),
        sf::Vector2f(880, 645),  sf::Vector2f(880, 710),  sf::Vector2f(880, 770),
        sf::Vector2f(880, 830),  sf::Vector2f(880, 880),  sf::Vector2f(1025, 880),
        sf::Vector2f(1025, 830), sf::Vector2f(1025, 770), sf::Vector2f(1025, 710),
        sf::Vector2f(1025, 645), sf::Vector2f(1095, 580), sf::Vector2f(1165, 580),
        sf::Vector2f(1230, 580), sf::Vector2f(1295, 580), sf::Vector2f(1360, 580),
        sf::Vector2f(1360, 440), sf::Vector2f(1295, 440), sf::Vector2f(1230, 440),
        sf::Vector2f(1165, 440), sf::Vector2f(1095, 440), sf::Vector2f(1025, 370),
        sf::Vector2f(1025, 310), sf::Vector2f(1025, 250), sf::Vector2f(1025, 190),
        sf::Vector2f(1025, 130),

        // Pasillo Rojo (40-43)
        sf::Vector2f(950, 190), sf::Vector2f(950, 250), sf::Vector2f(950, 310), sf::Vector2f(950, 370),

        // Pasillo Amarillo (44-47)
        sf::Vector2f(615, 510), sf::Vector2f(680, 510), sf::Vector2f(740, 510), sf::Vector2f(810, 510),

        // Pasillo Azul (48-51)
        sf::Vector2f(955, 830), sf::Vector2f(955, 770), sf::Vector2f(955, 710), sf::Vector2f(955, 645),

        // Pasillo Verde (52-55)
        sf::Vector2f(1295, 510), sf::Vector2f(1230, 510), sf::Vector2f(1165, 510), sf::Vector2f(1095, 510),

        // Metas finales (56-59)
        sf::Vector2f(950, 440),   // Rojo
        sf::Vector2f(880, 510),    // Amarillo
        sf::Vector2f(955, 580),    // Azul
        sf::Vector2f(1025, 510)    // Verde
    };
}

const sf::Vector2f& Tablero::getPosicionCasilla(int indice) const {
    if (indice < 0 || indice >= NUM_CASILLAS) {
        throw std::out_of_range("Índice de casilla inválido");
    }
    return casillas[indice];
}

bool Tablero::esCasillaSegura(int indice) const {
    // Casillas seguras: salidas y esquinas
    const std::array<int, 8> seguras = { 0, 10, 20, 30, 5, 15, 25, 35 };
    return std::find(seguras.begin(), seguras.end(), indice) != seguras.end();
}

int Tablero::getPasilloMetaDesdeColor(int color) const {
    if (color < 0 || color > 3) return -1;
    return entradasMeta[color];
}