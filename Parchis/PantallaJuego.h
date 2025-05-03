#pragma once
#include "Pantalla.h"
#include "resources.h"
#include <optional>
#include <iostream>

using namespace sf;
using namespace std;

class PantallaJuego : public Pantalla {


private:
    GameResources resources;
    vector<Sprite> sprite;
    string siguienteEstado = "juego";

public:

    PantallaJuego() {
        if (!resources.loadAllResources()) {
            cerr << "Error al cargar texturas." << endl;
            throw std::runtime_error("Fallo al cargar texturas.");
        }

        // Posiciones por color
        auto cargarFichas = [&](Texture& tex, const vector<Vector2f>& posiciones) {
            sprite.reserve(sprite.size() + posiciones.size());  // Prevent multiple reallocations
            for (const auto& pos : posiciones) {
                sprite.emplace_back(tex);  // Constructs sprite directly in the vector
                sprite.back().setPosition(pos);
            }
            };

		cargarFichas(resources.fondo, { {0,0} }); // Fondo
		cargarFichas(resources.decoracion, { {0,0} }); // Decoración
		cargarFichas(resources.tablero, { {450,50} }); // Tablero
        cargarFichas(resources.fichaRoja, { {610,190}, {745,190}, {610,300}, {745,300} });   // Rojas
        cargarFichas(resources.fichaAmarilla, { {610,700}, {745,700}, {610,810}, {745,810} });   // Amarillas
        cargarFichas(resources.fichaAzul, { {1160,700}, {1290,700}, {1160,810}, {1290,810} }); // Azules
        cargarFichas(resources.fichaVerde, { {1160,190}, {1290,190}, {1160,300}, {1290,300} }); // Verdes
    }

    void handleInput(RenderWindow& window) override {
        while (const optional<Event> event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }

            // Aquí puedes manejar clicks, teclas, etc.
        }
    }

    void update(float dt) override {
        // Lógica futura: movimiento, colisiones, turnos, etc.

        
		
    }

    void draw(RenderWindow& window) override {
        for (auto& sprites : sprite) {
            window.draw(sprites);
        }
    }

    string nextState() const override {
        return siguienteEstado;
    }
};