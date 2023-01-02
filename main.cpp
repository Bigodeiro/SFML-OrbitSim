#include <SFML/Graphics.hpp>
#include <iostream>
#include <typeinfo> //* bib para descobrir o tipo de certas variaveis, usa "typeid(<variavel>).name" para conseguir o nome

int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 512), "SFML!", sf::Style::Close | sf::Style::Titlebar);

    sf::RectangleShape player(sf::Vector2f(100.0f, 100.0f));//* estes valores são o tamanho do retangulo, não a posição
    player.setFillColor(sf::Color::Cyan);

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

            case sf::Event::TextEntered:
                
                char input = evnt.text.unicode;

                //? sim, é possivel comparar char com int
                if (input < 128)  printf("%c", input);
                
                break;
            }
        }

    //? renderiza algo para a tela, modificando-a
    window.draw(player);

    //? recarrega a tela, fazendo com que as mudanças sejam efetivadas
    window.display();
    }

    return 0;
}