#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include "resources.h"

class Tablero {
public:
    Tablero();
    void dibujar(sf::RenderWindow& window) const {
        // Dibuja el tablero aquí
        window.draw(tablero);  // Asegúrate de tener este sprite
    }
    // Métodos clave
    const sf::Vector2f& getPosicionCasilla(int indice) const;
    bool esCasillaSegura(int indice) const;
    int getPasilloMetaDesdeColor(int color) const;

    // Constantes públicas para acceso directo
    static constexpr int NUM_CASILLAS = 60; // 40 generales + 16 pasillos + 4 metas
    static constexpr int ENTRADA_ROJO = 0;
    static constexpr int ENTRADA_AMARILLO = 10;
    static constexpr int ENTRADA_AZUL = 20;
    static constexpr int ENTRADA_VERDE = 30;

private:
    std::array<sf::Vector2f, NUM_CASILLAS> casillas;
    std::array<int, 4> entradasMeta = { ENTRADA_ROJO, ENTRADA_AMARILLO, ENTRADA_AZUL, ENTRADA_VERDE };

    void inicializarPosiciones();
    void moverFicha(Ficha& ficha, int pasos,
        const std::array<std::unique_ptr<JugadorBase>, 4>& jugadores) {
        // Implementa la lógica de movimiento aquí
    }
};