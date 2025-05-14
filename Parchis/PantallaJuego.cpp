#include "PantallaJuego.h"
#include <iostream>

using namespace std;
using namespace sf;

PantallaJuego::PantallaJuego(sf::RenderWindow& mainWindow, sf::TcpSocket& socket) : window(mainWindow), socket(socket) {
	// Inicializa los recursos del juego
	if (!resources.loadAllResources()) {
		std::cerr << "Error al cargar recursos del juego" << std::endl;
		return;
	}

    auto cargarRecursos = [&](sf::Texture& tex, const std::vector<sf::Vector2f>& posiciones) {
        sprites.reserve(sprites.size() + posiciones.size());
        for (const auto& pos : posiciones) {
            sprites.emplace_back(tex);
            sprites.back().setPosition(pos);
        }
        };
	cargarRecursos(resources.fondo, { {0, 0} });
	cargarRecursos(resources.tablero,{ {450 ,50} });
	fichasRojas.reserve(4); // Reservar espacio para 4 fichas rojas
	fichasRojas.emplace_back(FichaRoja(1, { 100, 100 },resources)); // Ejemplo de ficha roja
	fichasRojas.emplace_back(FichaRoja(2, { 200, 100 }, resources)); // Ejemplo de ficha roja
	fichasRojas.emplace_back(FichaRoja(3, { 300, 100 }, resources)); // Ejemplo de ficha roja
	fichasRojas.emplace_back(FichaRoja(4, { 400, 100 }, resources)); // Ejemplo de ficha roja
}



void PantallaJuego::handleInput(sf::RenderWindow& window) {
    
}

void PantallaJuego::handleEvents() {
	while (const std::optional event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>())
			window.close();
	}
}
void PantallaJuego::update(float dt) {
    
}

void PantallaJuego::render() {
	window.clear();
	for (const auto& sprite : sprites) {
		window.draw(sprite);
	}
	for (auto& ficha : fichasRojas) {
		ficha.dibujar(window);  // Dibuja cada ficha
	}

	
}

void PantallaJuego::draw(sf::RenderWindow& window) {
	render();
}

std::string PantallaJuego::nextState() const {
    return "";
}