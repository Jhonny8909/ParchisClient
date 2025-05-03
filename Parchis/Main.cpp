/*#include "PantallaJuego.h"
#include "PantallaLobby.h"

enum class Estado { Login, Lobby, Juego };

int prueba() {
    Estado estadoActual = Estado::Juego; // Ejemplo: empezar en juego
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Parchis Online");

    sf::Clock clock;

    std::unique_ptr<Pantalla> estado = std::make_unique<PantallaJuego>();
	//std::unique_ptr<Pantalla> estado = std::make_unique<PantallaLobby>();

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        std::unique_ptr<Pantalla> pantalla;

        switch (estadoActual) {
        case Estado::Juego:
            pantalla = std::make_unique<PantallaJuego>();
            break;
		case Estado::Lobby:
			Lobby();
			break;
		//case Estado::Login:
		//	pantalla = std::make_unique<PantallaLogin>();
		//	break;
            // ... otros casos (Login, Lobby)
        }

        estado->handleInput(window);
        estado->update(dt);

        window.clear();
        estado->draw(window);
        window.display();

        estadoActual = Estado::Lobby;
        // Aquí puedes cambiar el estado a otro si lo deseas
    }

    return 0;
}*/