#include <SFML/Network.hpp>
#include<iostream>
#include<string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <sstream>
#include <stdlib.h>
#include <iomanip>
#include <openssl/evp.h>  // Nueva API para hashing en OpenSSL 3.0+
#include <openssl/sha.h>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

#define SERVER "127.0.0.1"
#define USERNAME "root"
#define PASSWORD ""
#define DATABASE "loginparchis"

#define SERVER_PORT 55000
const sf::IpAddress SERVER_IP = sf::IpAddress(127, 0, 0, 1);

// Función para hashear contraseñas con SHA-256 usando la API EVP de OpenSSL 3.0+
std::string hashSHA256(const std::string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();

    if (mdctx == nullptr) {
        std::cerr << "Error al crear contexto EVP" << std::endl;
        return "";
    }

    // Inicializa el contexto para SHA-256
    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), nullptr)) {
        std::cerr << "Error al inicializar digest" << std::endl;
        EVP_MD_CTX_free(mdctx);
        return "";
    }

    // Procesa el input
    if (1 != EVP_DigestUpdate(mdctx, password.c_str(), password.size())) {
        std::cerr << "Error al actualizar digest" << std::endl;
        EVP_MD_CTX_free(mdctx);
        return "";
    }

    // Finaliza y obtiene el hash
    unsigned int lengthOfHash = 0;
    if (1 != EVP_DigestFinal_ex(mdctx, hash, &lengthOfHash)) {
        std::cerr << "Error al finalizar digest" << std::endl;
        EVP_MD_CTX_free(mdctx);
        return "";
    }

    EVP_MD_CTX_free(mdctx);

    // Convierte el hash a string hexadecimal
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}





#define HEIGHT 1080
#define WIDTH 1920

#define BG_WIDTH 1280
#define BG_HEIGHT 720


int eventPressed = 0;
sf::String name;
sf::String pswd;


void Render(sf::RenderWindow& window, sf::Sprite& BackgroundSprite, sf::Sprite& SpriteGarabatos, sf::Sprite& tituloSprite, sf::Sprite& nombreSprite, sf::Sprite& PassSprite, sf::Sprite& spritebuttonReg, sf::Sprite& spritebuttonNom, sf::RectangleShape& square, sf::RectangleShape& square2, sf::Text& textNombre, sf::Text& textContrasena) {

    window.clear(sf::Color(0x000000FF));
    window.draw(BackgroundSprite);
    window.draw(SpriteGarabatos);
    window.draw(tituloSprite);
    window.draw(nombreSprite);
    window.draw(PassSprite);
    window.draw(square);
    window.draw(square2);
    window.draw(spritebuttonReg);
    window.draw(spritebuttonNom);
    window.draw(textNombre);
    window.draw(textContrasena);

    window.display();
}

void HandleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.is<sf::Event::Closed>()) {
        window.close();
    }

    if (const sf::Event::KeyPressed* keyPressed = event.getIf<sf::Event::KeyPressed>()) {

        if (keyPressed->code == sf::Keyboard::Key::Enter && eventPressed == 0) {
            eventPressed++;
        }
        else if (keyPressed->code == sf::Keyboard::Key::Enter && eventPressed == 1) {
            eventPressed++;
        }
    }

}



sf::Texture LoadSpriteSheet(const std::string& filePath) {
    sf::Texture texture;
    if (!texture.loadFromFile(filePath)) {
        std::cerr << "Error al cargar el sprite" << std::endl;
        return texture;
    }
    return texture;
}

