#include <iostream>
#include <SFML/Graphics.hpp>

#include "vec3.h"
#include "ray.h"

void SetPixel(sf::Texture& Tex, unsigned X, unsigned Y, Color& C)
{
    Tex.update(reinterpret_cast<sf::Uint8*>(&C), 1, 1, X, Y);
}

void SetPixel(sf::Texture& Tex, unsigned X, unsigned Y, Vec3f& V)
{
    Color Col(V.X(), V.Y(), V.Z());
    SetPixel(Tex, X, Y, Col);
}

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 400;

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

    for (int j = 0; j < WINDOW_HEIGHT; j++)
    {
        for (int i = 0; i < WINDOW_WIDTH; i++)
        {
            float U = float(i) / float(WINDOW_WIDTH);
            float V = float(j) / float(WINDOW_HEIGHT);
            // float B = 0.2f;
            // auto C = Color(int(255.99*R), int(255.99*G), int(255.99*B));

            Ray ColRay(Origin, LowerLeftCorner + U*Horizonal + V*Vertical);
            Color Col = ColRay.ToScreenLerpColor(Color(127, 179, 255));
            SetPixel(Tex, i, j, Col);
        }
        window.draw(Sprt);
        window.display();
    }


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
