#include <iostream>
#include <SFML/Graphics.hpp>

#include <vec3.h>

void SetPixel(sf::Texture& texture, unsigned x, unsigned y, sf::Color& color)
{
    texture.update(reinterpret_cast<sf::Uint8*>(&color), 1, 1, x, y);
}

const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 720;

using Vec3f = Vec3<float>;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "raytracer", sf::Style::Titlebar | sf::Style::Close);

    Vec3f v1(10, 11, 127);
    Vec3f v2(20, 21, 227);
    v2 += v1;
    std::cout << v2 << std::endl;
    std::cout << v1.Cross(v2) << std::endl;

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
            auto c = sf::Color(int(255.99*r), int(255.99*g), int(255.99*b));
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
