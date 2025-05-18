#include "PantallaLobby.h"
#include <iostream>

#define WIDTH 1920
#define HEIGHT 1080


LobbyScreen::LobbyScreen(sf::RenderWindow& mainWindow, sf::TcpSocket& socket) : window(mainWindow), socket(socket) {
    auto localAddress = sf::IpAddress::getLocalAddress();
    if (!localAddress) {
        std::cerr << "[ERROR] No se pudo obtener la dirección local" << std::endl;
        myIP = "127.0.0.1";
    }
    else {
        myIP = localAddress->toString();
    }
    std::cout << "[LOBBY] Initializing lobby screen. Local IP: " << myIP << std::endl;

    if (!resources.loadAll()) {
        std::cerr << "[ERROR] Failed to load resources" << std::endl;
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

                std::cout << "[INPUT] Click at: " << mousePosF.x << ", " << mousePosF.y << std::endl;
                if (inputCrearActivo) std::cout << "[INPUT] Focus on CREATE ROOM code field" << std::endl;
                if (inputUnirActivo) std::cout << "[INPUT] Focus on JOIN ROOM code field" << std::endl;
            }
        }

        if (const auto* textEvent = event->getIf<sf::Event::TextEntered>()) {
            if (inputCrearActivo) {
                if (textEvent->unicode == '\b') {
                    if (!codigoCrear.empty()) {
                        codigoCrear.pop_back();
                        std::cout << "[INPUT] Backspace in CREATE field. Current code: " << codigoCrear << std::endl;
                    }
                }
                else if (textEvent->unicode < 128 && textEvent->unicode != '\r') {
                    codigoCrear += static_cast<char>(textEvent->unicode);
                    std::cout << "[INPUT] Typed in CREATE field. Current code: " << codigoCrear << std::endl;
                }
                resources.texts[0].setString(codigoCrear);
            }
            else if (inputUnirActivo) {
                if (textEvent->unicode == '\b') {
                    if (!codigoUnir.empty()) {
                        codigoUnir.pop_back();
                        std::cout << "[INPUT] Backspace in JOIN field. Current code: " << codigoUnir << std::endl;
                    }
                }
                else if (textEvent->unicode < 128 && textEvent->unicode != '\r') {
                    codigoUnir += static_cast<char>(textEvent->unicode);
                    std::cout << "[INPUT] Typed in JOIN field. Current code: " << codigoUnir << std::endl;
                }
                resources.texts[1].setString(codigoUnir);
            }
        }

        if (crearClick) {
            sf::Packet packet;
            packet << "LOBBY" << "CREAR" << codigoCrear << myIP;
            std::cout << "[NETWORK] Sending CREATE ROOM request to server. Code: " << codigoCrear << " | My IP: " << myIP << std::endl;

            if (socket.send(packet) == sf::Socket::Status::Done) {
                isHost = true;
                currentState = LobbyState::Waiting;
                std::cout << "[LOBBY] Now waiting for players to join room: " << codigoCrear << std::endl;
                std::cout << "[NETWORK] CREATE ROOM packet sent successfully" << std::endl;
            }
            else {
                std::cerr << "[ERROR] Failed to send CREATE ROOM packet" << std::endl;
            }
        }

        if (unirClick) {
            sf::Packet packet;
            packet << "LOBBY" << "UNIRSE" << codigoUnir << myIP;
            std::cout << "[NETWORK] Sending JOIN ROOM request to server. Code: " << codigoUnir << " | My IP: " << myIP << std::endl;

            if (socket.send(packet) == sf::Socket::Status::Done) {
                currentState = LobbyState::Waiting;
                std::cout << "[LOBBY] Requesting to join room: " << codigoUnir << std::endl;
                std::cout << "[NETWORK] JOIN ROOM packet sent successfully" << std::endl;
            }
            else {
                std::cerr << "[ERROR] Failed to send JOIN ROOM packet" << std::endl;
            }
        }

        // Handle server responses
        sf::Packet serverPacket;
        if (socket.receive(serverPacket) == sf::Socket::Status::Done) {
            std::string packetType;
            serverPacket >> packetType;
            std::cout << "[NETWORK] Received packet from server. Type: " << packetType << std::endl;

            if (packetType == "GAME_START") {
                std::cout << "[LOBBY] Game start signal received from server" << std::endl;
                handleGameStart(serverPacket);
            }
            else if (packetType == "PLAYER_JOINED") {
                std::string joiningPlayerIP;
                serverPacket >> joiningPlayerIP;
                std::cout << "[LOBBY] New player joined the room: " << joiningPlayerIP << std::endl;
            }
            else if (packetType == "ROOM_CREATED") {
                std::cout << "[LOBBY] Room successfully created on server" << std::endl;
            }
            else if (packetType == "ROOM_JOINED") {
                std::cout << "[LOBBY] Successfully joined room on server" << std::endl;
            }
            else if (packetType == "ERROR") {
                std::string errorMsg;
                serverPacket >> errorMsg;
                std::cerr << "[ERROR] Server error: " << errorMsg << std::endl;
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
    std::cout << "[GAME] Game starting. My role: " << role << std::endl;

    std::vector<std::string> peerIPs;
    std::string ip;
    while (packet >> ip) {
        peerIPs.push_back(ip);
        std::cout << "[NETWORK] Peer IP to connect: " << ip << std::endl;
    }

    establishP2PConnections(peerIPs);
    currentState = LobbyState::InGame;
    NextWindow = "Juego";
    std::cout << "[LOBBY] Transitioning to game screen" << std::endl;
}

void LobbyScreen::establishP2PConnections(const std::vector<std::string>& peerIPs) {
    std::cout << "[NETWORK] Establishing P2P connections with " << peerIPs.size() << " peers" << std::endl;

    for (const auto& ip : peerIPs) {
        auto peerSocket = std::make_unique<sf::TcpSocket>();
        auto peerAddress = sf::IpAddress::resolve(ip);

        if (!peerAddress) {
            std::cerr << "[ERROR] Could not resolve peer IP: " << ip << std::endl;
            continue;
        }

        // Intento de conexión con timeout
        sf::Socket::Status status = peerSocket->connect(*peerAddress, 53000, sf::seconds(5));

        if (status == sf::Socket::Status::Done) {
            peerSockets.push_back(std::move(peerSocket));
            std::cout << "[NETWORK] Successfully connected to peer: " << ip << std::endl;
        }
        else {
            std::cerr << "[ERROR] Failed to connect to peer: " << ip
                << " (Error: " << static_cast<int>(status) << ")" << std::endl;
        }
    }
}