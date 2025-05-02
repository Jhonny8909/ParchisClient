#include "resources.h"
#include <iostream>

bool GameResources::loadAllResources() {

    // Cargar texturas

    //Fondo
    if (!texture.loadFromFile("Tablero y Fichas/Tab_fondo.png")) {
        std::cerr << "Error al cargar Tab_fondo.png" << std::endl;
        return false;
    }

    //Decoracion
    if (!texture2.loadFromFile("Tablero y Fichas/Tab_garabatos.png")) {
        std::cerr << "Error al cargar Tab_garabatos.png" << std::endl;
        return false;
    }

	//Tablero
    if (!texture3.loadFromFile("Tablero y Fichas/Tab_Tablero.png")) {
        std::cerr << "Error al cargar Tab_Tablero.png" << std::endl;
        return false;
    }

	//Fichas rojas
    if (!texture4.loadFromFile("Tablero y Fichas/Tab_Ficha_Roja_01.png")) {
        std::cerr << "Error al cargar Tab_Ficha_Roja_01.png" << std::endl;
        return false;
    }

	//Fichas amarillas
    if (!texture5.loadFromFile("Tablero y Fichas/Tab_Ficha_amarilla_01.png")) {
        std::cerr << "Error al cargar Tab_Ficha_Roja_01.png" << std::endl;
        return false;
    }

	//Fichas azules
    if (!texture6.loadFromFile("Tablero y Fichas/Tab_Ficha_azul_01.png")) {
        std::cerr << "Error al cargar Tab_Ficha_Roja_01.png" << std::endl;
        return false;
    }

    if (!tex2.loadFromFile("Tablero y Fichas/Tab_verde_01.png"))
    {
        std::cerr << "Error al cargar Tab_verde_01.png" << std::endl;
    }

    return true;
}