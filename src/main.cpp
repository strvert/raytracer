#include <iostream>
#include <memory>
#include <limits>
#include <cstdint>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "vec.h"
#include "ray.h"
#include "utils.h"
#include "sphere.h"
#include "color.h"
#include "camera.h"
#include "mats/materials.h"

constexpr const unsigned int WINDOW_WIDTH = 1200;
constexpr const unsigned int WINDOW_HEIGHT = 600;
constexpr const unsigned int NS = 10;
constexpr const unsigned int RENDER_CELL_SIZE = 40;
constexpr const bool PARALLEL = false;

Color ScreenColor(const Ray& R, const Hitable& World, int Depth)
{
    HitRecord Rec;
    if (World.Hit(R, 0.001, std::numeric_limits<float>::max(), Rec))
    {
        Ray Scattered;
        Color Attenuation;
        if (Depth < 50 && Rec.Mat->Scatter(R, Rec, Attenuation, Scattered))
        {
            return Attenuation * ScreenColor(Scattered, World, Depth+1);
        }
        else
        {
            return Color::FromRGBA256(0, 0, 0);
        }
    }
    else
    {
        return R.ToScreenLerpColor(Color::FromRGBA256(255, 255, 255, 255), Color::FromRGBA256(127, 179, 255, 255));
    }
}

void RenderProc(sf::Texture& Tex, const Camera& Cam, const Hitable& List, const unsigned X, const unsigned Y, const unsigned SizeX, const unsigned SizeY)
{
    std::vector<Color> Map(SizeX*SizeY, Color(0));
    std::vector<std::uint8_t> Data(SizeX*SizeY*4, 255);
    for (unsigned i = X; i < X + SizeX; i++)
    {
        for (unsigned j = Y; j < Y + SizeY; j++)
        {
            Color Sum(0, 0, 0);
            for (int s = 0; s < NS; s++)
            {
                double Rand = Utils::RandZeroToOne();
                float U = float(i + Rand) / float(WINDOW_WIDTH);
                float V = float(j + Rand) / float(WINDOW_HEIGHT);
                Ray R = Cam.GetRay(U, V);
                Sum += ScreenColor(R, List, 0);
            }
            auto Avg = Sum / NS;
            Data[((j-Y)*SizeX + (i-X))*4] = Avg.R256();
            Data[((j-Y)*SizeX + (i-X))*4+1] = Avg.G256();
            Data[((j-Y)*SizeX + (i-X))*4+2] = Avg.B256();
            Data[((j-Y)*SizeX + (i-X))*4+3] = 255;
        }
    }
    Tex.update(reinterpret_cast<sf::Uint8*>(Data.data()), SizeX, SizeY, X, Y);
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

    HitableList List;
    List.Add(std::make_unique<Sphere>(
                Vec<float>(0, 0.8, -1), 0.5,
                std::make_shared<Lambertian>(Color::FromRGBA256(204, 77, 77))));
    List.Add(std::make_unique<Sphere>(
                Vec<float>(-0.6, 0, -1), 0.5,
                std::make_shared<Dielectric>(1.5)));
    List.Add(std::make_unique<Sphere>(
                Vec<float>(-0.6, 0, -1), -0.48,
                std::make_shared<Dielectric>(1.5)));
    List.Add(std::make_unique<Sphere>(
                Vec<float>(0.6, 0, -1), 0.5,
                std::make_shared<Metal>(Color::FromRGBA256(204, 153, 51), 0.1)));
    List.Add(std::make_unique<Sphere>(
                Vec<float>(0.0, -100.5, -1), 100,
                std::make_shared<Lambertian>(Color::FromRGBA256(204, 255, 255))));

    std::chrono::system_clock::time_point start, end;
    start = std::chrono::system_clock::now();

    Camera Cam;
    if (PARALLEL)
    {
        std::vector<std::thread> Threads;
        for (int i = 0; i < WINDOW_WIDTH / RENDER_CELL_SIZE; i++ )
        {
            for (int j = 0; j < WINDOW_HEIGHT / RENDER_CELL_SIZE; j++ )
            {
                Threads.emplace_back(std::thread(
                            RenderProc,
                            std::ref(Tex), std::ref(Cam), std::ref(List),
                            RENDER_CELL_SIZE * i, RENDER_CELL_SIZE * j,
                            RENDER_CELL_SIZE, RENDER_CELL_SIZE
                        ));
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
    }
    Window.draw(Sprt);
    Window.display();

    end = std::chrono::system_clock::now();
    double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    std::cout << float(elapsed / 1000) << " [sec]" << std::endl;

    while (Window.isOpen())
    {
        sf::Event event;
        if (!Window.pollEvent(event)) continue;
        if (event.type == sf::Event::Closed)
        {
            Window.close();
        }
    }

    auto Image = Tex.copyToImage();
    Image.flipHorizontally();
    Image.flipVertically();

    Image.saveToFile("./image.png");
}
