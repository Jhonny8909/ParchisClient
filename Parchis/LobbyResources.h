#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class LobbyResources {
public:
    // Texturas
    sf::Texture fondo;
    sf::Texture decoracion;
    sf::Texture crear;
    sf::Texture Codigocrear;
    sf::Texture ok;
    sf::Texture Unir;
    sf::Texture Codigounir;
    sf::Texture okHover;

    // Fuente
    sf::Font font;
    std::vector<sf::Text> texts;

    bool loadAll();
};