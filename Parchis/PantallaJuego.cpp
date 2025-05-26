#include "PantallaJuego.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;
using namespace sf;

PantallaJuego::PantallaJuego(sf::RenderWindow& mainWindow,sf::TcpSocket& socket,int colorJugador,const std::string& codigoSala)
	: window(mainWindow),socket(socket),esMiTurno(false),codigoLobby(codigoSala)  // Guardamos el código en miembro de clase
{
	socket.setBlocking(false);
	miColor = static_cast<ColorJugador>(colorJugador);

	std::cout << "Juego iniciado - Sala: " << codigoLobby
		<< ", Color: " << static_cast<int>(miColor) << std::endl;

	std::cout << "Color asignado: ";
	switch (miColor) {
	case ColorJugador::ROJO: std::cout << "ROJO"; break;
	case ColorJugador::AMARILLO: std::cout << "AMARILLO"; break;
	case ColorJugador::VERDE: std::cout << "VERDE"; break;
	case ColorJugador::AZUL: std::cout << "AZUL"; break;
	default: std::cout << "NINGUNO";
	}
	std::cout << std::endl;

	// Limpiar cualquier paquete residual en el buffer
	sf::Packet tempPacket;
	while (socket.receive(tempPacket) == sf::Socket::Status::Done) {
		tempPacket.clear();
	}

	// Resto de la inicialización (sin cambios)
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

void PantallaJuego::handleTurnEvents(const sf::Event& event) { // ¡Nombre y parámetros correctos!
	if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
		if (keyPressed->code == sf::Keyboard::Key::Enter) {
			LanzarDado();
		}
	}

	if (const auto* mousePress = event.getIf<sf::Event::MouseButtonPressed>()) {
		if (mousePress->button == sf::Mouse::Button::Left) {
			verificarClickEnFichas(getMousePosition());
		}
	}
}

sf::Vector2f PantallaJuego::getMousePosition() const {
	return window.mapPixelToCoords(
		sf::Mouse::getPosition(window),
		window.getView()
	);
}

void PantallaJuego::handleEvents() {
	while (const std::optional event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			window.close();
			return;
		}

		if (!esMiTurno) {
#ifdef DEBUG
			std::cout << "[DEBUG] Input ignorado (no es tu turno)" << std::endl;
#endif
			continue;
		}

		handleTurnEvents(*event);
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
	switch (miColor) {
	case ColorJugador::ROJO:
		for (size_t i = 0; i < fichasRojas.size(); ++i) {
			if (fichasRojas[i].contiene(mousePos)) {
				fichaSeleccionada = i; // Índice 0-3
				fichasRojas[i].seleccionar();
				return;
			}
		}
		break;

	case ColorJugador::AZUL:
		for (size_t i = 0; i < fichasAzules.size(); ++i) {
			if (fichasAzules[i].contiene(mousePos)) {
				fichaSeleccionada = i + 4; // Índice 4-7
				fichasAzules[i].seleccionar();
				return;
			}
		}
		break;

	case ColorJugador::AMARILLO:
		for (size_t i = 0; i < fichasAmarillas.size(); ++i) {
			if (fichasAmarillas[i].contiene(mousePos)) {
				fichaSeleccionada = i + 8; // Índice 8-11
				fichasAmarillas[i].seleccionar();
				return;
			}
		}
		break;

	case ColorJugador::VERDE:
		for (size_t i = 0; i < fichasVerdes.size(); ++i) {
			if (fichasVerdes[i].contiene(mousePos)) {
				fichaSeleccionada = i + 12; // Índice 12-15
				fichasVerdes[i].seleccionar();
				return;
			}
		}
		break;
	}
	fichaSeleccionada = -1; // Ninguna ficha seleccionada
}

void PantallaJuego::avanzarFichaSeleccionada() {
	if (fichaSeleccionada < 0) return;

	if (fichaSeleccionada < 4) { // Rojas (0-3)
		fichasRojas[fichaSeleccionada].avanzarUnaPosicion(board.positions);
	}
	else if (fichaSeleccionada < 8) { // Azules (4-7)
		fichasAzules[fichaSeleccionada - 4].avanzarUnaPosicion(board.positions);
	}
	else if (fichaSeleccionada < 12) { // Amarillas (8-11)
		fichasAmarillas[fichaSeleccionada - 8].avanzarUnaPosicion(board.positions);
	}
	else if (fichaSeleccionada < 16) { // Verdes (12-15)
		fichasVerdes[fichaSeleccionada - 12].avanzarUnaPosicion(board.positions);
	}
}


void PantallaJuego::finalizarTurno() {
	if (!esMiTurno) return;

	sf::Packet packet;
	packet << "FIN_TURNO" << codigoLobby << miColor;

	if (socket.send(packet) == sf::Socket::Status::Done) {
		esMiTurno = false;
		std::cout << "[CLIENTE] Turno finalizado notificado al servidor" << std::endl;
	}
}

