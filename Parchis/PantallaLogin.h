#pragma once
#include "Pantalla.h"
#include "LoginResources.h"
#include <SFML/Network.hpp>

class PantallaLogin : public Pantalla {
public:

    explicit PantallaLogin(sf::RenderWindow& mainWindow, sf::TcpSocket& socket);

    void handleInput(sf::RenderWindow& window) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    std::string nextState() const override;
    std::vector<sf::Sprite> sprites;
    bool success;

private:
    sf::RenderWindow& window;
    LoginResources resources;
    sf::TcpSocket& socket;

    // Estado
    int inputState = 0; // 0: usuario, 1: contraseña
    std::string usuario;
    std::string contrasena;
    std::string NextWindow;

    sf::RectangleShape loginButtonRect;
    sf::RectangleShape registerButtonRect;

    int eventPressed = 0;
    bool shouldSendLogin = false;
    bool shouldSendRegister = false;
	

    void handleEvents();
    void sendAuthPacket(bool isLogin);
    void receiveAuthPacket();
};
