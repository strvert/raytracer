#include <iostream>
#include <memory>
#include <random>
#include <limits>
#include <cstdint>
#include <SFML/Graphics.hpp>

#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "color.h"
#include "camera.h"

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 400;
const unsigned int NS = 100;

std::random_device Rnd;
std::mt19937 Mt(Rnd());
std::uniform_real_distribution<double> RandZeroToOne(0.0, 1.0);
std::uniform_real_distribution<double> RandMinusOneToPlusOne(-1.0, 1.0);

void SetPixel(sf::Texture& Tex, unsigned X, unsigned Y, Color C)
{
    auto Size = Tex.getSize();
    Tex.update(reinterpret_cast<sf::Uint8*>(&C), 1, 1, Size.x - X, Size.y - Y);
}

Vec3f RandInUnitSphere()
{
    Vec3f P;
    do {
        P = Vec3f(RandMinusOneToPlusOne(Mt), RandMinusOneToPlusOne(Mt), RandMinusOneToPlusOne(Mt));
    } while (P.SquaredLength() >= 1.0);
    return P;
}

Color ScreenColor(const Ray& R, std::shared_ptr<Hitable> World)
{
    HitRecord Rec;
    if (World->Hit(R, 0, std::numeric_limits<float>::max(), Rec))
    {
        Vec3f Target = Rec.P + Rec.N + RandInUnitSphere();
        return 0.5*ScreenColor(Ray(Rec.P, Target-Rec.P), World);
    }
    else
    {
        return R.ToScreenLerpColor(Color(255, 255, 255), Color(127, 179, 255));
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "raytracer", sf::Style::Titlebar | sf::Style::Close);

    sf::Texture Tex;
    Tex.create(WINDOW_WIDTH, WINDOW_HEIGHT);
    sf::Sprite Sprt;
    Sprt.setTexture(Tex);

    auto List = std::make_shared<HitableList>();
    List->Add(std::make_unique<Sphere>(Vec3f(0, 0, -1), 0.5));
    List->Add(std::make_unique<Sphere>(Vec3f(0.0, -100.5, -1), 100));

    Camera Cam;
    for (int j = 0; j < WINDOW_HEIGHT; j++)
    {
        for (int i = 0; i < WINDOW_WIDTH; i++)
        {
            Vec3f ColorSum(0, 0, 0);
            for (int s = 0; s < NS; s++)
            {
                double Rand = RandZeroToOne(Mt);
                float U = float(i + Rand) / float(WINDOW_WIDTH);
                float V = float(j + Rand) / float(WINDOW_HEIGHT);
                Ray R = Cam.GetRay(U, V);
                ColorSum += ScreenColor(R, List);
            }
            Color C = ColorSum / NS;
            SetPixel(Tex, i, j, C);
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
