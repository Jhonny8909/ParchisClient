#include "PantallaJuego.h"
#include "PantallaLobby.h"
// #include "PantallaLogin.h" // si la implementas

enum class Estado { Login, Lobby, Juego, Ninguno };

std::unique_ptr<Pantalla> crearPantalla(Estado estado, sf::RenderWindow& window) {
    switch (estado) {
    case Estado::Lobby: return std::make_unique<LobbyScreen>(window);
    case Estado::Juego: return std::make_unique<PantallaJuego>(window);
        // case Estado::Login: return std::make_unique<PantallaLogin>(window);
    default: return nullptr;
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Parchis Online");
    sf::Clock clock;

    Estado estadoActual = Estado::Lobby;
    std::unique_ptr<Pantalla> pantalla = crearPantalla(estadoActual, window);

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        pantalla->handleInput(window);
        pantalla->update(dt);

        window.clear();
        pantalla->draw(window);
        window.display();

        std::string siguiente = pantalla->nextState();
        if (siguiente == "juego") {
            estadoActual = Estado::Juego;
            pantalla = crearPantalla(estadoActual, window);
        }
        else if (siguiente == "lobby") {
            estadoActual = Estado::Lobby;
            pantalla = crearPantalla(estadoActual, window);
        }
        else if (siguiente == "login") {
            estadoActual = Estado::Login;
            pantalla = crearPantalla(estadoActual, window);
        }
    }

    return 0;
}