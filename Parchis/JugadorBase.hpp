#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory> // Para std::unique_ptr

// Forward declarations
class Ficha; // Clase base abstracta
class GameResources;

class JugadorBase {
protected:
    std::vector<std::unique_ptr<Ficha>> fichas; // Polimorfismo con Fichas espec�ficas
    int color;
    bool esSuTurno = false;
    GameResources& recursos;

    virtual const std::vector<std::unique_ptr<Ficha>>& getFichas() const = 0;
    

public:
    
    JugadorBase(int color, GameResources& resources);
    virtual ~JugadorBase() = default;

    // M�todos comunes
    virtual void inicializarFichas() = 0; // Implementaci�n espec�fica por color
    void dibujarFichas(sf::RenderWindow& ventana) const;

    // L�gica del juego
    bool todasFichasEnMeta() const;
    bool puedeMoverAlgunaFicha(int valorDado) const;
    Ficha* getFichaEnCasilla(int indiceCasilla) const;

    // Getters
    int getColor() const { return color; }
    bool enTurno() const { return esSuTurno; }
    void setTurno(bool turno) { esSuTurno = turno; }

    
};

