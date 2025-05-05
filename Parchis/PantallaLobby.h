#pragma once
#include "LobbyResources.h"
#include "Pantalla.h"
#include <SFML/Network.hpp>

class LobbyScreen : public Pantalla {
public:
    explicit LobbyScreen(sf::RenderWindow& mainWindow, sf::TcpSocket& socket);

    void handleInput(sf::RenderWindow& window) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    std::string nextState() const override;

    std::vector<sf::Sprite> sprites;  // Cambiado de 'sprite' a 'sprites' por convención

private:
    sf::RenderWindow& window;
    LobbyResources resources;
    sf::TcpSocket& socket;

    // Variables de estado
    std::string codigoCrear;
    std::string codigoUnir;
    bool inputCrearActivo = false;
    bool inputUnirActivo = false;
    bool crearClick = false;
    bool unirClick = false;
    bool showHover = false;

    // Elementos UI
    sf::RectangleShape box1, box2, boton1, boton2;
    sf::FloatRect textArea1, textArea2, botonArea1, botonArea2;

    void handleEvents();
    void render();
};