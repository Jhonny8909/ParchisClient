#include "resources.h"

bool GameResources::loadAllResources() {
    bool success = true;

    // Cargar tablero y fichas
    success &= fondo.loadFromFile("Tablero y Fichas/Tab_fondo.png");
    success &= tablero.loadFromFile("Tablero y Fichas/Tab_Tablero.png");
    success &= fichaRoja.loadFromFile("Tablero y Fichas/Tab_Ficha_Roja_01.png");
    success &= fichaAmarilla.loadFromFile("Tablero y Fichas/Tab_Ficha_amarilla_01.png");
    success &= fichaAzul.loadFromFile("Tablero y Fichas/Tab_Ficha_azul_01.png");
    success &= fichaVerde.loadFromFile("Tablero y Fichas/Tab_verde_01.png");

    return success;
}