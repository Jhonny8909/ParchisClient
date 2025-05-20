#include "PantallaJuego.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;
using namespace sf;


PantallaJuego::PantallaJuego(sf::RenderWindow& mainWindow, sf::TcpSocket& socket)
	: window(mainWindow), socket(socket), dadoValue(1), fichaSeleccionada(-1), dadoLanzado(false) {

	std::srand(static_cast<unsigned>(std::time(nullptr)));
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

	auto cargarDado = [&](sf::Texture& tex, const std::vector<sf::Vector2f>& posiciones) {
		Dado.reserve(Dado.size() + posiciones.size());
		for (const auto& pos : posiciones) {
			Dado.emplace_back(tex);
			Dado.back().setPosition(pos);
		}
		};

	cargarRecursos(resources.fondo, { {0, 0} });
	cargarRecursos(resources.tablero,{ {450 ,50} });
	cargarDado(resources.dado1, { { 0, 0 } });
	fichasRojas.reserve(4); // Reservar espacio para 4 fichas rojas
	fichasRojas.emplace_back(FichaRoja(1, { 880, 130 }, resources)); // Ejemplo de ficha roja
	fichasRojas.emplace_back(FichaRoja(2, { 200, 100 }, resources)); // Ejemplo de ficha roja
	fichasRojas.emplace_back(FichaRoja(3, { 300, 100 }, resources)); // Ejemplo de ficha roja
	fichasRojas.emplace_back(FichaRoja(4, { 400, 100 }, resources)); // Ejemplo de ficha roja
	
}



void PantallaJuego::handleInput(sf::RenderWindow& window) {
	handleEvents();
}

void PantallaJuego::handleEvents() {
	while (const std::optional event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			window.close();
		}

		// Detectar tecla Enter presionada
		if (const sf::Event::KeyPressed* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
			if (keyPressed->code == sf::Keyboard::Key::Enter ) {
				LanzarDado();
				std::cout << "Dado lanzado: " << dadoValue << std::endl;
			}
		}
			
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
	drawDado(dadoValue);
}

void PantallaJuego::draw(sf::RenderWindow& window) {
	render();
}

void PantallaJuego::drawDado(int dadoValue) {
	/*switch (dadoValue)
	{
		case 1:
			window.draw(Dado[0]);
			break;
		case 2:
			window.draw(Dado[1]);
			break;
		case 3:
			window.draw(Dado[2]);
			break;
		case 4:
			window.draw(Dado[3]);
			break;
		case 5:
			window.draw(Dado[4]);
			break;
		case 6:
			window.draw(Dado[5]);
			break;
	default:
		break;
	}*/
}

void PantallaJuego::LanzarDado() {
	dadoValue = std::rand() % 6 + 1;
	dadoLanzado = true;
	fichaSeleccionada = -1;
	std::cout << "Dado: " << dadoValue << ". Selecciona una ficha.\n";
}

std::string PantallaJuego::nextState() const {
    return "";
}