#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct GameResources {
    // Texturas del tablero
    sf::Texture fondo;
    sf::Texture tablero;

    // Texturas de fichas
    sf::Texture fichaRoja;
    sf::Texture fichaAmarilla;
    sf::Texture fichaAzul;
    sf::Texture fichaVerde;

    // Texturas del dado (6 caras)
	sf::Texture dado1;
	sf::Texture dado2;
	sf::Texture dado3;
	sf::Texture dado4;
	sf::Texture dado5;
	sf::Texture dado6;

    bool loadAllResources();
};