void main()
{
    sf::TcpSocket socket;

    if (socket.connect(SERVER_IP, SERVER_PORT) != sf::Socket::Status::Done) {
        std::cerr << "Error al conectar al servidor" << std::endl;
    }
    std::cout << "Conectado al server" << std::endl;

  

    

 


    sf::Font font("AssetsLogin/Handwritingdarky-Regular.ttf");
    sf::Text nombreText(font);
    sf::Text contrasenaText(font);
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ WIDTH, HEIGHT }), "Sala Lobby");
    sf::Texture spriteBackground = LoadSpriteSheet("AssetsLogin/MM_Fondo.png");
    sf::Texture spriteGarabatos = LoadSpriteSheet("AssetsLogin/MM_garabatos.png");
    sf::Texture spriteTitulo = LoadSpriteSheet("AssetsLogin/MM_Titulo.png");
    sf::Texture spriteNombre = LoadSpriteSheet("AssetsLogin/MM_entrada_nombre.png");
    sf::Texture spritePass = LoadSpriteSheet("AssetsLogin/MM_entrada_contraseña.png");
    sf::Texture buttonRegSprite = LoadSpriteSheet("AssetsLogin/MM_iniciar_sesion.png");
    sf::Texture buttonNomSprite = LoadSpriteSheet("AssetsLogin/MM_registrarse.png");
    sf::Sprite spriteButtonReg = sf::Sprite(buttonRegSprite);
    sf::Sprite spriteButtonNom = sf::Sprite(buttonNomSprite);
    sf::Sprite NombreSprite = sf::Sprite(spriteNombre);
    sf::Sprite PassSprite = sf::Sprite(spritePass);
    sf::Sprite tituloSprite = sf::Sprite(spriteTitulo);
    sf::Sprite BackgroundSprite = sf::Sprite(spriteBackground);
    sf::Sprite SpriteGarabatos = sf::Sprite(spriteGarabatos);
    spriteButtonReg.setPosition({ 250,HEIGHT * 2.5 / 4 });
    spriteButtonNom.setPosition({ 1000,HEIGHT * 2.5 / 4 });
    NombreSprite.setPosition({ 250,HEIGHT / 3 });
    PassSprite.setPosition({ 1000,HEIGHT / 3 });
    tituloSprite.setPosition({ WIDTH / 10, 10 });

    sf::RectangleShape square;
    square.setSize({ 635, 173 });
    square.setPosition({ 250,HEIGHT * 2.5 / 4 });

    sf::RectangleShape square2;
    square2.setSize({ 635, 173 });
    square2.setPosition({ 1000,HEIGHT * 2.5 / 4 });

    std::string usuario;

    nombreText.setPosition({ 300,(HEIGHT / 2) - 30 });
    nombreText.setFillColor({ 0, 0, 0 });


    std::string contrasena;

    contrasenaText.setPosition({ 1100,(HEIGHT / 2) - 30 });
    contrasenaText.setFillColor({ 0, 0, 0 });




    while (window->isOpen()) {

        while (const std::optional event = window->pollEvent()) {

            HandleEvent(*event, *window);
            if (eventPressed == 0) {
                if (const auto* textEvent = event->getIf<sf::Event::TextEntered>()) {
                    if (textEvent->unicode == '\b' && !usuario.empty()) {
                        usuario.pop_back(); // Borrar con backspace
                    }
                    else if (textEvent->unicode < 128 && textEvent->unicode != '\r') {
                        usuario += static_cast<char>(textEvent->unicode);
                    }
                    nombreText.setString(usuario);
                    window->draw(nombreText);
                }

            }
            else if (eventPressed == 1) {
                if (const auto* textEvent = event->getIf<sf::Event::TextEntered>()) {
                    if (textEvent->unicode == '\b' && !contrasena.empty()) {
                        contrasena.pop_back(); // Borrar con backspace
                    }
                    else if (textEvent->unicode < 128 && textEvent->unicode != '\r') {
                        contrasena += static_cast<char>(textEvent->unicode);
                    }
                    contrasenaText.setString(contrasena);
                    window->draw(contrasenaText);
                }
            }
            else if (eventPressed == 2) {
                name = nombreText.getString().toAnsiString();
                pswd = contrasenaText.getString().toAnsiString();

            }


        }
        Render(*window, BackgroundSprite, SpriteGarabatos, tituloSprite, NombreSprite, PassSprite, spriteButtonReg, spriteButtonNom, square, square2, nombreText, contrasenaText);



        // Mouse position
        float mouse_x = sf::Mouse::getPosition(*window).x;
        float mouse_y = sf::Mouse::getPosition(*window).y;
        //position button login
        float x1Log = square.getPosition().x;
        float y1Log = square.getPosition().y;
        float x2Log = x1Log + square.getSize().x;
        float y2Log = y1Log + square.getSize().y;

        //position button Register
        float x1 = square2.getPosition().x;
        float y1 = square2.getPosition().y;
        float x2 = x1 + square2.getSize().x;
        float y2 = y1 + square2.getSize().y;

        //Mouse is over button login
        if ((mouse_x >= x1Log) and (mouse_x <= x2Log) and
            (mouse_y >= y1Log) and (mouse_y <= y2Log)) {
            sf::Texture buttonRegSprite = LoadSpriteSheet("AssetsLogin/MM_iniciar_sesion_hover.png");
            square.setFillColor(sf::Color(255, 0, 0, 128));

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                square.setFillColor(sf::Color(0, 255, 0, 128));

                sf::Packet packet;

                bool login = true;

                sf::String usuario = name;
                sf::String contrasena = pswd;

                packet << login << usuario << contrasena;
                socket.send(packet);

                if (socket.send(packet) == sf::Socket::Status::Done) {
          
                    std::cout << "Info login Enviada" << std::endl;
                  
                    packet.clear();
                }
                else {
                    std::cerr << "Error al enviar Info login" << std::endl;
                }

               

                
            }

        }
        else {
            sf::Texture buttonRegSprite = LoadSpriteSheet("AssetsLogin/MM_iniciar_sesion.png");
            square.setFillColor(sf::Color(0, 0, 0, 256));
        }

        //Mouse is over button Register
        if ((mouse_x >= x1) and (mouse_x <= x2) and
            (mouse_y >= y1) and (mouse_y <= y2)) {
            square2.setFillColor(sf::Color(255, 0, 0, 128));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                square2.setFillColor(sf::Color(0, 255, 0, 128));
                sf::Packet packet;

                bool login = false;

                std::string usuario = name;
                std::string contrasena = pswd;

                packet << login << usuario << contrasena;
                std::cout << "Client sending packet with size: " << packet.getDataSize() << std::endl;
                std::cout << "Contents - isLogin: " << login<< ", username: " << usuario << ", password: " << contrasena << std::endl;
                socket.send(packet);

                if (socket.send(packet) == sf::Socket::Status::Done) {

                    std::cout << "Info login Enviada" << std::endl;

                    packet.clear();
                }
                else {
                    std::cerr << "Error al enviar Info login" << std::endl;
                }

            }
        }
        else {
            square2.setFillColor(sf::Color(0, 0, 0, 256));

        }

    }
    
    delete window;
}