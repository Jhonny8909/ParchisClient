#include "Dado.hpp"

void Dado::cargarCaras(const std::vector<std::string>& rutas, const std::vector<sf::Vector2f>& posiciones) {
    // Asegurarse que hay 6 texturas y 6 posiciones
    if (rutas.size() != 6 || posiciones.size() != 6) {
        throw std::runtime_error("Se necesitan exactamente 6 texturas y 6 posiciones para el dado");
    }

    // Cargar cada textura y crear su sprite
    for (size_t i = 0; i < 6; ++i) {
        sf::Texture tex;
        if (!tex.loadFromFile(rutas[i])) {
            throw std::runtime_error("Error al cargar textura del dado: " + rutas[i]);
        }
        texturas.push_back(tex); // Almacenar la textura

        sf::Sprite sprite;
        sprite.setTexture(texturas.back());
        sprite.setPosition(posiciones[i]);
        caras.push_back(sprite);
    }
}

// Resto de métodos permanecen iguales...
void Dado::lanzar() {
    estaAnimando = true;
    relojAnimacion.restart();
    valorActual = rand() % 6 + 1;
}

void Dado::actualizar(float deltaTime) {
    if (estaAnimando && relojAnimacion.getElapsedTime().asSeconds() < 1.0f) {
        for (auto& cara : caras) {
            cara.rotate(sf::degrees(360) * deltaTime * 5); // Animación de giro
        }
    }
    else {
        estaAnimando = false;
    }
}

void Dado::dibujar(sf::RenderWindow& ventana) const {
    if (estaAnimando) {
        ventana.draw(caras[rand() % 6]); // Cara aleatoria durante animación
    }
    else {
        ventana.draw(caras[valorActual - 1]); // Cara final
    }
}

int Dado::getValor() const {
    return valorActual;
}