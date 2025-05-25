#include "PantallaJuego.h"
#include "PantallaLobby.h"
#include "PantallaLogin.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <memory>
#include <iostream>

constexpr unsigned short SERVER_PORT = 55000;
const sf::IpAddress SERVER_IP = sf::IpAddress(127,0,0,1); // Cambiado a formato string

enum class Estado { Login, Lobby, Juego, Ninguno };

std::unique_ptr<Pantalla> crearPantalla(
    Estado estado,
    sf::RenderWindow& window,
    sf::TcpSocket& socket,
    int colorJugador = -1,  // Valor por defecto para otros estados
    const std::string& codigoSala = "") // Valor por defecto
{
    switch (estado) {
    case Estado::Login:
        return std::make_unique<PantallaLogin>(window, socket);

    case Estado::Lobby:
        return std::make_unique<LobbyScreen>(window, socket);

    case Estado::Juego:
        // Pasamos los parámetros directamente sin tipos
        return std::make_unique<PantallaJuego>(window, socket, colorJugador, codigoSala);

    default:
        return nullptr;
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Parchis Online");
    sf::TcpSocket socket;

    // Conexión al servidor
    if (socket.connect(SERVER_IP, SERVER_PORT) != sf::Socket::Status::Done) {
        std::cerr << "Error al conectar al servidor" << std::endl;
        return -1;
    }
    std::cout << "[CLIENTE] Conectado al servidor " << SERVER_IP << ":" << SERVER_PORT << std::endl;

    socket.setBlocking(false);

    Estado estadoActual = Estado::Login;
    auto pantalla = crearPantalla(estadoActual, window, socket);

    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        // Procesar mensajes de red
        sf::Packet packet;
        while (socket.receive(packet) == sf::Socket::Status::Done) {
            std::string tipo;
            if (packet >> tipo) {
                if (tipo == "GAME_START") {
                    int colorJugador;
                    std::string codigoSala;
                    if (packet >> colorJugador >> codigoSala) {
                        // Validar el color recibido
                        if (colorJugador < 0 || colorJugador > 3) {
                            std::cerr << "Color inválido recibido: " << colorJugador << std::endl;
                            colorJugador = 4; // NINGUNO
                        }

                        estadoActual = Estado::Juego;
                        pantalla = std::make_unique<PantallaJuego>(window, socket, colorJugador, codigoSala);
                    }
                }
                else if (pantalla != nullptr) {
                    dynamic_cast<PantallaJuego*>(pantalla.get())->procesarPaqueteExterno(packet);
                }
            }
            packet.clear();
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
            // Usar el constructor sin paquete
            pantalla = crearPantalla(estadoActual, window, socket, 0, "");
        }
    } // <-- Esta llave cierra el while (window.isOpen())
    return 0;
}

std::string colorIntToString(int color) {
    switch (color) {
    case 0: return "ROJO";
    case 1: return "AMARILLO";
    case 2: return "VERDE";
    case 3: return "AZUL";
    default: return "NINGUNO";
    }
}