#include "PantallaJuego.h"
#include "PantallaLobby.h"
#include <iostream>
#include "PantallaLogin.h" // si la implementas

#define SERVER_PORT 55000
const sf::IpAddress SERVER_IP = sf::IpAddress(192, 168, 0, 25);




enum class Estado { Login, Lobby, Juego, Ninguno };

std::unique_ptr<Pantalla> crearPantalla(Estado estado, sf::RenderWindow& window, sf::TcpSocket& socket) {
    sf::Socket::Status status = socket.connect({ 192, 168, 0, 25 }, 55000);
    switch (estado) {
    case Estado::Lobby: return std::make_unique<LobbyScreen>(window, socket);
        //case Estado::Juego: return std::make_unique<PantallaJuego>(window);
    case Estado::Login: return std::make_unique<PantallaLogin>(window, socket);
    default: return nullptr;
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Parchis Online");

    sf::TcpSocket socket;

    if (socket.connect(SERVER_IP, SERVER_PORT) != sf::Socket::Status::Done) {
        std::cerr << "Error al conectar al servidor" << std::endl;
        return -1;
    }

    std::cout << "Conectado al servidor" << std::endl;


    sf::Clock clock;

    Estado estadoActual = Estado::Login;
    std::unique_ptr<Pantalla> pantalla = crearPantalla(estadoActual, window, socket);

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        pantalla->handleInput(window);
        pantalla->update(dt);

        window.clear();
        pantalla->draw(window);
        window.display();


        std::string siguiente = pantalla->nextState();
        /*if (siguiente == "juego") {
            estadoActual = Estado::Juego;
            pantalla = crearPantalla(estadoActual, window);
        }
        else*/ if (siguiente == "lobby") {
            estadoActual = Estado::Lobby;
            pantalla = crearPantalla(estadoActual, window, socket);
        }
        else if (siguiente == "login") {
            estadoActual = Estado::Login;
            pantalla = crearPantalla(estadoActual, window, socket);
        }
    }

    return 0;
}