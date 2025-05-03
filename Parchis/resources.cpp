#include "resources.h"

bool GameResources::loadAllResources() {
    bool ok = true;

    ok &= fondo.loadFromFile("Tablero y Fichas/Tab_fondo.png");
    ok &= decoracion.loadFromFile("Tablero y Fichas/Tab_garabatos.png");
    ok &= tablero.loadFromFile("Tablero y Fichas/Tab_Tablero.png");
    ok &= fichaRoja.loadFromFile("Tablero y Fichas/Tab_Ficha_Roja_01.png");
    ok &= fichaAmarilla.loadFromFile("Tablero y Fichas/Tab_Ficha_amarilla_01.png");
    ok &= fichaAzul.loadFromFile("Tablero y Fichas/Tab_Ficha_azul_01.png");
    ok &= fichaVerde.loadFromFile("Tablero y Fichas/Tab_verde_01.png");

    return ok;
}