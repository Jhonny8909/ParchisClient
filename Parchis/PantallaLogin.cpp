#include "PantallaLogin.h"
#include <iostream>
#include <iomanip>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <sstream>

#define HEIGHT 1920
#define WIDTH 1080

PantallaLogin::PantallaLogin(sf::RenderWindow& mainWindow, sf::TcpSocket& socket) : window(mainWindow), socket(socket) {
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
    loginButtonRect.setPosition({ 1000, 635});
    loginButtonRect.setFillColor(sf::Color::Transparent);

    registerButtonRect.setSize({ 635, 173 });
    registerButtonRect.setPosition({ 250, 635});
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
        if(eventPressed==1 || eventPressed==2){
            if (const auto* mouseButton = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseButton->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords({ mouseButton->position.x, mouseButton->position.y });
                    if (loginButtonRect.getGlobalBounds().contains(mousePos)) {
                        shouldSendLogin = true;
                        loginButtonRect.setFillColor(sf::Color::Red);
                        eventPressed = 2;// bloquea escritura después
                        std::cout << "Login enviado" << std::endl;
                    }
                    else if (registerButtonRect.getGlobalBounds().contains(mousePos)) {
                        registerButtonRect.setFillColor(sf::Color::Red);
                        shouldSendRegister = true;
                        eventPressed = 2; // bloquea escritura después
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
    if ((isLogin && !shouldSendLogin) || (!isLogin && !shouldSendRegister))
        return;

    sf::Packet packet;
    packet << isLogin << usuario << contrasena;

    if (socket.send(packet) == sf::Socket::Status::Done) {
        std::cout << (isLogin ? "Login" : "Registro") << " enviado correctamente: "
            << usuario << ", " << contrasena << std::endl;
    }
    else {
        std::cerr << "Error al enviar " << (isLogin ? "login" : "registro") << std::endl;
    }

    shouldSendLogin = false;
    shouldSendRegister = false;
}

std::string PantallaLogin::hashSHA256(const std::string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();

    if (!mdctx) return "";

    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), nullptr) != 1 ||
        EVP_DigestUpdate(mdctx, password.c_str(), password.size()) != 1 ||
        EVP_DigestFinal_ex(mdctx, hash, nullptr) != 1) {
        EVP_MD_CTX_free(mdctx);
        return "";
    }

    EVP_MD_CTX_free(mdctx);

    std::ostringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];

    return ss.str();
}

std::string PantallaLogin::nextState() const {
    return "Lobby";
}
