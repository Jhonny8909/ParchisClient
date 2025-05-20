#include "PantallaLobby.h"
#include <iostream>

LobbyScreen::LobbyScreen(sf::RenderWindow& mainWindow, sf::TcpSocket& socket)
    : window(mainWindow), socket(socket) {
    if (!resources.loadAll()) {
        std::cerr << "[ERROR] Failed to load resources" << std::endl;
        return;
    }

    // Carga de sprites
    auto loadSprites = [&](const sf::Texture& tex, const std::vector<sf::Vector2f>& positions) {
        for (const auto& pos : positions) {
            sprites.emplace_back(tex);
            sprites.back().setPosition(pos);
        }
        };

    loadSprites(resources.fondo, { {0, 0} });
    loadSprites(resources.decoracion, { {0, 0} });
    loadSprites(resources.crear, { {150, 100} });
    loadSprites(resources.Codigocrear, { {150, 390} });
    loadSprites(resources.ok, { {1350, 390} });
    loadSprites(resources.Unir, { {150, 550} });
    loadSprites(resources.Codigounir, { {150, 800} });
    loadSprites(resources.ok, { {1350, 820} });

    // Configuración de UI
    createBox.setSize({ 600, 80 });
    createBox.setPosition({ 550, 420 });
    createBox.setOutlineThickness(2);
    createBox.setFillColor(sf::Color::Transparent);

    joinBox.setSize({ 600, 80 });
    joinBox.setPosition({ 550, 820 });
    joinBox.setOutlineThickness(2);
    joinBox.setFillColor(sf::Color::Transparent);

    createButton.setSize({ 120, 95 });
    createButton.setPosition({ 1350, 400 });
    createButton.setOutlineThickness(2);
    createButton.setFillColor(sf::Color::Transparent);

    joinButton.setSize({ 120, 95 });
    joinButton.setPosition({ 1350, 820 });
    joinButton.setOutlineThickness(2);
    joinButton.setFillColor(sf::Color::Transparent);

    resources.texts[0].setPosition({ 600, 395 });
    resources.texts[1].setPosition({ 600, 800 });
}

void LobbyScreen::handleInput(sf::RenderWindow& window) {
    handleEvents();
}

void LobbyScreen::handleEvents() {
    while (const std::optional event = window.pollEvent()) {
        // Evento de cierre
        if (event->is<sf::Event::Closed>()) {
            window.close();
            continue;
        }

        // Eventos de clic del mouse
        if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseEvent->button == sf::Mouse::Button::Left) {
                const auto mousePos = window.mapPixelToCoords(mouseEvent->position);

                createActive = createBox.getGlobalBounds().contains(mousePos);
                joinActive = joinBox.getGlobalBounds().contains(mousePos);

                if (createButton.getGlobalBounds().contains(mousePos) && !createCode.empty()) {
                    sendLobbyPacket("CREAR", createCode);
                }
                else if (joinButton.getGlobalBounds().contains(mousePos) && !joinCode.empty()) {
                    sendLobbyPacket("UNIRSE", joinCode);
                }
            }
        }

        // Eventos de entrada de texto
        if (const auto* textEvent = event->getIf<sf::Event::TextEntered>()) {
            if (createActive) {
                handleTextInput(createCode, textEvent->unicode, resources.texts[0]);
            }
            else if (joinActive) {
                handleTextInput(joinCode, textEvent->unicode, resources.texts[1]);
            }
        }

        // Eventos de teclado adicionales (ejemplo)
        if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
            if (keyEvent->code == sf::Keyboard::Key::Enter) {
                // Manejar Enter key
            }
        }
    }
}

void LobbyScreen::handleTextInput(std::string& code, uint32_t unicode, sf::Text& displayText) {
    if (unicode == '\b') { // Backspace
        if (!code.empty()) {
            code.pop_back();
        }
    }
    else if (unicode < 128 && unicode != '\r') { // Caracteres ASCII normales
        code += static_cast<char>(unicode);
    }
    displayText.setString(code);
}

void LobbyScreen::sendLobbyPacket(const std::string& action, const std::string& code) {
    sf::Packet packet;
    packet << "LOBBY" << action << code; // Asegúrate que los tipos coincidan

    // Debug: Mostrar lo que se está enviando
    std::cout << "[CLIENTE] Enviando paquete LOBBY: "
        << "Acción: " << action << ", Código: " << code << std::endl;

    // Cambio temporal a modo bloqueante para el envío
    socket.setBlocking(true);
    sf::Socket::Status status = socket.send(packet);
    socket.setBlocking(false);

    if (status != sf::Socket::Status::Done) {
        std::cerr << "[CLIENTE] Error al enviar paquete LOBBY: "
            << static_cast<int>(status) << std::endl;
    }
    else {
        std::cout << "[CLIENTE] Paquete LOBBY enviado correctamente" << std::endl;
    }

    waitingForResponse = true;
}

void LobbyScreen::update(float dt) {
    if (waitingForResponse) {
        checkServerResponse();
    }
}

void LobbyScreen::checkServerResponse() {
    sf::Packet packet;
    if (socket.receive(packet) == sf::Socket::Status::Done) {
        std::string packetType;
        if (packet >> packetType) {
            if (packetType == "LOBBY_RESPONSE") {
                std::string status;
                if (packet >> status) {
                    waitingForResponse = false;
                    if (status == "CREATED" || status == "JOINED") {
                        // Esperar inicio de juego
                    }
                }
            }
            else if (packetType == "GAME_START") {
                gameStarting = true;
                nextWindow = "Juego";
                waitingForResponse = false;
            }
        }
    }
}

void LobbyScreen::render() {
    window.clear();

    // Dibujar todos los sprites
    for (const auto& sprite : sprites) {
        window.draw(sprite);
    }

    // Dibujar cajas y botones
    window.draw(createBox);
    window.draw(joinBox);
    window.draw(createButton);
    window.draw(joinButton);

    // Dibujar textos
    for (const auto& text : resources.texts) {
        window.draw(text);
    }
}

void LobbyScreen::draw(sf::RenderWindow& window) {
    render();
}

std::string LobbyScreen::nextState() const {
    return gameStarting ? nextWindow : "";
}