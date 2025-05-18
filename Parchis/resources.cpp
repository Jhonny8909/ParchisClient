#include "resources.h"
#include <iostream>
bool GameResources::loadAllResources() {
    bool success = true;

    // Cargar tablero y fichas
    success &= fondo.loadFromFile("Tablero y Fichas/Tab_fondo.png");
    success &= tablero.loadFromFile("Tablero y Fichas/Tab_Tablero.png");
    success &= fichaRoja.loadFromFile("Tablero y Fichas/Tab_Ficha_Roja_01.png");
    success &= fichaAmarilla.loadFromFile("Tablero y Fichas/Tab_Ficha_amarilla_01.png");
    success &= fichaAzul.loadFromFile("Tablero y Fichas/Tab_Ficha_azul_01.png");
    success &= fichaVerde.loadFromFile("Tablero y Fichas/Tab_verde_01.png");
	success &= dado1.loadFromFile("Dado/dado_0005_lado_01.png");
	success &= dado2.loadFromFile("Dado/dado_0004_lado_02.png");
	success &= dado3.loadFromFile("Dado/dado_0003_lado_03.png");
	success &= dado4.loadFromFile("Dado/dado_0002_lado_04.png");
	success &= dado5.loadFromFile("Dado/dado_0001_lado_05.png");
	success &= dado6.loadFromFile("Dado/dado_0000_lado_06.png");
    std::cout << "Tamaño de dado1: " << dado1.getSize().x << "x" << dado1.getSize().y << std::endl;
    return success;
}