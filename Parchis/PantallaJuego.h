#pragma once
#include "Pantalla.h"
#include <SFML/Network.hpp>
#include "resources.h"
#include "FichaRoja.h"
#include "FichaAzul.h"
#include "FichaVerde.h"
#include "FichaAmarilla.h"
#include "Tablero.h"
#include "GameTypes.h" 


class PantallaJuego : public Pantalla {
public:
    explicit PantallaJuego(sf::RenderWindow& mainWindow, sf::TcpSocket& socket, ColorJugador colorAsignado);
    void handleInput(sf::RenderWindow& window) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    std::string nextState() const override;

    std::vector<sf::Sprite> sprites;
    std::vector<sf::Sprite> Dado;
	std::vector<FichaRoja> fichasRojas; // Vector para almacenar las fichas
	std::vector<FichaAzul> fichasAzules; // Vector para almacenar las fichas
	std::vector<FichaVerde> fichasVerdes; // Vector para almacenar las fichas
    std::vector<FichaAmarilla> fichasAmarillas; // Vector para almacenar las fichas
    
private:

    ColorJugador miColor;  // Color asignado por el servidor
    bool esMiTurno;

    GameResources resources;
    sf::RenderWindow& window;
    sf::TcpSocket& socket;
    int fichaSeleccionada;  
    bool dadoLanzado;       

    int dadoValue; // Valor del dado lanzado
   

    void handleEvents();
    void render();
	void LanzarDado();
    void verificarClickEnFichas(const sf::Vector2f& mousePos);
    int getIndiceFichaClickeada(const sf::Vector2f& mousePos) const;
    Tablero board; // Asegúrate de tener este miembro
    void avanzarFichaSeleccionada();

    // Para la animación del dado
    sf::Clock animacionDadoClock;
    bool enAnimacionDado = false;
    float tiempoAnimacionDado = 1.5f; // Duración total de la animación en segundos
    int frameActualDado = 0;
    const int totalFramesAnimacion = 60; // Número de cambios durante la animación

    void actualizarAnimacionDado();
    void iniciarAnimacionDado();
    void detenerAnimacionDado();
    void procesarPaquetesRed();
};