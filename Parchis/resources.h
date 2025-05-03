#pragma once
#include <SFML/Graphics.hpp>
#include <string>

struct GameResources {
    sf::Texture fondo;         // Fondo general
    sf::Texture decoracion;    // Decoraci�n adicional
    sf::Texture tablero;       // Imagen del tablero
    sf::Texture fichaRoja;
    sf::Texture fichaAmarilla;
    sf::Texture fichaAzul;
    sf::Texture fichaVerde;

    bool loadAllResources();
};