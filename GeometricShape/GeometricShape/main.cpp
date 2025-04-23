#include "CShapeManager.h"
#include "CCanvas.h"
#include <SFML/Graphics.hpp>
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const std::string WINDOW_TITLE = "Shapes Canvas";

int main(int argc, char* argv[])
{
    CShapeManager manager;
    std::string line;

    std::cout << "Enter shapes:\n";

    while (std::getline(std::cin, line))
    {
        if (line.empty()) break;
        manager.AddShapeFromString(line);
    }

    manager.PrintInfoAboutExtremes();

    if (argc == 1)
    {
        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
        CCanvas canvas(window);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }

            window.clear(sf::Color::White);
            manager.DrawShapes(canvas);
            window.display();
        }
    }

    return 0;
}
