#include "LoginResources.h"
#include <iostream>

bool LoginResources::loadAllResources() {
    bool success = true;

    success &= background.loadFromFile("AssetsLogin/MM_Fondo.png");
    success &= doodles.loadFromFile("AssetsLogin/MM_garabatos.png");
    success &= title.loadFromFile("AssetsLogin/MM_Titulo.png");
    success &= nameInput.loadFromFile("AssetsLogin/MM_entrada_nombre.png");
    success &= passwordInput.loadFromFile("AssetsLogin/MM_entrada_contraseña.png");
    success &= loginButton.loadFromFile("AssetsLogin/MM_iniciar_sesion.png");
    success &= loginButtonHover.loadFromFile("AssetsLogin/MM_iniciar_sesion_hover.png");
    success &= registerButton.loadFromFile("AssetsLogin/MM_registrarse.png");
    success &= registerButtonHover.loadFromFile("AssetsLogin/MM_registrarse_hover.png");

    if (!font.openFromFile("AssetsLogin/Handwritingdarky-Regular.ttf")) {
        std::cerr << "Error cargando fuente" << std::endl;
        success = false;
    }

    sf::Text usernameText(font);
    usernameText.setPosition({ 1100,(1080 / 2) - 30 });
    usernameText.setFillColor({ 0, 0, 0 });
    texts.push_back(usernameText);

    sf::Text passwordText(font);
    passwordText.setPosition({ 300,(1080 / 2) - 30 });
    passwordText.setFillColor({ 0, 0, 0 });
    texts.push_back(passwordText);
    return success;
}