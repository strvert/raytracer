#include <iostream>
#include <memory>
#include <limits>
#include <SFML/Graphics.hpp>

#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "color.h"

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 400;

void SetPixel(sf::Texture& Tex, unsigned X, unsigned Y, Color C)
{
    auto Size = Tex.getSize();
    Tex.update(reinterpret_cast<sf::Uint8*>(&C), 1, 1, Size.x - X, Size.y - Y);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "raytracer", sf::Style::Titlebar | sf::Style::Close);

    sf::Texture Tex;
    Tex.create(WINDOW_WIDTH, WINDOW_HEIGHT);
    sf::Sprite Sprt;
    Sprt.setTexture(Tex);

    Vec3f LowerLeftCorner(-2.0, -1.0, -1.0);
    Vec3f Horizonal(4.0, 0.0, 0.0);
    Vec3f Vertical(0.0, 2.0, 0.0);
    Vec3f Origin(0.0, 0.0, 0.0);

    HitableList List;
    List.Add(std::make_unique<Sphere>(Vec3f(0, 0, -1), 0.4));
    List.Add(std::make_unique<Sphere>(Vec3f(0.5, 0, -1), 0.4));

    for (int j = 0; j < WINDOW_HEIGHT; j++)
    {
        for (int i = 0; i < WINDOW_WIDTH; i++)
        {
            float U = float(i) / float(WINDOW_WIDTH);
            float V = float(j) / float(WINDOW_HEIGHT);
            Ray R(Origin, LowerLeftCorner + U*Horizonal + V*Vertical);

            SetPixel(Tex, i, j, R.ToScreenLerpColor(Color(255, 255, 255), Color(127, 179, 255)));
            HitRecord Rec;
            if (List.Hit(R, 0.0, std::numeric_limits<float>::max(), Rec))
            {
                SetPixel(Tex, i, j, (1+Rec.N)*127);
            }
        }
        window.draw(Sprt);
        window.display();
    }

    Tex.copyToImage().saveToFile("./image.png");

    while (window.isOpen())
    {
        sf::Event event;
        if (!window.pollEvent(event)) continue;
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}
