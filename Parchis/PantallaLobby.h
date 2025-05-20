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

private:
    sf::RenderWindow& window;
    LobbyResources resources;
    sf::TcpSocket& socket;

    std::vector<sf::Sprite> sprites;
    sf::RectangleShape createBox;
    sf::RectangleShape joinBox;
    sf::RectangleShape createButton;
    sf::RectangleShape joinButton;

    std::string createCode;
    std::string joinCode;
    bool createActive = false;
    bool joinActive = false;
    bool waitingForResponse = false;
    bool gameStarting = false;
    std::string nextWindow;

    void handleEvents();
    void sendLobbyPacket(const std::string& action, const std::string& code);
    void checkServerResponse();
    void handleTextInput(std::string& code, uint32_t unicode, sf::Text& displayText);
    void render();
};