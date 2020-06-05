#include <iostream>
#include <memory>
#include <random>
#include <limits>
#include <cstdint>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "color.h"
#include "camera.h"

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 400;
const unsigned int NS = 100;
const unsigned int RENDER_CELL_SIZE = 200;
const bool PARALLEL = false;

std::random_device Rnd;
std::mt19937 Mt(Rnd());
std::uniform_real_distribution<double> RandZeroToOne(0.0, 1.0);
std::uniform_real_distribution<double> RandMinusOneToPlusOne(-1.0, 1.0);

void SetPixel(sf::Texture& Tex, unsigned X, unsigned Y, Color C)
{
    auto Size = Tex.getSize();
    Tex.update(reinterpret_cast<sf::Uint8*>(&C), 1, 1, Size.x - X, Size.y - Y);
}

void SetLinePixels(sf::Texture& Tex, unsigned X, unsigned Y, const std::vector<Color>& C)
{
    auto Size = Tex.getSize();
    Tex.update(reinterpret_cast<const sf::Uint8*>(C.data()), C.size(), 1, Size.x - X, Size.y - Y);
}

Vec3f RandInUnitSphere()
{
    Vec3f P;
    do {
        P = Vec3f(RandMinusOneToPlusOne(Mt), RandMinusOneToPlusOne(Mt), RandMinusOneToPlusOne(Mt));
    } while (P.SquaredLength() >= 1.0);
    return P;
}

Color ScreenColor(const Ray& R, const std::shared_ptr<Hitable> World)
{
    HitRecord Rec;
    if (World->Hit(R, 0.001, std::numeric_limits<float>::max(), Rec))
    {
        Vec3f Target = Rec.P + Rec.N + RandInUnitSphere();
        return 0.5*ScreenColor(Ray(Rec.P, Target-Rec.P), World);
    }
    else
    {
        return R.ToScreenLerpColor(Color(255, 255, 255), Color(127, 179, 255));
    }
}

void RenderProc(sf::Texture& Tex, const Camera& Cam, const std::shared_ptr<Hitable> List, const unsigned X, const unsigned Y, const unsigned SizeX, const unsigned SizeY)
{
    std::vector<Color> Map(SizeX*SizeY, Color(0));
    for (unsigned i = X; i < X + SizeX; i++)
    {
        for (unsigned j = Y; j < Y + SizeY; j++)
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
            Vec3f Cf = (ColorSum / NS) / 255.0;
            Map[(j-Y)*SizeX + (i-X)] = Vec3f(std::sqrt(Cf.X()), std::sqrt(Cf.Y()), std::sqrt(Cf.Z())) * 255;
        }
    }
    Tex.update(reinterpret_cast<sf::Uint8*>(Map.data()), SizeX, SizeY, X, Y);
}

int main()
{
    sf::RenderWindow Window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "raytracer", sf::Style::Titlebar | sf::Style::Close);

    sf::Texture Tex;
    Tex.create(WINDOW_WIDTH, WINDOW_HEIGHT);
    sf::Sprite Sprt;
    Sprt.setTexture(Tex);
    Sprt.setOrigin({Sprt.getLocalBounds().width, Sprt.getLocalBounds().height});
    Sprt.setScale(-1.0, -1.0);

    auto List = std::make_shared<HitableList>();
    List->Add(std::make_unique<Sphere>(Vec3f(0, 0, -1), 0.5));
    List->Add(std::make_unique<Sphere>(Vec3f(3, 1, -4), 0.5));
    List->Add(std::make_unique<Sphere>(Vec3f(0.0, -100.5, -1), 100));

    Camera Cam;

    std::chrono::system_clock::time_point start, end;
    start = std::chrono::system_clock::now();

    if (PARALLEL)
    {
        std::vector<std::thread> Threads;
        for (int i = 0; i < WINDOW_WIDTH / RENDER_CELL_SIZE; i++ )
        {
            for (int j = 0; j < WINDOW_HEIGHT / RENDER_CELL_SIZE; j++ )
            {
                Threads.push_back(std::thread(RenderProc, std::ref(Tex), std::ref(Cam), List, i * RENDER_CELL_SIZE, j * RENDER_CELL_SIZE, RENDER_CELL_SIZE, RENDER_CELL_SIZE));
            }
        }
        for (auto& Th: Threads)
        {
            Th.join();
            Window.draw(Sprt);
            Window.display();
        }
    }
    else
    {
        RenderProc(Tex, Cam, List, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        Window.draw(Sprt);
        Window.display();
    }

    end = std::chrono::system_clock::now();
    double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    std::cout << float(elapsed / 1000) << "(sec)" << std::endl;

    Tex.copyToImage().saveToFile("./image.png");
    while (Window.isOpen())
    {
        sf::Event event;
        if (!Window.pollEvent(event)) continue;
        if (event.type == sf::Event::Closed)
        {
            Window.close();
        }
    }
}
