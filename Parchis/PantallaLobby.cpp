#include "PantallaLobby.h"
#include <iostream>

#define WIDTH 1920
#define HEIGHT 1080


LobbyScreen::LobbyScreen(sf::RenderWindow& mainWindow, sf::TcpSocket& socket) : window(mainWindow), socket(socket) {
    myIP = sf::IpAddress::getLocalAddress().value().toString();

    if (!resources.loadAll()) {
        std::cerr << "Error al cargar recursos" << std::endl;
        return;
    }

    // Función lambda para carga de sprites
    auto cargarFichas = [&](sf::Texture& tex, const std::vector<sf::Vector2f>& posiciones) {
        sprites.reserve(sprites.size() + posiciones.size());
        for (const auto& pos : posiciones) {
            sprites.emplace_back(tex);
            sprites.back().setPosition(pos);
        }
        };

    // Carga y posicionamiento
    cargarFichas(resources.fondo, { {0, 0} });
    cargarFichas(resources.decoracion, { {0, 0} });
    cargarFichas(resources.crear, { {150, 100} });
    cargarFichas(resources.Codigocrear, { {150, 390} });
    cargarFichas(resources.ok, { {1350, 390} });
    cargarFichas(resources.Unir, { {150, 550} });
    cargarFichas(resources.Codigounir, { {150, 800} });
    cargarFichas(resources.ok, { {1350, 820} });
    cargarFichas(resources.okHover, { {0, 0} }); // Posición temporal

    // Configuración de áreas interactivas
    textArea1 = sf::FloatRect({ 580, 390 }, { 600, 80 });
    textArea2 = sf::FloatRect({ 580, 800 }, { 600, 80 });
    botonArea1 = sf::FloatRect({ 1355, 400 }, { 120, 95 });
    botonArea2 = sf::FloatRect({ 1355, 830 }, { 120, 95 });

    // Configuración de cajas
    box1.setSize({ 600, 80 });
    box1.setPosition({ 550, 420 });
    box1.setOutlineThickness(2);
    box1.setFillColor(sf::Color::Transparent);

    box2.setSize({ 600, 80 });
    box2.setPosition({ 550, 820 });
    box2.setOutlineThickness(2);
    box2.setFillColor(sf::Color::Transparent);

    boton1.setSize({ 120, 95 });
    boton1.setPosition({ 1350, 400 });
    boton1.setOutlineThickness(2);
    boton1.setFillColor(sf::Color::Transparent);

    boton2.setSize({ 120, 95 });
    boton2.setPosition({ 1350, 820 });
    boton2.setOutlineThickness(2);
    boton2.setFillColor(sf::Color::Transparent);

    // Posición de textos
    resources.texts[0].setPosition({ 600, 395 });
    resources.texts[1].setPosition({ 600, 800 });
}


void LobbyScreen::handleInput(sf::RenderWindow& window) {
    handleEvents();
}

void LobbyScreen::handleEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();

        if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseEvent->button == sf::Mouse::Button::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                inputCrearActivo = textArea1.contains(mousePosF);
                inputUnirActivo = textArea2.contains(mousePosF);
                crearClick = botonArea1.contains(mousePosF);
                unirClick = botonArea2.contains(mousePosF);

                std::cout << "Clic en: " << mousePosF.x << ", " << mousePosF.y << std::endl;
            }
        }

        if (const auto* textEvent = event->getIf<sf::Event::TextEntered>()) {
            if (inputCrearActivo) {
                if (textEvent->unicode == '\b') {
                    if (!codigoCrear.empty()) codigoCrear.pop_back();
                }
                else if (textEvent->unicode < 128 && textEvent->unicode != '\r') {
                    codigoCrear += static_cast<char>(textEvent->unicode);
                }
                resources.texts[0].setString(codigoCrear);
            }
            else if (inputUnirActivo) {
                if (textEvent->unicode == '\b') {
                    if (!codigoUnir.empty()) codigoUnir.pop_back();
                }
                else if (textEvent->unicode < 128 && textEvent->unicode != '\r') {
                    codigoUnir += static_cast<char>(textEvent->unicode);
                }
                resources.texts[1].setString(codigoUnir);
            }
        }

        if (crearClick) {
            sf::Packet packet;
            packet << "LOBBY" << "CREAR" << codigoCrear << myIP; // Incluye tu IP

            if (socket.send(packet) == sf::Socket::Status::Done) {
                isHost = true;
                currentState = LobbyState::Waiting;
                std::cout << "Esperando jugadores...\n";
            }
        }

        if (unirClick) {
            sf::Packet packet;
            packet << "LOBBY" << "UNIRSE" << codigoUnir << myIP;

            if (socket.send(packet) == sf::Socket::Status::Done) {
                currentState = LobbyState::Waiting;
                std::cout << "Solicitando unión...\n";
            }
        }

        // Manejo de respuestas del servidor (añade esto al final de handleEvents)
        sf::Packet serverPacket;
        if (socket.receive(serverPacket) == sf::Socket::Status::Done) {
            std::string packetType;
            serverPacket >> packetType;

            if (packetType == "GAME_START") {
                handleGameStart(serverPacket);
            }
        }
    }
}

void LobbyScreen::update(float dt) {
    sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(window));
    showHover = sprites[4].getGlobalBounds().contains(mouse) ||
        sprites[7].getGlobalBounds().contains(mouse);

    box1.setOutlineColor(inputCrearActivo ? sf::Color::Green : sf::Color::White);
    box2.setOutlineColor(inputUnirActivo ? sf::Color::Green : sf::Color::White);
    boton1.setOutlineColor(crearClick ? sf::Color::Green : sf::Color::White);
    boton2.setOutlineColor(unirClick ? sf::Color::Green : sf::Color::White);


}

void LobbyScreen::render() {
    window.clear();

    // Fondo y decoración
    window.draw(sprites[0]); // Fondo
    window.draw(sprites[1]); // Decoración

    // Elementos UI
    for (int i = 2; i <= 7; ++i) {
        window.draw(sprites[i]);
    }

    // Hover effect
    if (showHover) {
        sprites[8].setPosition(
            sprites[4].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) ?
            sprites[4].getPosition() :
            sprites[7].getPosition()
        );
        window.draw(sprites[8]);
    }

    // Dibuja cajas y textos
    window.draw(box1);
    window.draw(box2);
    window.draw(boton1);
    window.draw(boton2);

    for (auto& text : resources.texts) {
        window.draw(text);
    }
}

void LobbyScreen::draw(sf::RenderWindow& window) {
    render();
}

std::string LobbyScreen::nextState() const {
    return NextWindow;
}

void LobbyScreen::handleGameStart(sf::Packet& packet) {
    std::string role;
    packet >> role;

    std::vector<std::string> peerIPs;
    std::string ip;
    while (packet >> ip) {
        peerIPs.push_back(ip);
    }

    establishP2PConnections(peerIPs);
    currentState = LobbyState::InGame;
    NextWindow = "game"; // Cambia a la pantalla de juego
}

void LobbyScreen::establishP2PConnections(const std::vector<std::string>& peerIPs) {
    for (const auto& ip : peerIPs) {
        auto peerSocket = std::make_unique<sf::TcpSocket>();
        std::optional<sf::IpAddress> peerAddress = sf::IpAddress::resolve(ip);

        if (peerAddress && peerSocket->connect(*peerAddress, 53000) == sf::Socket::Status::Done) {
            peerSockets.push_back(std::move(peerSocket));
            std::cout << "Conectado a " << ip << std::endl;
        }
    }
}