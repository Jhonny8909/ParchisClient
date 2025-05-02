// resources.cpp
#include "resources.h"
#include <iostream>

bool GameResources::loadAllResources() {
    // Cargar texturas
    if (!texture.loadFromFile("Tablero y Fichas/Tab_fondo.png")) {
        std::cerr << "Error al cargar Tab_fondo.png" << std::endl;
        return false;
    }

    if (!texture2.loadFromFile("Tablero y Fichas/Tab_garabatos.png")) {
        std::cerr << "Error al cargar Tab_garabatos.png" << std::endl;
        return false;
    }

    if (!texture3.loadFromFile("Tablero y Fichas/Tab_Tablero.png")) {
        std::cerr << "Error al cargar Tab_Tablero.png" << std::endl;
        return false;
    }

    // Cargar fuente
    if (!font.openFromFile("Handwritingdarky-Regular.ttf")) {
        std::cerr << "Error al cargar la fuente" << std::endl;
        return false;
    }

    return true;
}