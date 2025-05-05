#include "Dado.hpp"
#include <cstdlib>
#include <ctime>

Dado::Dado(GameResources& resources) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Función lambda para cargar dados (versión mejorada)
    auto cargarDado = [&](sf::Texture& tex, const sf::Vector2f& posicion) {
        spritesDado.emplace_back(tex);
        spritesDado.back().setPosition(posicion);
        };

    // Cargamos cada cara del dado con su textura
    cargarDado(resources.dado1, { 800, 800 });
    cargarDado(resources.dado2, { 800, 800 });
    cargarDado(resources.dado3, { 800, 800 });
    cargarDado(resources.dado4, { 800, 800 });
    cargarDado(resources.dado5, { 800, 800 });
    cargarDado(resources.dado6, { 800, 800 });

    if (spritesDado.empty()) {
        throw std::runtime_error("Error al cargar sprites del dado");
    }

    spriteActual = &spritesDado[0];
}

void Dado::lanzar() {
    estaAnimando = true;
    relojAnimacion.restart();
    valorActual = (std::rand() % 6) + 1;
}

void Dado::actualizar(float deltaTime) {
    if (estaAnimando) {
        if (relojAnimacion.getElapsedTime().asSeconds() < 1.0f) {
            int caraAleatoria = std::rand() % 6;
            spriteActual = &spritesDado[caraAleatoria];
        }
        else {
            estaAnimando = false;
            spriteActual = &spritesDado[valorActual - 1];
        }
    }
}

void Dado::dibujar(sf::RenderWindow& ventana) const {
    ventana.draw(*spriteActual);
}