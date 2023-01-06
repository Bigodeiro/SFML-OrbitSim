#include <SFML/Graphics.hpp>
#include <iostream>
#include <typeinfo> //* bib para descobrir o tipo de certas variaveis, usa "typeid(<variavel>).name" para conseguir o nome
#include <cmath>
#include <math.h>
#define WIDTH 800
#define HEIGTH 600


int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGTH), "SFML!", sf::Style::Close | sf::Style::Titlebar);

    sf::CircleShape player(50.0f);
    player.setFillColor(sf::Color::Cyan);

    sf::CircleShape circuloParado(50.0f);
    circuloParado.setFillColor(sf::Color::Red);
    circuloParado.setPosition(sf::Vector2f(WIDTH/2 - 50, HEIGTH/2 - 50));

    while (window.isOpen())//! cada iteração aqui é um frame
    {
        sf::Event evnt;

        //* move o player
        player.setPosition(sf::Vector2f(evnt.mouseMove.x - 50, evnt.mouseMove.y - 50));


        //? Calcula se houve colisão
        bool colisao = false;

        int distanciaX = circuloParado.getPosition().x - player.getPosition().x;
        int distanciaY = circuloParado.getPosition().y - player.getPosition().y;

        int distanciaEntreCentros = sqrt(pow(distanciaX, 2)  + pow(distanciaY, 2));

        

        if (distanciaEntreCentros < 100)
        {
            colisao = true;
        }else
        {
            colisao = false;
        }
        
        

        while (window.pollEvent(evnt))
        {
            if (colisao) printf("As esferas estao colidindo\n");
            switch (evnt.type)
            {
            case sf::Event::Closed:
                
                window.close();

                break;

            // case sf::Event::TextEntered:
                
            //     char input = evnt.text.unicode;

            //     //? sim, é possivel comparar char com int
            //     if (input < 128)  printf("%c", input);
                
            //     break;
            }
        }
    window.clear();


    //? renderiza algo para a tela, modificando-a
    window.draw(player);
    window.draw(circuloParado);

    //? recarrega a tela, fazendo com que as mudanças sejam efetivadas
    window.display();
    }

    return 0;
}