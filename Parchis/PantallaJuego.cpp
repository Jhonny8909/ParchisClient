#include "PantallaJuego.h"
#include "JugadorRojo.hpp"
#include "JugadorAmarillo.hpp"
#include "JugadorAzul.hpp"
#include "JugadorVerde.hpp"
#include "resources.h"  // Usando tu archivo resources.h

PantallaJuego::PantallaJuego(sf::RenderWindow& mainWindow)
    : window(mainWindow),
    tablero(),
    dado(resources), // Correcta inicialización del dado
    jugadorActual(0),
    valorDado(1),
    esperandoLanzamiento(true),
    esperandoSeleccion(false) {

    // Cargar recursos
    if (!resources.loadAllResources()) {
        throw std::runtime_error("Error al cargar recursos");
    }

    // Configurar dado (si usas texturas individuales)
    dado = Dado({ resources });

    inicializarJugadores();

    // Configurar UI
    if (!font.openFromFile("assets/fuentes/arial.ttf")) {
        throw std::runtime_error("Error al cargar fuente");
    }
    textoTurno.setFont(font);
    textoDado.setFont(font);
    actualizarUI();
}

void PantallaJuego::inicializarJugadores() {
    // Solo inicializamos el jugador amarillo
    jugadores[1] == std::make_unique<JugadorAmarillo>(resources);
    jugadores[1]->inicializarFichas();  // Asegúrate de llamar esto

    // Los otros jugadores pueden ser nullptr temporalmente
    jugadores[0] = nullptr;
    jugadores[2] = nullptr;
    jugadores[3] = nullptr;

    jugadorActual = 1;  // Empezamos con el jugador amarillo
}

void PantallaJuego::handleInput(sf::RenderWindow& window) {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) window.close();

        if (esperandoLanzamiento &&
            event->is<sf::Event::KeyPressed>() &&
            event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Space) {

            dado.lanzar();
            esperandoLanzamiento = false;
        }

        if (esperandoSeleccion &&
            event->is<sf::Event::MouseButtonPressed>() &&
            event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left) {

            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            auto& jugador = jugadores[jugadorActual];

            for (int i = 0; i < jugador->getFichas().size(); ++i) {
                if (jugador->getFichas()[i].getSprite().getGlobalBounds().contains(mousePos)) {
                    tablero.moverFicha(jugador->getFichas()[i], dado.getValor(), jugadores);
                    if (dado.getValor() != 6) cambiarTurno();
                    break;
                }
            }
        }
    }
}

void PantallaJuego::update(float dt) {
    dado.actualizar(dt);
    if (!dado.estaRodando() && !esperandoLanzamiento) {
        valorDado = dado.getValor();
        esperandoSeleccion = true;
        actualizarUI();
    }
}

void PantallaJuego::draw(sf::RenderWindow& window) {
    window.clear();

    // Dibujar tablero y fichas
    tablero.dibujar(window);

    if (jugadores[1]) {
        jugadores[1]->dibujarFichas(window);
    }

    // Dibujar UI
    window.draw(textoTurno);
    window.draw(textoDado);
    dado.dibujar(window);

    window.display();
}