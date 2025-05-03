#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Dado {
private:
    std::vector<sf::Sprite> caras;  // 6 sprites para cada cara
    int valorActual = 1;
    bool estaAnimando = false;
    sf::Clock relojAnimacion;

public:
    void cargarCaras(const sf::Texture& tex, const std::vector<sf::Vector2f>& posiciones);
    void lanzar();
    void actualizar(float deltaTime);
    void dibujar(sf::RenderWindow& ventana) const;
    int getValor() const;
};