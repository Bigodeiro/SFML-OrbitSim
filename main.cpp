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

    circleObj vermelho(WIDTH/2, HEIGTH/2, 10, 100, sf::Color::Red);

    circleObj verde(400, 600, 25, 1, sf::Color::Green);
    verde.velocity.x = 0.15f;



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

    window.clear();

    //!codigo a ser executado todo frame

    verde = grav(vermelho, verde);

    //? renderiza algo para a tela, modificando-a
    vermelho.applyChanges();
    window.draw(vermelho.sfCircle);

    verde.applyChanges();
    window.draw(verde.sfCircle);


    //? recarrega a tela, fazendo com que as mudanças sejam efetivadas
    window.display();
    }

    return 0;
}