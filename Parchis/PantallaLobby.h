/*#pragma once
#pragma once

#include "Pantalla.h"
#include "LobbyResources.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <optional>

class PantallaLobby : public Pantalla {
private:
    LobbyResources resources;
    std::vector<sf::Sprite> sprites;
    std::vector<sf::Text> textos;
    std::vector<sf::RectangleShape> cajas;

    std::string siguienteEstado = "lobby";
    sf::TcpSocket socket;

    sf::FloatRect textArea1, textArea2, botonArea1, botonArea2;
    bool textInputActive1 = false;
    bool textInputActive2 = false;
    bool botonClick1 = false;
    bool botonClick2 = false;
    bool showHover = false;
    std::string usuario;

public:
    PantallaLobby();

    void handleInput(sf::RenderWindow& window) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    std::string nextState() const override;
};*/