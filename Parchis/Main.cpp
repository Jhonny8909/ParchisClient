// main.cpp
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
        return -1;  // Si falla la carga, salir
    }

    // Crear sprites y texto usando los recursos cargados
    Sprite sprite(resources.texture);
    Sprite sprite2(resources.texture2);
    Sprite sprite3(resources.texture3);
    Text text(resources.font);
    text.setString("");

    // Resto del código original sin cambios
    sprite3.setPosition({ 450.f, 50.f });
    RenderWindow window(VideoMode({ MAXWIDTH, MAXHEIGHT }), "SFML window");

    while (window.isOpen()) {
        while (const optional<Event> event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        window.draw(sprite);
        window.draw(sprite2);
        window.draw(sprite3);
        text.setCharacterSize(100);
        text.setPosition({ 0,0 });
        window.draw(text);
        window.display();
    }

    return 0;
}