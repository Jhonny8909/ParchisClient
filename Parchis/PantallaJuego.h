#pragma once
#include "Pantalla.h"
#include <SFML/Network.hpp>
#include "resources.h"
#include "Dado.hpp"
#include "FichaRoja.h"


class PantallaJuego : public Pantalla {
public:
    explicit PantallaJuego(sf::RenderWindow& mainWindow, sf::TcpSocket& socket); 
    void handleInput(sf::RenderWindow& window) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    std::string nextState() const override;

    std::vector<sf::Sprite> sprites;

	std::vector<FichaRoja> fichasRojas; // Vector para almacenar las fichas

    Dado Dado;

private:
    GameResources resources;
    sf::RenderWindow& window;
    sf::TcpSocket& socket; 

    void handleEvents(); 
    void render(); 
};