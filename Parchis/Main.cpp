#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "resources.h"  // Incluir nuestro nuevo header

using namespace sf;
using namespace std;

#define MAXWIDTH 1920
#define MAXHEIGHT 1080

int main() {
    string usuario;

    // Cargar todos los recursos
    GameResources resources;
    if (!resources.loadAllResources()) {
        return -1;
    }

    // Crear sprites y texto usando los recursos cargados
	Sprite sprite(resources.texture);//Fondo
	Sprite sprite2(resources.texture2);//Decoracion
	Sprite sprite3(resources.texture3); //Tablero

	Sprite sprite4(resources.texture4); //FICHA ROJA
	Sprite sprite5(resources.texture4); //FICHA ROJA
	Sprite sprite6(resources.texture4); //FICHA ROJA
	Sprite sprite7(resources.texture4); //FICHA ROJA

	Sprite sprite8(resources.texture5); //FICHA AMARILLA
	Sprite sprite9(resources.texture5);	//FICHA AMARILLA
	Sprite sprite10(resources.texture5); //FICHA AMARILLA
	Sprite sprite11(resources.texture5); //FICHA AMARILLA

	Sprite sprite12(resources.texture6); //FICHA AZUL
	Sprite sprite13(resources.texture6); //FICHA AZUL
	Sprite sprite14(resources.texture6); //FICHA AZUL
	Sprite sprite15(resources.texture6); //FICHA AZUL

	Sprite sprite16(resources.tex2); //FICHA VERDE
	Sprite sprite17(resources.tex2); //FICHA VERDE
	Sprite sprite18(resources.tex2); //FICHA VERDE	
	Sprite sprite19(resources.tex2); //FICHA VERDE

	// configurar los sprites
	sprite3.setPosition({ 450.f, 50.f }); //TABLERO

	sprite4.setPosition({ 610.f, 190.f }); //FICHA ROJA
	sprite5.setPosition({ 745.f, 190.f }); //FICHA ROJA
	sprite6.setPosition({ 610.f, 300.f }); //FICHA ROJA
	sprite7.setPosition({ 745.f, 300.f }); //FICHA ROJA

	sprite8.setPosition({ 610.f, 700.f }); //FICHA AMARILLA
	sprite9.setPosition({ 745.f, 700.f }); //FICHA AMARILLA
	sprite10.setPosition({ 610.f, 810.f }); //FICHA AMARILLA
	sprite11.setPosition({ 745.f, 810.f }); //FICHA AMARILLA

	sprite12.setPosition({ 1160.f, 700.f }); //FICHA AZUL
	sprite13.setPosition({ 1290.f, 700.f }); //FICHA AZUL
	sprite14.setPosition({ 1160.f, 810.f }); //FICHA AZUL
	sprite15.setPosition({ 1290.f, 810.f }); //FICHA AZUL

	sprite16.setPosition({ 1160.f, 190.f }); //FICHA VERDE
	sprite17.setPosition({ 1290.f, 190.f }); //FICHA VERDE
	sprite18.setPosition({ 1160.f, 300.f }); //FICHA VERDE
	sprite19.setPosition({ 1290.f, 300.f }); //FICHA VERDE

    RenderWindow window(VideoMode({ MAXWIDTH, MAXHEIGHT }), "SFML window");

    while (window.isOpen()) {
        while (const optional<Event> event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }
        }

        window.clear();

		// Dibujar los sprites
		window.draw(sprite);//Fondo
		window.draw(sprite2); //Decoracion
		window.draw(sprite3); //Tablero

		window.draw(sprite4); //FICHA ROJA
		window.draw(sprite5); //FICHA ROJA
		window.draw(sprite6); //FICHA ROJA
		window.draw(sprite7); //FICHA ROJA

		window.draw(sprite8); //FICHA AMARILLA
		window.draw(sprite9); //FICHA AMARILLA
		window.draw(sprite10); //FICHA AMARILLA
		window.draw(sprite11); //FICHA AMARILLA

		window.draw(sprite12); //FICHA AZUL
		window.draw(sprite13); //FICHA AZUL
		window.draw(sprite14); //FICHA AZUL
		window.draw(sprite15); //FICHA AZUL

		window.draw(sprite16); //FICHA VERDE
		window.draw(sprite17); //FICHA VERDE
		window.draw(sprite18); //FICHA VERDE
		window.draw(sprite19); //FICHA VERDE

        window.display();
    }

    return 0;
}