#pragma once
#include <array>
#include <SFML/System.hpp>

class Tablero {
public:

    const std::array<sf::Vector2f, 44> positions = {
        sf::Vector2f(885, 160),    // 1
        sf::Vector2f(885, 220),    // 2
        sf::Vector2f(885, 280),    // 3
        sf::Vector2f(885, 340),    // 4
        sf::Vector2f(885, 400),    // 5
        sf::Vector2f(815, 470),    // 6
        sf::Vector2f(745, 470),    // 7
        sf::Vector2f(685, 470),    // 8
        sf::Vector2f(615, 470),    // 9
        sf::Vector2f(545, 470),    // 10
        sf::Vector2f(545, 540),    // 11
        sf::Vector2f(545, 605),    // 12
        sf::Vector2f(615, 605),    // 13
        sf::Vector2f(680, 605),    // 14
        sf::Vector2f(745, 605),    // 15
        sf::Vector2f(810, 605),    // 16
        sf::Vector2f(880, 675),    // 17
        sf::Vector2f(880, 740),    // 18
        sf::Vector2f(880, 800),    // 19
        sf::Vector2f(880, 860),    // 20
        sf::Vector2f(880, 910),   // 21
        sf::Vector2f(950, 910),   // 22
        sf::Vector2f(1025, 910),   // 23
        sf::Vector2f(1025, 860),   // 24
        sf::Vector2f(1025, 800),   // 25
        sf::Vector2f(1025, 740),   // 26
        sf::Vector2f(1025, 675),   // 27
        sf::Vector2f(1100, 605),   // 28
        sf::Vector2f(1165, 605),   // 29
        sf::Vector2f(1230, 605),   // 30
        sf::Vector2f(1295, 605),   // 31
        sf::Vector2f(1360, 605),   // 32
        sf::Vector2f(1360, 540),   // 33
        sf::Vector2f(1360, 470),   // 34
        sf::Vector2f(1300, 470),   // 35
        sf::Vector2f(1230, 470),   // 36
        sf::Vector2f(1170, 470),   // 37
        sf::Vector2f(1100, 470),   // 38
        sf::Vector2f(1025, 400),   // 39
        sf::Vector2f(1025, 340),    // 40
		sf::Vector2f(1025, 280),   // 41
        sf::Vector2f(1025, 220),   // 42
        sf::Vector2f(1025, 160),   // 43
		sf::Vector2f(955, 160)    // 44
    };

	//Inicio de cada color
    const std::array<sf::Vector2f, 4> inicio_Rojas = {
        sf::Vector2f(620, 220),    // 1
        sf::Vector2f(620, 340),    // 2
        sf::Vector2f(750, 220),   // 3
        sf::Vector2f(750, 340)    // 4
    };

    const std::array<sf::Vector2f, 4> inicio_Verde = {
        sf::Vector2f(1165, 220),    // 1
        sf::Vector2f(1165, 340),    // 2
        sf::Vector2f(1300, 220),   // 3
        sf::Vector2f(1300, 340)    // 4
    };

    const std::array<sf::Vector2f, 4> inicio_Azul = {
        sf::Vector2f(1165, 740),    // 1
        sf::Vector2f(1165, 850),    // 2
        sf::Vector2f(1300, 740),   // 3
        sf::Vector2f(1300, 850)    // 4
    };

    const std::array<sf::Vector2f, 4> inicio_Amarillo = {
        sf::Vector2f(620, 740),    // 1
        sf::Vector2f(620, 850),    // 2
        sf::Vector2f(750, 740),   // 3
        sf::Vector2f(750, 850)    // 4
    };

	//Metas de cada color
    const std::array<sf::Vector2f, 5> meta_Rojas = {
        sf::Vector2f(950, 210),    // 1
        sf::Vector2f(950, 285),    // 2
        sf::Vector2f(950, 350),   // 3
        sf::Vector2f(950, 400),    // 4
		sf::Vector2f(950, 480)    // 5
    };

    const std::array<sf::Vector2f, 5> meta_Verde = {
        sf::Vector2f(1295, 535),    // 1
        sf::Vector2f(1230, 535),    // 2
        sf::Vector2f(1165, 535),   // 3
        sf::Vector2f(1095, 535),    // 4
		sf::Vector2f(1025, 535)    // 5
    };
    
    const std::array<sf::Vector2f, 5> meta_Azul = {
        sf::Vector2f(955, 850),    // 1
        sf::Vector2f(955, 800),    // 2
        sf::Vector2f(955, 730),   // 3
        sf::Vector2f(955, 680),    // 4
		sf::Vector2f(955, 600)    // 5
	};

    const std::array<sf::Vector2f, 5> meta_Amarillo = {
        sf::Vector2f(620, 535),    // 1
        sf::Vector2f(680, 535),    // 2
        sf::Vector2f(750, 535),   // 3
        sf::Vector2f(810, 535),    // 4
		sf::Vector2f(890, 535)    // 5
    };
};