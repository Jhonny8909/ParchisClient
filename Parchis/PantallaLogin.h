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

    const std::string& getUsername() const { return username; }

private:
    sf::RenderWindow& window;
    LoginResources resources;
    sf::TcpSocket& socket;

    std::vector<sf::Sprite> sprites;
    sf::RectangleShape loginButtonRect;
    sf::RectangleShape registerButtonRect;

    enum class InputField { Username, Password, None };
    InputField activeField = InputField::Username;

    std::string username;
    std::string password;
    std::string nextWindow;

    bool authInProgress = false;
    bool authSuccess = false;

    void handleEvents();
    void handleTextInput(std::string& field, uint32_t unicode, sf::Text& displayText, bool isPassword);
    void sendAuthPacket(bool isLogin);
    void processAuthResponse(sf::Packet& packet);
    void handleNetworkError(sf::Socket::Status status);
    void resetLoginForm();
};