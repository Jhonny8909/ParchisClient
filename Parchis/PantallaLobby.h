#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <SFML/Network.hpp>

#define HEIGHT 1080
#define WIDTH 1920

#define SERVER_PORT 55000
const sf::IpAddress SERVER_IP = sf::IpAddress(127, 0, 0, 1);

// --------------------------- FUNCIONES AUXILIARES ---------------------------

void HandleEvent(const sf::Event& event, sf::RenderWindow& window) {
	if (event.is<sf::Event::Closed>()) {
		window.close();
	}
}

void Render(sf::RenderWindow& window, sf::Sprite& BackgroundSprite, sf::Sprite& SpriteGarabatos, sf::Sprite& SpriteCrea,
	sf::Sprite& SpriteTexto, sf::Sprite& SpriteBoton, sf::Sprite& SpriteUnete, sf::Sprite& SpriteUnir, sf::Sprite& SpriteBoton2,
	sf::Sprite& BotonHover, bool showHover, sf::RectangleShape textAreaBox, sf::Text& texto, sf::Text& texto2, sf::RectangleShape BotonAreaClick,
	sf::RectangleShape textAreaBox2, sf::RectangleShape BotonAreaClick2) {

	window.clear(sf::Color(0x000000FF));
	window.draw(BackgroundSprite);
	window.draw(SpriteGarabatos);
	window.draw(SpriteCrea);
	window.draw(SpriteTexto);
	window.draw(SpriteBoton);
	window.draw(SpriteUnete);
	window.draw(SpriteUnir);
	window.draw(SpriteBoton2);
	window.draw(textAreaBox);
	window.draw(texto);
	window.draw(texto2);
	window.draw(BotonAreaClick);
	window.draw(BotonAreaClick2);
	window.draw(textAreaBox2);


	if (showHover)
		window.draw(BotonHover);
	window.display();
}

sf::Texture LoadSpriteSheet(const std::string& filePath) {
	sf::Texture texture;
	if (!texture.loadFromFile(filePath)) {
		std::cerr << "Error al cargar el sprite" << std::endl;
	}
	return texture;
}

void LoadFont(sf::Font& font, std::string str) {
	if (!font.openFromFile(str)) {
		std::cerr << "No se encontro la fuente" << str << "!!!" << std::endl;
	}
}

// --------------------------- FUNCIÓN PRINCIPAL ---------------------------

