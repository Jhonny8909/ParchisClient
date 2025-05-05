#pragma once
#include "Pantalla.h"
#include "Tablero.hpp"
#include "JugadorBase.hpp"  // Clase base para los jugadores
#include "Dado.hpp"
#include <memory>           // Para std::unique_ptr
#include <array>            // Para std::array
#include <vector>           // Para std::vector
#include "resources.h"

// Declaración adelantada para evitar includes circulares
class Jugador;  // Solo si realmente necesitas la clase Jugador concreta

class PantallaJuego : public Pantalla {
public:
    explicit PantallaJuego(sf::RenderWindow& mainWindow);
    void handleInput(sf::RenderWindow& window) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    std::string nextState() const override;

private:

    GameResources resources;
    sf::RenderWindow& window;
    // Componentes del juego - especificando tipos claramente
    Tablero tablero;  // Asegúrate que Tablero esté definido en Tablero.hpp
    Dado dado;        // Asegúrate que Dado esté definido en Dado.hpp

    // Sistema de jugadores - versión correcta
    std::array<std::unique_ptr<JugadorBase>, 4> jugadores;  // Usando JugadorBase

    // Estado del juego
    int jugadorActual = 0;
    int valorDado = 1;
    bool esperandoLanzamiento = true;
    bool esperandoSeleccion = false;
    std::string siguienteEstado = "juego";

    // UI
    sf::Font font;
    sf::Text textoTurno;
    sf::Text textoDado;

    // Métodos privados
    void inicializarJugadores();
    void actualizarUI();
    void cambiarTurno();
};