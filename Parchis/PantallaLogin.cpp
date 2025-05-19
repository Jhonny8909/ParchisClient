#include "PantallaLogin.h"
#include <iostream>
#include <iomanip>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <sstream>

PantallaLogin::PantallaLogin(sf::RenderWindow& mainWindow, sf::TcpSocket& socket) : window(mainWindow),
socket(socket), success(false)
{
    socket.setBlocking(false);

    if (!resources.loadAllResources()) {
        throw std::runtime_error("Failed to load login resources");
    }

    auto cargarFichas = [&](sf::Texture& tex, const std::vector<sf::Vector2f>& posiciones) {
        for (const auto& pos : posiciones) {
            sprites.emplace_back(tex);
            sprites.back().setPosition(pos);
        }
        };

    cargarFichas(resources.background, { {0, 0} });
    cargarFichas(resources.doodles, { {0, 0} });
    cargarFichas(resources.title, { {192, 10} });
    cargarFichas(resources.nameInput, { {250, 360} });
    cargarFichas(resources.passwordInput, { {1000, 360} });
    cargarFichas(resources.loginButton, { {1000, 635} });
    cargarFichas(resources.loginButtonHover, { {1000, 635} });
    cargarFichas(resources.registerButton, { {250, 635} });
    cargarFichas(resources.registerButtonHover, { {250, 635} });

    loginButtonRect.setSize({ 635, 173 });
    loginButtonRect.setPosition({ 1000, 635 });
    loginButtonRect.setFillColor(sf::Color::Transparent);

    registerButtonRect.setSize({ 635, 173 });
    registerButtonRect.setPosition({ 250, 635 });
    registerButtonRect.setFillColor(sf::Color::Transparent);
}

void PantallaLogin::handleInput(sf::RenderWindow& window) {
    handleEvents();
}

void PantallaLogin::update(float dt) {
    if (shouldSendLogin) {
        sendAuthPacket(true);
    }
    else if (shouldSendRegister) {
        sendAuthPacket(false);
    }

    if (success == true) {
        receiveAuthPacket();
    }
}

void PantallaLogin::draw(sf::RenderWindow& window) {
    window.clear();
    for (const auto& sprite : sprites) {
        window.draw(sprite);
    }
    window.draw(loginButtonRect);
    window.draw(registerButtonRect);
    window.draw(resources.texts[0]); // Username
    window.draw(resources.texts[1]); // Password
}

void PantallaLogin::handleEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (const sf::Event::KeyPressed* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Enter && eventPressed < 1) {
                eventPressed++;
            }
        }

        if (eventPressed == 0) {
            if (const auto* textEvent = event->getIf<sf::Event::TextEntered>()) {
                if (textEvent->unicode == '\b' && !usuario.empty()) {
                    usuario.pop_back();
                }
                else if (textEvent->unicode < 128 && textEvent->unicode != '\r') {
                    usuario += static_cast<char>(textEvent->unicode);
                }
                resources.texts[1].setString(usuario);
            }
        }
        else if (eventPressed == 1) {
            if (const auto* textEvent = event->getIf<sf::Event::TextEntered>()) {
                if (textEvent->unicode == '\b' && !contrasena.empty()) {
                    contrasena.pop_back();
                }
                else if (textEvent->unicode < 128 && textEvent->unicode != '\r') {
                    contrasena += static_cast<char>(textEvent->unicode);
                }
                resources.texts[0].setString(std::string(contrasena));
            }
        }
        if (eventPressed == 1 || eventPressed == 2) {
            if (const auto* mouseButton = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseButton->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords({ mouseButton->position.x, mouseButton->position.y });
                    if (loginButtonRect.getGlobalBounds().contains(mousePos)) {
                        shouldSendLogin = true;
                        loginButtonRect.setFillColor(sf::Color::Red);
                        eventPressed = 2;// bloquea escritura despues
                        std::cout << "Login enviado" << std::endl;
                    }
                    else if (registerButtonRect.getGlobalBounds().contains(mousePos)) {
                        registerButtonRect.setFillColor(sf::Color::Red);
                        shouldSendRegister = true;
                        eventPressed = 2; // bloquea escritura despues
                        std::cout << "register enviado" << std::endl;
                    }
                }
            }
            else {
                registerButtonRect.setFillColor(sf::Color::Transparent);
                loginButtonRect.setFillColor(sf::Color::Transparent);
            }

        }

    }
}

void PantallaLogin::sendAuthPacket(bool isLogin) {
    sf::Packet packet;
    packet << "AUTH" << isLogin << usuario << contrasena; // Añade prefijo "AUTH"

    if (socket.send(packet) != sf::Socket::Status::Done) {
        std::cerr << "Error al enviar credenciales\n";
        return;
    }
    success = true;
}


void PantallaLogin::receiveAuthPacket() {
    sf::Packet packet;
    if (socket.receive(packet) == sf::Socket::Status::Done) {
        std::string tipo;
        bool exito;

        if (packet >> tipo >> exito && tipo == "AUTH_RESPONSE") {
            NextWindow = exito ? "Lobby" : "";
            std::cerr << exito << std::endl;
        }
    }
}

std::string PantallaLogin::nextState() const {
    return NextWindow;
}