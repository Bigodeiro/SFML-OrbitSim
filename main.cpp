#include <SFML/Graphics.hpp>
#include <iostream>
#include <typeinfo> //* bib para descobrir o tipo de certas variaveis, usa "typeid(<variavel>).name" para conseguir o nome
#include <cmath>
#include <math.h>
#define WIDTH 1200
#define HEIGTH 800

class cord 
{
  public:

    float x;
    float y;
};

class circleObj 
{
  public:

    int mass;
    float radius;

    cord pos;
    cord velocity;

    sf::CircleShape sfCircle;
    sf::Color color;


    void applyChanges()
    {
        sfCircle.setFillColor(color);
        sfCircle.setRadius(radius);

        pos.x += velocity.x;
        pos.y += velocity.y;

        sfCircle.setPosition(pos.x - radius, pos.y - radius);
    };


    circleObj(float xPos, float yPos, float cRadius, int cMass, sf::Color cColor)
    {
        radius = cRadius;
        mass = cMass;
        color = cColor;

        velocity.x = 0;
        velocity.y = 0;

        pos.x = xPos;
        pos.y = yPos;

        sfCircle = sf::CircleShape(cRadius);
        sfCircle.setFillColor(color);
    };
};

circleObj grav(circleObj corpoFixo, circleObj corpoMovel)
{
    float distanciaX = corpoFixo.pos.x - corpoMovel.pos.x;
    float distanciaY = corpoFixo.pos.y - corpoMovel.pos.y;

    float distanciaEntreCentros = sqrt(pow(distanciaX, 2)  + pow(distanciaY, 2));

    float forcaAplicada = ((corpoFixo.mass * corpoMovel.mass) / (pow(distanciaEntreCentros, 2))/10);

    float distanciaTotal = abs(distanciaX) + abs(distanciaY);

    float forcaX = (distanciaX / distanciaTotal) * forcaAplicada;
    float forcaY = (distanciaY / distanciaTotal) * forcaAplicada;

    corpoMovel.velocity.x += forcaX;
    corpoMovel.velocity.y += forcaY;

    return corpoMovel;
}



int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGTH), "SFML!", sf::Style::Close | sf::Style::Titlebar);

    circleObj vermelho(1000, HEIGTH/2, 10, 5, sf::Color::Red);
    vermelho.velocity.y = -0.05f;

    circleObj amarelo(600, HEIGTH/2, 10, 5, sf::Color::Yellow);

    circleObj verde(200, HEIGTH/2, 10, 5, sf::Color::Green);
    verde.velocity.y = 0.05f;

    sf::Vertex lines[] =
    {
        sf::Vector2f(0, 0),
        sf::Vector2f(0, 0),
        sf::Vector2f(0, 0),
        sf::Vector2f(0, 0),
        sf::Vector2f(0, 0),
        sf::Vector2f(0, 0)
    };

    



    while (window.isOpen())//! cada iteração aqui é um frame
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                
                window.close();

                break;
            }
        }

    //!codigo a ser executado todo frame

    



    vermelho = grav(verde, vermelho);
    verde = grav(vermelho, verde);
    vermelho = grav(amarelo, vermelho);
    verde = grav(amarelo, verde);
    amarelo = grav(verde, amarelo);
    amarelo = grav(vermelho, amarelo);

    window.clear();

    //? renderiza algo para a tela, modificando-a
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
    {
        vermelho = circleObj(1000, HEIGTH/2, 10, 5, sf::Color::Red);
        vermelho.velocity.y = 0.05f;
        vermelho.velocity.x = 0;

        verde = circleObj (200, HEIGTH/2, 10, 5, sf::Color::Green);
        verde.velocity.y = - 0.05f;
        verde.velocity.x = 0;

        circleObj meio(WIDTH/2, HEIGTH/2, 3, 8, sf::Color::White);
    }

    vermelho.applyChanges();
    verde.applyChanges();
    amarelo.applyChanges();


    lines[0] = sf::Vector2f(vermelho.pos.x, vermelho.pos.y);
    lines[1] = sf::Vector2f(verde.pos.x, verde.pos.y);

    lines[2] = sf::Vector2f(verde.pos.x, verde.pos.y);
    lines[3] = sf::Vector2f(amarelo.pos.x, amarelo.pos.y);

    lines[4] = sf::Vector2f(vermelho.pos.x, vermelho.pos.y);
    lines[5] = sf::Vector2f(amarelo.pos.x, amarelo.pos.y);


    window.draw(vermelho.sfCircle);
    window.draw(verde.sfCircle);
    window.draw(amarelo.sfCircle);
    window.draw(lines, 6, sf::Lines);


    //? recarrega a tela, fazendo com que as mudanças sejam efetivadas
    window.display();
    }

    return 0;
}