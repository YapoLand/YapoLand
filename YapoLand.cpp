#include <thread>
#include <SFML/Graphics.hpp>
#include "YapoLandSocket.hpp"

struct position
{
    int x, y;
};

position pos {0};
position e_pos {0};

yl_sock::Tcp_socket client_socket;

void thread_func()
{
    while (1)
    {
        int array[2];

        client_socket.receive<int>(array, sizeof(int) * 2);

        e_pos.x = array[0];
        e_pos.y = array[1];
    }
}

void thread_func1()
{
    while (1)
    {
        int array[2] = {pos.x, pos.y};

        client_socket.send<int>(array, sizeof(int) * 2);
    }
}

int main()
{
    client_socket.connect("20.52.38.191", 50003);

    std::thread thread(thread_func);
    std::thread thread1(thread_func1);

    sf::RenderWindow window(sf::VideoMode(800, 600), "YapoLand");

    sf::Texture texture;
    
    if (!texture.loadFromFile("gucciduckling.jpg"))
    {
        return 0;
    }

    sf::Sprite GucciDuckling;
    GucciDuckling.setTexture(texture);

    sf::Sprite GucciDuckling1;
    GucciDuckling1.setTexture(texture);

    while (window.isOpen())
    {        
        sf::Event event;
        
        while (window.pollEvent(event))
        {            
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                pos.x += 20;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                pos.x -= 20;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                pos.y -= 20;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                pos.y += 20;
            }
        }
        
        window.clear(sf::Color::White);

        int array[2] = {pos.x, pos.y};

        GucciDuckling.setPosition(pos.x, pos.y);
        GucciDuckling1.setPosition(e_pos.x, e_pos.y);

        window.draw(GucciDuckling);
        window.draw(GucciDuckling1);

        window.display();
    }

    return 0;
}