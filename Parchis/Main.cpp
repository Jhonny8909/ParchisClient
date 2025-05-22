#include "PantallaJuego.h"
#include "PantallaLobby.h"
#include "PantallaLogin.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <memory>
#include <iostream>

constexpr unsigned short SERVER_PORT = 55000;
const sf::IpAddress SERVER_IP = sf::IpAddress(127,0,0,1);

enum class Estado { Login, Lobby, Juego, Ninguno };

std::unique_ptr<Pantalla> crearPantalla(
    Estado estado,
    sf::RenderWindow& window,
    sf::TcpSocket& socket,
    ColorJugador color = ColorJugador::NINGUNO // Nuevo parámetro con valor por defecto
) {
    switch (estado) {
    case Estado::Login:
        return std::make_unique<PantallaLogin>(window, socket);
    case Estado::Lobby:
        return std::make_unique<LobbyScreen>(window, socket);
    case Estado::Juego:
        return std::make_unique<PantallaJuego>(window, socket, color);
    default:
        return nullptr;
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Parchis Online");
    sf::TcpSocket socket;

    // Conexión corregida para SFML 3.0.0
    if (socket.connect(SERVER_IP, SERVER_PORT) != sf::Socket::Status::Done) {
        std::cerr << "Error al conectar al servidor" << std::endl;
        return -1;
    }

    socket.setBlocking(false);

    Estado estadoActual = Estado::Login;
    auto pantalla = crearPantalla(estadoActual, window, socket);

    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        // Procesar mensajes de red ANTES de handleInput
        sf::Packet packet;
        while (socket.receive(packet) == sf::Socket::Status::Done) {
            std::string tipo;
            if (packet >> tipo) {
                if (tipo == "LOBBY_UPDATE") {
                    int numJugadores, colorInt;
                    if (packet >> numJugadores >> colorInt) {
                        ColorJugador colorJugador = static_cast<ColorJugador>(colorInt);
                        // Si recibimos color y estamos en juego, actualizar pantalla
                        if (estadoActual == Estado::Juego) {
                            pantalla = std::make_unique<PantallaJuego>(window, socket, colorJugador);
                        }
                    }
                }
            }
        }

        pantalla->handleInput(window);
        pantalla->update(dt);

        window.clear();
        pantalla->draw(window);
        window.display();

        std::string siguienteEstado = pantalla->nextState();
        if (!siguienteEstado.empty()) {
            estadoActual = (siguienteEstado == "Login") ? Estado::Login :
                (siguienteEstado == "Lobby") ? Estado::Lobby :
                Estado::Juego;
            pantalla = crearPantalla(estadoActual, window, socket);
        }
    }
    return 0;
}