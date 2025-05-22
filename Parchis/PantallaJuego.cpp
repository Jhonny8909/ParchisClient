#include "PantallaJuego.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;
using namespace sf;


PantallaJuego::PantallaJuego(sf::RenderWindow& mainWindow, sf::TcpSocket& socket, ColorJugador colorAsignado)
	: window(mainWindow), socket(socket), miColor(colorAsignado), esMiTurno(false) {


	std::string colorStr;
	switch (miColor) {
	case ColorJugador::ROJO: colorStr = "ROJO"; break;
	case ColorJugador::AMARILLO: colorStr = "AMARILLO"; break;
	case ColorJugador::VERDE: colorStr = "VERDE"; break;
	case ColorJugador::AZUL: colorStr = "AZUL"; break;
	default: colorStr = "NINGUNO";
	}
	std::cout << "Color asignado: " << colorStr << std::endl;

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

	//Cargar los recursos de la pantalla de juego

	cargarRecursos(resources.fondo, { {0, 0} });
	cargarRecursos(resources.tablero, { {960 ,540} });

	cargarDado(resources.dado1, { { 1770, 900 } });
	cargarDado(resources.dado2, { { 1770, 900 } });
	cargarDado(resources.dado3, { { 1770, 900 } });
	cargarDado(resources.dado4, { { 1770, 900 } });
	cargarDado(resources.dado5, { { 1770, 900 } });
	cargarDado(resources.dado6, { { 1770, 900 } });

	//Modificar el origen y escala

	sprites[1].setOrigin({ 533.5f, 488.0f });
	Dado[0].setOrigin({ 288, 300 });
	Dado[1].setOrigin({ 288, 300 });
	Dado[2].setOrigin({ 288, 300 });
	Dado[3].setOrigin({ 288, 300 });
	Dado[4].setOrigin({ 288, 300 });
	Dado[5].setOrigin({ 288, 300 });

	Dado[0].setScale({ 0.5f, 0.5f });
	Dado[1].setScale({ 0.5f, 0.5f });
	Dado[2].setScale({ 0.5f, 0.5f });
	Dado[3].setScale({ 0.5f, 0.5f });
	Dado[4].setScale({ 0.5f, 0.5f });
	Dado[5].setScale({ 0.5f, 0.5f });

	//Cargar las fichas de los jugadores

	fichasRojas.reserve(4); // Reservar espacio para 4 fichas rojas

	fichasRojas.emplace_back(FichaRoja(1, { 620, 220 }, resources));
	fichasRojas.emplace_back(FichaRoja(2, { 620, 340 }, resources));
	fichasRojas.emplace_back(FichaRoja(3, { 750, 220 }, resources));
	fichasRojas.emplace_back(FichaRoja(4, { 750, 340 }, resources));

	fichasAzules.reserve(4); // Reservar espacio para 4 fichas azules

	fichasAzules.emplace_back(FichaAzul(1, { 1165, 740 }, resources));
	fichasAzules.emplace_back(FichaAzul(2, { 1165, 850 }, resources));
	fichasAzules.emplace_back(FichaAzul(3, { 1300, 740 }, resources));
	fichasAzules.emplace_back(FichaAzul(4, { 1300, 850 }, resources));

	fichasAmarillas.reserve(4); // Reservar espacio para 4 fichas amarillas

	fichasAmarillas.emplace_back(FichaAmarilla(1, { 620, 740 }, resources));
	fichasAmarillas.emplace_back(FichaAmarilla(2, { 620, 850 }, resources));
	fichasAmarillas.emplace_back(FichaAmarilla(3, { 750, 740 }, resources));
	fichasAmarillas.emplace_back(FichaAmarilla(4, { 750, 850 }, resources));

	fichasVerdes.reserve(4); // Reservar espacio para 4 fichas verdes

	fichasVerdes.emplace_back(FichaVerde(1, { 1165, 220 }, resources));
	fichasVerdes.emplace_back(FichaVerde(2, { 1165, 340 }, resources));
	fichasVerdes.emplace_back(FichaVerde(3, { 1300, 220 }, resources));
	fichasVerdes.emplace_back(FichaVerde(4, { 1300, 340 }, resources));
}

