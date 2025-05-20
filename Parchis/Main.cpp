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
    sf::TcpSocket& socket
) {
    switch (estado) {
    case Estado::Login:
        return std::make_unique<PantallaLogin>(window, socket);
    case Estado::Lobby:
        return std::make_unique<LobbyScreen>(window, socket);
    case Estado::Juego:
        return std::make_unique<PantallaJuego>(window, socket);
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

        pantalla->handleInput(window);
        pantalla->update(dt);  // Aquí se procesa la respuesta

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