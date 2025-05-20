#include "PantallaLogin.h"
#include <iostream>
#include <iomanip>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <sstream>

PantallaLogin::PantallaLogin(sf::RenderWindow& mainWindow, sf::TcpSocket& socket)
    : window(mainWindow), socket(socket) {
    if (!resources.loadAllResources()) {
        throw std::runtime_error("Failed to load login resources");
    }

    auto cargarFichas = [&](const sf::Texture& tex, const std::vector<sf::Vector2f>& posiciones) {
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
    if (authInProgress) {
        // Intenta recibir la respuesta del servidor
        sf::Packet packet;
        sf::Socket::Status status;

        // Cambio temporal a modo bloqueante con timeout
        socket.setBlocking(true);
        status = socket.receive(packet);
        socket.setBlocking(false);

        if (status == sf::Socket::Status::Done) {
            processAuthResponse(packet);
        }
        else if (status == sf::Socket::Status::NotReady) {
            // No hay datos disponibles aún, seguimos esperando
            return;
        }
        else {
            // Error o desconexión
            handleNetworkError(status);
        }
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
            continue;
        }

        // Manejo de eventos de teclado
        if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
            if (keyEvent->code == sf::Keyboard::Key::Enter) {
                if (activeField == InputField::Username) {
                    activeField = InputField::Password;
                }
                else if (activeField == InputField::Password) {
                    if (!username.empty() && !password.empty()) {
                        sendAuthPacket(true); // Intento de login
                    }
                }
            }
            else if (keyEvent->code == sf::Keyboard::Key::Tab) {
                activeField = (activeField == InputField::Username) ?
                    InputField::Password : InputField::Username;
            }
        }

        // Manejo de entrada de texto
        if (const auto* textEvent = event->getIf<sf::Event::TextEntered>()) {
            if (!authInProgress) {
                if (activeField == InputField::Username) {
                    handleTextInput(username, textEvent->unicode, resources.texts[1], false);
                }
                else if (activeField == InputField::Password) {
                    handleTextInput(password, textEvent->unicode, resources.texts[0], true);
                }
            }
        }

        // Manejo de clics del mouse
        if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseEvent->button == sf::Mouse::Button::Left) {
                const auto mousePos = window.mapPixelToCoords(mouseEvent->position);

                if (loginButtonRect.getGlobalBounds().contains(mousePos)) {
                    if (!username.empty() && !password.empty()) {
                        sendAuthPacket(true); // Login
                    }
                }
                else if (registerButtonRect.getGlobalBounds().contains(mousePos)) {
                    if (!username.empty() && !password.empty()) {
                        sendAuthPacket(false); // Registro
                    }
                }
            }
        }
    }
}

void PantallaLogin::handleTextInput(std::string& field, uint32_t unicode, sf::Text& displayText, bool isPassword) {
    if (unicode == '\b') { // Backspace
        if (!field.empty()) {
            field.pop_back();
        }
    }
    else if (unicode < 128 && unicode != '\r') { // Caracteres ASCII normales
        field += static_cast<char>(unicode);
    }

    if (isPassword) {
        displayText.setString(std::string(field.size(), '*'));
    }
    else {
        displayText.setString(field);
    }
}

void PantallaLogin::sendAuthPacket(bool isLogin) {
    sf::Packet packet;
    packet << "AUTH" << isLogin << username << password;
	std::cerr << "Enviando credenciales: " << username << " " << password << std::endl;

    if (socket.send(packet) != sf::Socket::Status::Done) {
        std::cerr << "Error al enviar credenciales" << std::endl;
        return;
    }

    authInProgress = true;
}

void PantallaLogin::processAuthResponse(sf::Packet& packet) {
    std::string packetType;
    bool success;
    std::string message;

    if (packet >> packetType >> success >> message) {
        authInProgress = false;
        authSuccess = success;

        if (packetType == "AUTH_RESPONSE") {
            if (success) {
                nextWindow = "Lobby";
                std::cout << "[CLIENTE] Autenticación exitosa" << std::endl;
            }
            else {
                std::cerr << "[CLIENTE] Error de autenticación: " << message << std::endl;
                resetLoginForm();
            }
        }
    }
    else {
        std::cerr << "[CLIENTE] Paquete de respuesta inválido" << std::endl;
        resetLoginForm();
    }
}

void PantallaLogin::handleNetworkError(sf::Socket::Status status) {
    authInProgress = false;

    switch (status) {
    case sf::Socket::Status::Disconnected:
        std::cerr << "[CLIENTE] Servidor desconectado" << std::endl;
        break;
    case sf::Socket::Status::Error:
        std::cerr << "[CLIENTE] Error de conexión" << std::endl;
        break;
    default:
        std::cerr << "[CLIENTE] Error desconocido (" << static_cast<int>(status) << ")" << std::endl;
    }

    resetLoginForm();
}

void PantallaLogin::resetLoginForm() {
    username.clear();
    password.clear();
    resources.texts[0].setString("");
    resources.texts[1].setString("");
    activeField = InputField::Username;
}


std::string PantallaLogin::nextState() const {
    return authSuccess ? nextWindow : "";
}