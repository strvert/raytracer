#include <iostream>
#include <SFML/Graphics.hpp>

#include <vec3.h>

void SetPixel(sf::Texture& texture, unsigned x, unsigned y, Color& color)
{
    texture.update(reinterpret_cast<sf::Uint8*>(&color), 1, 1, x, y);
}

const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 720;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "raytracer", sf::Style::Titlebar | sf::Style::Close);

    sf::Texture texture;
    texture.create(WINDOW_WIDTH, WINDOW_HEIGHT);
    sf::Sprite sprite;
    sprite.setTexture(texture);

    for (int j = 0; j < WINDOW_HEIGHT; j++)
    {
        for (int i = 0; i < WINDOW_WIDTH; i++)
        {
            float r = float(i) / float(WINDOW_WIDTH);
            float g = float(j) / float(WINDOW_HEIGHT);
            float b = 0.2f;
            auto c = Color(int(255.99*r), int(255.99*g), int(255.99*b));
            SetPixel(texture, i, j, c);
        }
    }


    while (window.isOpen())
    {
        window.draw(sprite);
        window.display();

        sf::Event event;
        if (!window.pollEvent(event)) continue;
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}