void PantallaJuego::handleInput(sf::RenderWindow& window) {
	handleEvents();
}

void PantallaJuego::handleEvents() {
	while (const std::optional event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			window.close();
		}

		// Solo permitir acciones si es mi turno
		if (esMiTurno) {
			// Detectar tecla Enter para lanzar dado
			if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
				if (keyPressed->code == sf::Keyboard::Key::Enter) {
					LanzarDado();
				}
			}

			// Detectar click en fichas de mi color
			if (const auto* mousePress = event->getIf<sf::Event::MouseButtonPressed>()) {
				if (mousePress->button == sf::Mouse::Button::Left) {
					const sf::Vector2f mousePos = window.mapPixelToCoords(
						sf::Mouse::getPosition(window),
						window.getView()
					);
					verificarClickEnFichas(mousePos);
				}
			}
		}
	}
}

int PantallaJuego::getIndiceFichaClickeada(const sf::Vector2f& mousePos) const {
	// Verificar fichas rojas (índices 0-3)
	for (size_t i = 0; i < fichasRojas.size(); ++i) {
		if (fichasRojas[i].contiene(mousePos)) {
			std::cout << "Ficha Roja " << (i + 1) << " clickeada\n";
			return i;
		}
	}

	// Verificar fichas azules (índices 4-7)
	for (size_t i = 0; i < fichasAzules.size(); ++i) {
		if (fichasAzules[i].contiene(mousePos)) {
			std::cout << "Ficha Azul " << (i + 1) << " clickeada\n";
			return i + fichasRojas.size();
		}
	}

	// Verificar fichas amarillas (índices 8-11)
	for (size_t i = 0; i < fichasAmarillas.size(); ++i) {
		if (fichasAmarillas[i].contiene(mousePos)) {
			std::cout << "Ficha Amarilla " << (i + 1) << " clickeada\n";
			return i + fichasRojas.size() + fichasAzules.size();
		}
	}

	// Verificar fichas verdes (índices 12-15)
	for (size_t i = 0; i < fichasVerdes.size(); ++i) {
		if (fichasVerdes[i].contiene(mousePos)) {
			std::cout << "Ficha Verde " << (i + 1) << " clickeada\n";
			return i + fichasRojas.size() + fichasAzules.size() + fichasAmarillas.size();
		}
	}

	return -1; // Ninguna ficha fue clickeada
}

void PantallaJuego::verificarClickEnFichas(const sf::Vector2f& mousePos) {
	// Solo verificar las fichas de mi color
	switch (miColor) {
	case ColorJugador::ROJO:
		for (size_t i = 0; i < fichasRojas.size(); ++i) {
			if (fichasRojas[i].contiene(mousePos)) {
				fichaSeleccionada = i;
				fichasRojas[i].seleccionar();
				std::cout << "Ficha Roja " << (i + 1) << " seleccionada\n";
				return;
			}
		}
		break;

	case ColorJugador::AMARILLO:
		for (size_t i = 0; i < fichasAmarillas.size(); ++i) {
			if (fichasAmarillas[i].contiene(mousePos)) {
				fichaSeleccionada = i + 8; // Offset para amarillas
				fichasAmarillas[i].seleccionar();
				std::cout << "Ficha Amarilla " << (i + 1) << " seleccionada\n";
				return;
			}
		}
		break;
	case ColorJugador::VERDE:
		for (size_t i = 0; i < fichasVerdes.size(); ++i) {
			if (fichasVerdes[i].contiene(mousePos)) {
				fichaSeleccionada = i + 12; // Offset para amarillas
				fichasVerdes[i].seleccionar();
				std::cout << "Ficha Verde " << (i + 1) << " seleccionada\n";
				return;
			}
		}
		break;
	case ColorJugador::AZUL:
		for (size_t i = 0; i < fichasAzules.size(); ++i) {
			if (fichasAzules[i].contiene(mousePos)) {
				fichaSeleccionada = i + 4; // Offset para amarillas
				fichasAzules[i].seleccionar();
				std::cout << "Ficha Azul " << (i + 1) << " seleccionada\n";
				return;
			}
		}
		break;
	}

	// Si llegamos aquí, no se clickeó una ficha válida
	fichaSeleccionada = -1;
}

