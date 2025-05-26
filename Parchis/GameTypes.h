#pragma once

enum class ColorJugador {
    ROJO = 0,
    AMARILLO = 1,
    VERDE = 2,
    AZUL = 3,
    NINGUNO = 4
};
// Sobrecarga de operadores para SFML (¡en el mismo archivo que el enum!)
inline sf::Packet& operator<<(sf::Packet& packet, const ColorJugador& color) {
    return packet << static_cast<int>(color);
}

inline sf::Packet& operator>>(sf::Packet& packet, ColorJugador& color) {
    int temp;
    packet >> temp;
    color = static_cast<ColorJugador>(temp);
    return packet;
}