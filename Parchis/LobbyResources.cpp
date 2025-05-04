#include "LobbyResources.h"
#include <iostream>

bool LobbyResources::loadAll() {
    bool success = true;

    // Carga de texturas
    success &= fondo.loadFromFile("Lobby/Sala_fondo.png");
    success &= decoracion.loadFromFile("Lobby/Sala_garabatos.png");
    success &= crear.loadFromFile("Lobby/Sala_Crea.png");
    success &= Codigocrear.loadFromFile("Lobby/Sala_CODIGO_crea.png");
    success &= ok.loadFromFile("Lobby/Sala_OK.png");
    success &= Unir.loadFromFile("Lobby/Sala_Unir.png");
    success &= Codigounir.loadFromFile("Lobby/Sala_CODIGO_unir.png");
    success &= okHover.loadFromFile("Lobby/Sala_ok_hover.png");

    // Carga de fuente
    if (!font.openFromFile("Fonts/Darky.otf")) {
        std::cerr << "Error cargando fuente" << std::endl;
        success = false;
    }

    // Inicialización de textos de forma segura
    sf::Text texto1(font);
    texto1.setCharacterSize(60);
    texto1.setString("");
    texto1.setFillColor(sf::Color::Black);
    texts.push_back(texto1);

    sf::Text texto2(font);
    texto2.setCharacterSize(60);
    texto2.setString("");
    texto2.setFillColor(sf::Color::Black);
    texts.push_back(texto2);

    return success;
}