void PantallaJuego::avanzarFichaSeleccionada() {
	if (fichaSeleccionada >= 0) {
		if (fichaSeleccionada < 4) { // Fichas rojas
			fichasRojas[fichaSeleccionada].avanzarUnaPosicion(board.positions);
		}
	}
}

void PantallaJuego::update(float dt) {
	
	procesarPaquetesRed();

	if (enAnimacionDado) {
		actualizarAnimacionDado();
	}
}

void PantallaJuego::procesarPaquetesRed() {
	// Procesar mensajes de red
	sf::Packet packet;
	while (socket.receive(packet) == sf::Socket::Status::Done) {
		std::string tipo;
		if (packet >> tipo) {
			if (tipo == "TURNO_ACTUAL") {
				int jugadorActual;
				if (packet >> jugadorActual) {
					esMiTurno = (jugadorActual == static_cast<int>(miColor));
				}
			}
		}
	}
}

void PantallaJuego::render() {
	window.clear();

	// Dibujar fondo y tablero
	for (const auto& sprite : sprites) {
		window.draw(sprite);
	}

	// Dibujar todas las fichas pero resaltar solo las mías
	for (auto& ficha : fichasRojas) {
		ficha.dibujar(window, miColor == ColorJugador::ROJO);
	}
	for (auto& ficha : fichasAmarillas) {
		ficha.dibujar(window, miColor == ColorJugador::AMARILLO);
	}
	for (auto& ficha : fichasAzules) {
		ficha.dibujar(window, miColor == ColorJugador::AZUL);
	}
	for (auto& ficha : fichasVerdes) {
		ficha.dibujar(window, miColor == ColorJugador::VERDE);
	}

	// Dibujar dado
	if (dadoValue >= 1 && dadoValue <= 6) {
		window.draw(Dado[dadoValue - 1]);
	}
}

void PantallaJuego::draw(sf::RenderWindow& window) {
	render();
}

void PantallaJuego::LanzarDado() {
	if (!enAnimacionDado) {
		iniciarAnimacionDado();
	}
}

std::string PantallaJuego::nextState() const {
    return "";
}

void PantallaJuego::iniciarAnimacionDado() {
	enAnimacionDado = true;
	animacionDadoClock.restart();
	frameActualDado = 0;
	dadoValue = 0; // Valor temporal durante animación
}

void PantallaJuego::detenerAnimacionDado() {
	enAnimacionDado = false;
	dadoValue = 1 + (rand() / (RAND_MAX / 6 + 1));
	dadoLanzado = true;
	fichaSeleccionada = -1;
	std::cout << "Dado lanzado: " << dadoValue << std::endl;
}

void PantallaJuego::actualizarAnimacionDado() {
	if (!enAnimacionDado) return;

	float tiempoTranscurrido = animacionDadoClock.getElapsedTime().asSeconds();

	if (tiempoTranscurrido >= tiempoAnimacionDado) {
		detenerAnimacionDado();
		return;
	}

	// Calcular el frame actual basado en el tiempo transcurrido
	int nuevoFrame = static_cast<int>((tiempoTranscurrido / tiempoAnimacionDado) * totalFramesAnimacion);

	// Solo actualizar si cambiamos de frame
	if (nuevoFrame != frameActualDado) {
		frameActualDado = nuevoFrame;
		// Mostrar una cara aleatoria durante la animación (excepto la última)
		if (frameActualDado < totalFramesAnimacion - 1) {
			dadoValue = std::rand() % 6 + 1;
		}
	}
}