/*#include "PantallaLobby.h"
#include <iostream>

#define WIDTH 1920
#define HEIGHT 1080
#define SERVER_PORT 55000
const sf::IpAddress SERVER_IP = sf::IpAddress(127, 0, 0, 1);

PantallaLobby::PantallaLobby() {
    if (!resources.loadAllResources()) {
        std::cerr << "Error al cargar recursos de Lobby." << std::endl;
        throw std::runtime_error("Fallo en LobbyResources.");
    }

    if (socket.connect(SERVER_IP, SERVER_PORT) != sf::Socket::Status::Done) {
        std::cerr << "No se pudo conectar al servidor." << std::endl;
    }

    auto cargarSprite = [&](sf::Texture& tex, sf::Vector2f pos) {
        sprites.emplace_back(tex);
        sprites.back().setPosition(pos);
        };

    cargarSprite(resources.fondo, { 0, 0 });
    cargarSprite(resources.garabatos, { 0, 0 });
    cargarSprite(resources.textoCrea, { WIDTH / 3.f - 200, HEIGHT / 6.f - 50 });
    cargarSprite(resources.codigoCrea, { WIDTH / 10.f, HEIGHT / 3.f });
    cargarSprite(resources.botonOK, { WIDTH / 1.3f - 200, HEIGHT / 2.9f });
    cargarSprite(resources.textoUnir, { WIDTH / 3.f - 200, HEIGHT / 1.7f - 50 });
    cargarSprite(resources.codigoUnir, { WIDTH / 10.f , HEIGHT / 1.4f });
    cargarSprite(resources.botonOK2, { WIDTH / 1.3f - 200, HEIGHT / 1.35f });

    // Textos
    sf::Text txt1(resources.fuente);
	txt1.setCharacterSize(60);
    txt1.setPosition({ 600.f, 395.f });
    txt1.setFillColor(sf::Color::Black);
    textos.push_back(txt1);

    sf::Text txt2(resources.fuente);
	txt2.setCharacterSize(60);
    txt2.setPosition({ 600.f, 800.f });
    txt2.setFillColor(sf::Color::Black);
    textos.push_back(txt2);

    // Cajas
    textArea1 = { {580.f, 390.f}, {600.f, 80.f} };
    textArea2 = { {580.f, 800.f}, {600.f, 80.f} };
    botonArea1 = { {1350.f, 380.f}, {120.f, 95.f} };
    botonArea2 = { {1350.f, 800.f}, {120.f, 95.f} };

    for (auto area : { textArea1, textArea2, botonArea1, botonArea2 }) {
        sf::RectangleShape caja(area.size);
        caja.setPosition(area.position);
        caja.setFillColor(sf::Color::Transparent);
        caja.setOutlineColor(sf::Color::White);
        caja.setOutlineThickness(2.f);
        cajas.push_back(caja);
    }

    sprites.emplace_back(resources.botonHover);  // al final para dibujarlo arriba si es necesario
}

void PantallaLobby::handleInput(sf::RenderWindow& window) {
    sf::Vector2f mouseWorld = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    showHover = false;

    if (sprites[4].getGlobalBounds().contains(mouseWorld)) {
        sprites.back().setPosition(sprites[4].getPosition());
        showHover = true;
    }
    else if (sprites[7].getGlobalBounds().contains(mouseWorld)) {
        sprites.back().setPosition(sprites[7].getPosition());
        showHover = true;
    }

    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (const auto* m = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (m->button == sf::Mouse::Button::Left) {
                textInputActive1 = textArea1.contains(mouseWorld);
                textInputActive2 = textArea2.contains(mouseWorld);
                botonClick1 = botonArea1.contains(mouseWorld);
                botonClick2 = botonArea2.contains(mouseWorld);
            }
        }

        if (textInputActive1 || textInputActive2) {
            if (const auto* t = event->getIf<sf::Event::TextEntered>()) {
                if (t->unicode == '\b') {
                    if (!usuario.empty()) usuario.pop_back();
                }
                else if (t->unicode < 128 && t->unicode != '\r') {
                    usuario += static_cast<char>(t->unicode);
                }

                if (textInputActive1) textos[0].setString(usuario);
                if (textInputActive2) textos[1].setString(usuario);
            }
        }

        if (botonClick1 || botonClick2) {
            sf::Packet packet;
            packet << (botonClick1 ? "CREAR" : "UNIRSE") << usuario;
            if (socket.send(packet) != sf::Socket::Status::Done) {
                std::cerr << "Error al enviar al servidor." << std::endl;
            }
            else {
                std::cout << "Datos enviados: " << usuario << std::endl;
            }

            botonClick1 = false;
            botonClick2 = false;
        }
    }
}

void PantallaLobby::update(float) {
    cajas[0].setOutlineColor(textInputActive1 ? sf::Color::Green : sf::Color::White);
    cajas[1].setOutlineColor(textInputActive2 ? sf::Color::Green : sf::Color::White);
    cajas[2].setOutlineColor(botonClick1 ? sf::Color::Green : sf::Color::White);
    cajas[3].setOutlineColor(botonClick2 ? sf::Color::Green : sf::Color::White);
}

void PantallaLobby::draw(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    for (size_t i = 0; i < sprites.size() - 1; ++i) window.draw(sprites[i]);  // todos menos el hover
    for (auto& c : cajas) window.draw(c);
    for (auto& t : textos) window.draw(t);
    if (showHover) window.draw(sprites.back());
    window.display();
}

std::string PantallaLobby::nextState() const {
    return siguienteEstado;
}*/