inline void Lobby()
{
	sf::TcpSocket socket;

	if (socket.connect(SERVER_IP, SERVER_PORT) != sf::Socket::Status::Done) {
		std::cerr << "Error al conectarse al server" << std::endl;
	}

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ WIDTH, HEIGHT }), "Sala Lobby");

	sf::Texture spriteBackground = LoadSpriteSheet("Lobby/Sala_fondo.png");
	sf::Texture spriteGarabatos = LoadSpriteSheet("Lobby/Sala_garabatos.png");
	sf::Texture spriteTexto = LoadSpriteSheet("Lobby/Sala_Crea.png");
	sf::Texture spriteCodigo = LoadSpriteSheet("Lobby/Sala_CODIGO_crea.png");
	sf::Texture spriteBoton = LoadSpriteSheet("Lobby/Sala_OK.png");
	sf::Texture spriteTexto2 = LoadSpriteSheet("Lobby/Sala_Unir.png");
	sf::Texture spriteCodigo2 = LoadSpriteSheet("Lobby/Sala_CODIGO_unir.png");
	sf::Texture spriteBoton2 = LoadSpriteSheet("Lobby/Sala_OK.png");
	sf::Texture HoverBoton = LoadSpriteSheet("Lobby/Sala_ok_hover.png");

	sf::Sprite BackgroundSprite = sf::Sprite(spriteBackground);
	sf::Sprite SpriteGarabatos = sf::Sprite(spriteGarabatos);
	sf::Sprite SpriteCrea = sf::Sprite(spriteTexto);
	sf::Sprite SpriteCodigoCrea = sf::Sprite(spriteCodigo);
	sf::Sprite SpriteBotonOK = sf::Sprite(spriteBoton);
	sf::Sprite SpriteUnete = sf::Sprite(spriteTexto2);
	sf::Sprite SpriteCodigo2 = sf::Sprite(spriteCodigo2);
	sf::Sprite SpriteBotonOK2 = sf::Sprite(spriteBoton2);
	sf::Sprite SpriteBotonOKHover(HoverBoton);

	SpriteCrea.setPosition({ WIDTH / 3.f - spriteTexto.getSize().x / 2, HEIGHT / 6.f - spriteTexto.getSize().y / 2 });
	SpriteCodigoCrea.setPosition({ WIDTH / 10.f, HEIGHT / 3.f });
	SpriteBotonOK.setPosition({ WIDTH / 1.3f - spriteBoton.getSize().x, HEIGHT / 2.9f });
	SpriteUnete.setPosition({ WIDTH / 3.f - spriteTexto2.getSize().x / 2, HEIGHT / 1.7f - spriteTexto2.getSize().y / 2 });
	SpriteCodigo2.setPosition({ WIDTH / 10.f , HEIGHT / 1.4f });
	SpriteBotonOK2.setPosition({ WIDTH / 1.3f - spriteBoton2.getSize().x, HEIGHT / 1.35f });

	bool showHover = false;
	std::string usuario;

	sf::FloatRect textArea({ 580.f, 390.f }, { 600.f, 80.f });
	sf::FloatRect textArea2({ 580.f, 800.f }, { 600.f, 80.f });
	sf::FloatRect BotonArea({ 1350.f, 380.f }, { 120.f, 95.f });
	sf::FloatRect BotonArea2({ 1350.f, 800.f }, { 120.f, 95.f });

	bool textInputActive = false;
	bool textInputActive2 = false;
	bool BotonClick = false;
	bool BotonClick2 = false;

	sf::Font font;
	LoadFont(font, "Fonts/Darky.otf");

	sf::Text text(font);
	text.setCharacterSize(60.f);
	text.setFillColor(sf::Color::Black);
	text.setPosition({ 600.f, 395.f });

	sf::Text text2(font);
	text2.setCharacterSize(60.f);
	text2.setFillColor(sf::Color::Black);
	text2.setPosition({ 600.f, 800.f });

	sf::RectangleShape textAreaBox(sf::Vector2f{ textArea.size });
	textAreaBox.setPosition(sf::Vector2{ textArea.position });
	textAreaBox.setFillColor(sf::Color::Transparent);
	textAreaBox.setOutlineColor(textInputActive ? sf::Color::Green : sf::Color::White);
	textAreaBox.setOutlineThickness(2.f);

	sf::RectangleShape textAreaBox2(sf::Vector2f{ textArea2.size });
	textAreaBox2.setPosition(sf::Vector2{ textArea2.position });
	textAreaBox2.setFillColor(sf::Color::Transparent);
	textAreaBox2.setOutlineColor(textInputActive2 ? sf::Color::Green : sf::Color::White);
	textAreaBox2.setOutlineThickness(2.f);

	sf::RectangleShape BotonAreaClick(sf::Vector2f{ BotonArea.size });
	BotonAreaClick.setPosition(sf::Vector2{ BotonArea.position });
	BotonAreaClick.setFillColor(sf::Color::Transparent);
	BotonAreaClick.setOutlineColor(BotonClick ? sf::Color::Green : sf::Color::White);
	BotonAreaClick.setOutlineThickness(2.f);

	sf::RectangleShape BotonAreaClick2(sf::Vector2f{ BotonArea2.size });
	BotonAreaClick2.setPosition(sf::Vector2{ BotonArea2.position });
	BotonAreaClick2.setFillColor(sf::Color::Transparent);
	BotonAreaClick2.setOutlineColor(BotonClick2 ? sf::Color::Green : sf::Color::White);
	BotonAreaClick2.setOutlineThickness(2.f);


	while (window->isOpen()) {
		sf::Vector2i mousePixel = sf::Mouse::getPosition(*window);
		sf::Vector2f mouseWorld = window->mapPixelToCoords(mousePixel);
		showHover = false;

		if (SpriteBotonOK.getGlobalBounds().contains(mouseWorld)) {
			SpriteBotonOKHover.setPosition(SpriteBotonOK.getPosition());
			showHover = true;
		}
		else if (SpriteBotonOK2.getGlobalBounds().contains(mouseWorld)) {
			SpriteBotonOKHover.setPosition(SpriteBotonOK2.getPosition());
			showHover = true;
		}

		while (const std::optional<sf::Event> event = window->pollEvent()) {
			HandleEvent(*event, *window);

			if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
				if (mouseEvent->button == sf::Mouse::Button::Left) {
					sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
					sf::Vector2f mousePosF{ static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) };

					textInputActive = textArea.contains(mousePosF);
					textInputActive2 = textArea2.contains(mousePosF);
					BotonClick = BotonArea.contains(mousePosF);
					BotonClick2 = BotonArea2.contains(mousePosF);
					std::cout << "Clic en: " << mousePosF.x << ", " << mousePosF.y << std::endl;
				}
			}
			// Entrada de texto solo si está activa
			if (textInputActive) {
				if (const auto* textEvent = event->getIf<sf::Event::TextEntered>()) {
					if (textEvent->unicode == '\b') {  // Backspace
						if (!usuario.empty()) {
							usuario.pop_back();
						}
					}
					else if (textEvent->unicode < 128 && textEvent->unicode != '\r') {
						usuario += static_cast<char>(textEvent->unicode);
					}
					text.setString(usuario);
				}
			}
			if (textInputActive2) {
				if (const auto* textEvent = event->getIf<sf::Event::TextEntered>()) {
					if (textEvent->unicode == '\b') {  // Backspace
						if (!usuario.empty()) {
							usuario.pop_back();
						}
					}
					else if (textEvent->unicode < 128 && textEvent->unicode != '\r') {
						usuario += static_cast<char>(textEvent->unicode);
					}
					text2.setString(usuario);
				}
			}

			if (BotonClick) {
				sf::Packet packet;
				std::string("CREAR") = usuario;
				packet << usuario;

				if (socket.send(packet) != sf::Socket::Status::Done) {
					std::cerr << "Error al enviar el codigo de sala al servidor." << std::endl;
				}
				else {
					std::cout << "Codigo de sala enviado: " << usuario << std::endl;
				}

				BotonClick = false;
			}
			if (BotonClick2) {
				sf::Packet packet;
				std::string("UNIRSE") = usuario;
				packet << usuario;

				if (socket.send(packet) != sf::Socket::Status::Done) {
					std::cerr << "Error al enviar el codigo de sala al servidor." << std::endl;
				}
				else {
					std::cout << "Codigo de sala enviado: " << usuario << std::endl;
				}
				BotonClick2 = false;
			}
		}

		Render(*window, BackgroundSprite, SpriteGarabatos, SpriteCrea, SpriteCodigoCrea,
			SpriteBotonOK, SpriteUnete, SpriteCodigo2, SpriteBotonOK2,
			SpriteBotonOKHover, showHover, textAreaBox, text, text2, BotonAreaClick, BotonAreaClick2, textAreaBox2);
	}

	delete window;
}