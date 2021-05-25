#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

struct position
{
    int x, y;
};

position pos {0};
position e_pos {0};

sf::TcpSocket socket;

void thread_func()
{
    int array[2] = {pos.x, pos.y};
    int e_array[2];

    size_t received;

    socket.send(array, sizeof(int) * 2);
    socket.receive(e_array, sizeof(int) * 2, received);

    e_pos.x = e_array[0];
    e_pos.y = e_array[1];
}

int main()
{
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

    socket.connect("20.52.38.191", 50003);

    sf::Thread thread(thread_func);
    thread.launch();

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

        GucciDuckling.setPosition(pos.x, pos.y);
        GucciDuckling1.setPosition(e_pos.x, e_pos.y);

        window.draw(GucciDuckling);
        window.draw(GucciDuckling1);

        window.display();
    }

    return 0;
}