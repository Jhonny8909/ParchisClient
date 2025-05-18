#pragma once
#include <array>
#include <SFML/System.hpp>

class tablero {
public:

    const std::array<sf::Vector2f, 40> positions = {
        sf::Vector2f(880.f, 130.f),    // 1
        sf::Vector2f(880.f, 190.f),    // 2
        sf::Vector2f(880.f, 250.f),    // 3
        sf::Vector2f(880.f, 310.f),    // 4
        sf::Vector2f(880.f, 370.f),    // 5
        sf::Vector2f(810.f, 440.f),    // 6
        sf::Vector2f(740.f, 440.f),    // 7
        sf::Vector2f(680.f, 440.f),    // 8
        sf::Vector2f(615.f, 440.f),    // 9
        sf::Vector2f(545.f, 440.f),    // 10
        sf::Vector2f(545.f, 580.f),    // 11
        sf::Vector2f(615.f, 580.f),    // 12
        sf::Vector2f(680.f, 580.f),    // 13
        sf::Vector2f(740.f, 580.f),    // 14
        sf::Vector2f(810.f, 580.f),    // 15
        sf::Vector2f(880.f, 645.f),    // 16
        sf::Vector2f(880.f, 710.f),    // 17
        sf::Vector2f(880.f, 770.f),    // 18
        sf::Vector2f(880.f, 830.f),    // 19
        sf::Vector2f(880.f, 880.f),    // 20
        sf::Vector2f(1025.f, 880.f),   // 21
        sf::Vector2f(1025.f, 830.f),   // 22
        sf::Vector2f(1025.f, 770.f),   // 23
        sf::Vector2f(1025.f, 710.f),   // 24
        sf::Vector2f(1025.f, 645.f),   // 25
        sf::Vector2f(1095.f, 580.f),   // 26
        sf::Vector2f(1165.f, 580.f),   // 27
        sf::Vector2f(1230.f, 580.f),   // 28
        sf::Vector2f(1295.f, 580.f),   // 29
        sf::Vector2f(1360.f, 580.f),   // 30
        sf::Vector2f(1360.f, 440.f),   // 31
        sf::Vector2f(1295.f, 440.f),   // 32
        sf::Vector2f(1230.f, 440.f),   // 33
        sf::Vector2f(1165.f, 440.f),   // 34
        sf::Vector2f(1095.f, 440.f),   // 35
        sf::Vector2f(1025.f, 370.f),   // 36
        sf::Vector2f(1025.f, 310.f),   // 37
        sf::Vector2f(1025.f, 250.f),   // 38
        sf::Vector2f(1025.f, 190.f),   // 39
        sf::Vector2f(1025.f, 130.f)    // 40
    };

};