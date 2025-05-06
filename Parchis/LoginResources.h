#pragma once
#include <SFML/Graphics.hpp>
#include <string>

struct LoginResources {
    sf::Texture background;
    sf::Texture doodles;
    sf::Texture title;
    sf::Texture nameInput;
    sf::Texture passwordInput;
    sf::Texture loginButton;
    sf::Texture loginButtonHover;
    sf::Texture registerButton;
    sf::Texture registerButtonHover;

    // Fuente
    sf::Font font;
    std::vector<sf::Text> texts;


    bool loadAllResources();
};
