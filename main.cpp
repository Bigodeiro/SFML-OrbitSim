#include <SFML/Graphics.hpp>
#include <iostream>
#include <typeinfo> //* bib para descobrir o tipo de certas variaveis, usa "typeid(<variavel>).name" para conseguir o nome
#include <cmath>
#include <math.h>
#define WIDTH 1800
#define HEIGTH 1000

class circleObj 
{
  public:

    int mass;
    float radius;

    sf::Vector2f pos;
    sf::Vector2f velocity;

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

float lerp(float a, float b, float t)
{
    float tot = a + b;
    float result = tot * t;

    return result;    
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGTH), "SFML!", sf::Style::Close | sf::Style::Titlebar);

    circleObj vermelho(WIDTH/2 - 400, HEIGTH/2, 10, 5, sf::Color::Red);
    vermelho.velocity.y = -0.05f;

    circleObj amarelo(WIDTH/2, HEIGTH/2, 10, 5, sf::Color::Yellow);

    circleObj verde(WIDTH/2 + 400, HEIGTH/2, 10, 5, sf::Color::Green);
    verde.velocity.y = 0.05f;

    circleObj pontoMedio1 (0, 0, 3, 0, sf::Color::White);
    circleObj pontoMedio2 (0, 0, 3, 0, sf::Color::White);
    circleObj pontoMedio3 (0, 0, 3, 0, sf::Color::White);

    sf::Vector2f teste(15,2);

    sf::Vertex lines[] =
    {
        sf::Vector2f(0, 0),
        sf::Vector2f(0, 0),
        sf::Vector2f(0, 0),
        sf::Vector2f(0, 0),
        sf::Vector2f(0, 0),
        sf::Vector2f(0, 0)
    };

    sf::Vertex lines2[] =
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
        vermelho = circleObj(WIDTH/2 - 400, HEIGTH/2, 10, 5, sf::Color::Red);
        vermelho.velocity.y = -0.05f;

        amarelo = circleObj(WIDTH/2, HEIGTH/2, 10, 5, sf::Color::Yellow);

        verde = circleObj(WIDTH/2 + 400, HEIGTH/2, 10, 5, sf::Color::Green);
        verde.velocity.y = 0.05f;
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

    pontoMedio1.pos = sf::Vector2f( lerp(vermelho.pos.x, verde.pos.x, 0.5), lerp(vermelho.pos.y, verde.pos.y, 0.5));
    pontoMedio2.pos = sf::Vector2f( lerp(amarelo.pos.x, verde.pos.x, 0.5), lerp(amarelo.pos.y, verde.pos.y, 0.5));
    pontoMedio3.pos = sf::Vector2f( lerp(vermelho.pos.x, amarelo.pos.x, 0.5), lerp(vermelho.pos.y, amarelo.pos.y, 0.5));

    lines2[0] = sf::Vector2f(vermelho.pos.x, vermelho.pos.y);
    lines2[1] = sf::Vector2f(pontoMedio2.pos.x, pontoMedio2.pos.y);

    lines2[2] = sf::Vector2f(verde.pos.x, verde.pos.y);
    lines2[3] = sf::Vector2f(pontoMedio3.pos.x, pontoMedio3.pos.y);

    lines2[4] = sf::Vector2f(amarelo.pos.x, amarelo.pos.y);
    lines2[5] = sf::Vector2f(pontoMedio1.pos.x, pontoMedio1.pos.y);

    pontoMedio1.applyChanges();
    pontoMedio2.applyChanges();
    pontoMedio3.applyChanges();


    window.draw(pontoMedio1.sfCircle);
    window.draw(pontoMedio2.sfCircle);
    window.draw(pontoMedio3.sfCircle);

    window.draw(lines, 6, sf::Lines);
    window.draw(lines2, 6, sf::Lines);
    window.draw(vermelho.sfCircle);
    window.draw(verde.sfCircle);
    window.draw(amarelo.sfCircle);


    //? recarrega a tela, fazendo com que as mudanças sejam efetivadas
    window.display();

    }
    return 0;
}