void PantallaJuego::procesarPaqueteRed(sf::Packet& packet) {
	// Guardar la posición inicial del paquete
	std::size_t initialPos = packet.getReadPosition();

	std::string tipo;
	if (!(packet >> tipo)) {
		std::cerr << "[CLIENT] Error al leer tipo de paquete. Posición: "
			<< initialPos << "/" << packet.getDataSize() << std::endl;
		packet.clear();
		return;
	}

	std::cout << "[CLIENT] Paquete completo (" << packet.getDataSize()
		<< " bytes). Tipo: " << tipo << std::endl;

	if (tipo == "DADO_RESULTADO") {
		int valor;
		int colorInt;
		if (packet >> valor >> colorInt) {
			ColorJugador color = static_cast<ColorJugador>(colorInt);
			std::cout << "[CLIENT] Resultado dado - Valor: " << valor
				<< ", Color: " << colorInt << std::endl;

			if (color == miColor) {
				detenerAnimacionDado(valor);
				dadoValue = valor;
				esMiTurno = true;
			}
		}
		else {
			std::cerr << "[CLIENT] Error leyendo datos de DADO_RESULTADO" << std::endl;
		}
	}
	else if (tipo == "CAMBIAR_TURNO") {
		bool turnoActual;
		if (packet >> turnoActual) {
			esMiTurno = turnoActual;
			std::cout << "[CLIENT] Turno actualizado: " << turnoActual << std::endl;
		}
		else {
			std::cerr << "[CLIENT] Error leyendo CAMBIAR_TURNO" << std::endl;
		}
	}
	else {
		std::cout << "[CLIENT] Tipo de paquete no manejado: " << tipo << std::endl;
		// Mostrar contenido restante del paquete para debug
		std::string remaining;
		while (packet >> remaining) {
			std::cout << "  Contenido extra: " << remaining << std::endl;
		}
	}
}

void PantallaJuego::update(float dt) {
	// Verificar conexión periódicamente
	static float connectionCheckTimer = 0;
	connectionCheckTimer += dt;

	if (connectionCheckTimer > 5.0f) { // Cada 5 segundos
		connectionCheckTimer = 0;

		sf::Packet pingPacket;
		pingPacket << "PING" << codigoLobby;

		bool wasBlocking = socket.isBlocking();
		socket.setBlocking(true);
		sf::Socket::Status status = socket.send(pingPacket);
		socket.setBlocking(wasBlocking);

		if (status != sf::Socket::Status::Done) {
			std::cerr << "[CLIENTE] Error de conexión con el servidor" << std::endl;
		}
	}

	if (enAnimacionDado) {
		actualizarAnimacionDado();
	}
}


void PantallaJuego::render() {
	window.clear();

	// Dibujar fondo y tablero
	for (const auto& sprite : sprites) {
		window.draw(sprite);
	}

	// Dibujar todas las fichas de todos los jugadores
	for (auto& ficha : fichasRojas) {
		ficha.dibujar(window, miColor == ColorJugador::ROJO); // Resaltar las propias
	}
	for (auto& ficha : fichasAmarillas) {
		ficha.dibujar(window, miColor == ColorJugador::AMARILLO);
	}
	for (auto& ficha : fichasVerdes) {
		ficha.dibujar(window, miColor == ColorJugador::VERDE);
	}
	for (auto& ficha : fichasAzules) {
		ficha.dibujar(window, miColor == ColorJugador::AZUL);
	}

	// Dibujar dado (animación o resultado final)
	if (enAnimacionDado) {
		// Mostrar cara aleatoria durante animación
		int caraMostrar = (dadoValue > 0 && dadoValue <= 6) ? dadoValue - 1 : std::rand() % 6;
		window.draw(Dado[caraMostrar]);
	}
	else if (dadoValue >= 1 && dadoValue <= 6) {
		// Mostrar resultado final
		window.draw(Dado[dadoValue - 1]);
	}
}

void PantallaJuego::draw(sf::RenderWindow& window) {
	render();
}

void PantallaJuego::LanzarDado() {
	if (!esMiTurno) return;

	// Cambiar temporalmente a modo bloqueante para enviar
	bool wasBlocking = socket.isBlocking();
	socket.setBlocking(true);

	sf::Packet packet;
	packet << "TIRAR_DADO" << codigoLobby << miColor;

	sf::Socket::Status status = socket.send(packet);
	socket.setBlocking(wasBlocking); // Restaurar estado original

	if (status != sf::Socket::Status::Done) {
		std::cerr << "[CLIENTE] Error al enviar lanzamiento de dado: " << static_cast<int>(status) << std::endl;
		enAnimacionDado = false;
	}
	else {
		std::cout << "[CLIENTE] Paquete TIRAR_DADO enviado correctamente" << std::endl;
		iniciarAnimacionDado();
	}
}

void PantallaJuego::MoverFicha(int fichaId, int nuevaPos) {
	if (!esMiTurno) return;

	sf::Packet packet;
	packet << "MOVIMIENTO" << codigoLobby << miColor << fichaId << nuevaPos;
	if (socket.send(packet) == sf::Socket::Status::Done) {
		// El servidor se encargará de cambiar el turno
		esMiTurno = false; // Asumimos que el turno termina después del movimiento
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

void PantallaJuego::detenerAnimacionDado(int valorFinal) {
	enAnimacionDado = false;
	dadoValue = valorFinal; // Usa el valor del servidor
	dadoLanzado = true;
	std::cout << "Dado lanzado (valor servidor): " << dadoValue << std::endl;
}

void PantallaJuego::actualizarAnimacionDado() {
	if (!enAnimacionDado) return;

	float tiempoTranscurrido = animacionDadoClock.getElapsedTime().asSeconds();

	// Actualizar frame de animación
	frameActualDado = static_cast<int>((tiempoTranscurrido / tiempoAnimacionDado) * totalFramesAnimacion);

	// Cambiar cara del dado durante animación (excepto último frame)
	if (frameActualDado < totalFramesAnimacion - 1) {
		dadoValue = (std::rand() % 6) + 1; // Valor temporal
	}

	// Finalizar animación si ha terminado el tiempo
	if (tiempoTranscurrido >= tiempoAnimacionDado) {
		enAnimacionDado = false;
		std::cout << "[ANIMACION] Esperando valor real del servidor..." << std::endl;
	}
}