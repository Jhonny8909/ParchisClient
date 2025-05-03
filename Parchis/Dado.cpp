#include "Dado.hpp"

void Dado::cargarCaras(const sf::Texture& tex, const std::vector<sf::Vector2f>& posiciones) {
    auto cargarCara = [&](const sf::Vector2f& pos) {
        caras.emplace_back(tex);
        caras.back().setPosition(pos);
        // Ajusta el textureRect para cada cara (asume spritesheet horizontal)
        int indice = static_cast<int>(caras.size()) - 1;
        caras.back().setTextureRect({ indice * 100, 0, 100, 100 });
        };

    for (const auto& pos : posiciones) {
        cargarCara(pos);
    }
}

void Dado::lanzar() {
    estaAnimando = true;
    relojAnimacion.restart();
    valorActual = rand() % 6 + 1;
}

void Dado::actualizar(float deltaTime) {
    if (estaAnimando && relojAnimacion.getElapsedTime().asSeconds() < 1.0f) {
        for (auto& cara : caras) {
            cara.rotate(360 * deltaTime * 5);  // Animación de giro
        }
    }
    else {
        estaAnimando = false;
    }
}

void Dado::dibujar(sf::RenderWindow& ventana) const {
    if (estaAnimando) {
        ventana.draw(caras[rand() % 6]);  // Cara aleatoria durante animación
    }
    else {
        ventana.draw(caras[valorActual - 1]);  // Cara final
    }
}

int Dado::getValor() const {
    return valorActual;
}