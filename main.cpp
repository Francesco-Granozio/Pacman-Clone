#include <iostream>
#include <SFML/Graphics.hpp>

#include "Pacman.h"

sf::RenderWindow window(sf::VideoMode(800, 800), "Pac-Man", sf::Style::Close);

sf::Sprite mapSprite;
sf::Texture mapTexture;

Pacman pacman = Pacman(40, 40);

struct Tile {
    enum tileType{None, Wall, Enemy, Player};
    bool isEmpty = true;
};

Tile tileArray[28][31];

int numberOfTilesX = sizeof(tileArray) / sizeof(tileArray[0]);
int numberOfTilesY = sizeof(tileArray[0]) / sizeof(tileArray[0][0]);

void Draw();
void LoadMap();
void CreateMapColliders();

int main()
{
    LoadMap();
    CreateMapColliders();

    while (window.isOpen())
    {
        //get input
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) 
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    pacman.OnKeyPressed(event.key);
                    //ChangeTestColliderValues(event.key);
                    break;
            }
        }

        //Logic
        pacman.Update();

        //render
        Draw();
    }

    return 0;
}


void LoadMap()
{
    if (mapTexture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(0, 0, 226, 248)))
    {
        mapTexture.setSmooth(false);
        mapSprite.setTexture(mapTexture);
        mapSprite.setScale(window.getSize().x / mapSprite.getLocalBounds().width, window.getSize().y / mapSprite.getLocalBounds().height);
        mapSprite.move(0, 1);
    }
    else 
    {
        std::cout << "texture not loaded correctly" << std::endl;
    }
}

void Draw() 
{
    window.clear();
    window.draw(mapSprite);
    window.draw(pacman.body);

    sf::Vector2f vec(0, 0);


    float dividedNumberX = 800 / (float)numberOfTilesX;
    float dividedNumberY = 800 / (float)numberOfTilesY;

    for (int y = 0; y < numberOfTilesY; y++)
    {
        vec.x = 0;
        for (int x = 0; x < numberOfTilesX; x++)
        {
            sf::VertexArray quad(sf::LinesStrip, 5);
            if (!tileArray[x][y].isEmpty)
            {
                quad[0].color = sf::Color::Transparent;
                quad[1].color = sf::Color::Transparent;
                quad[2].color = sf::Color::Transparent;
                quad[3].color = sf::Color::Transparent;
                quad[4].color = sf::Color::Transparent;
            }
                quad[0].position = vec;

                sf::Vector2f v = vec;
                v.x += dividedNumberX;
                quad[1].position = v;

                quad[2].position = sf::Vector2f(vec.x + dividedNumberX, vec.y + dividedNumberY);

                sf::Vector2f v2 = vec;
                v2.y += dividedNumberY;
                quad[3].position = v2;

                quad[4].position = vec;

                window.draw(quad);
                vec.x += dividedNumberX;
        }
        vec.y += dividedNumberY;
    }


    window.display();
}

void CreateMapColliders() 
{
    for (int i = 0; i < numberOfTilesX; i++)
    {
        tileArray[i][0].isEmpty = false;
        tileArray[i][numberOfTilesY - 1].isEmpty = false;
    }
    for (int i = 2; i <= 5; i++)
    {
        tileArray[i][2].isEmpty = false;
        tileArray[i][3].isEmpty = false;
        tileArray[i][4].isEmpty = false;

        tileArray[i + 20][2].isEmpty = false;
        tileArray[i + 20][3].isEmpty = false;
        tileArray[i + 20][4].isEmpty = false;
    }
    for (int i = 7; i <= 11; i++)
    {
        tileArray[i][2].isEmpty = false;
        tileArray[i][3].isEmpty = false;
        tileArray[i][4].isEmpty = false;

        tileArray[i + 9][2].isEmpty = false;
        tileArray[i + 9][3].isEmpty = false;
        tileArray[i + 9][4].isEmpty = false;
    }
    for (int i = 2; i <= 5; i++)
    {
        tileArray[i][6].isEmpty = false;
        tileArray[i][7].isEmpty = false;

        tileArray[i + 20][6].isEmpty = false;
        tileArray[i + 20][7].isEmpty = false;
    }
    for (int i = 10; i <= 17; i++)
    {
        tileArray[i][6].isEmpty = false;
        tileArray[i][7].isEmpty = false;

        tileArray[i][18].isEmpty = false;
        tileArray[i][19].isEmpty = false;

        tileArray[i][24].isEmpty = false;
        tileArray[i][25].isEmpty = false;
    }
    for (int i = 8; i <= 10; i++)
    {
        tileArray[13][i].isEmpty = false;
        tileArray[14][i].isEmpty = false;

        tileArray[13][i + 12].isEmpty = false;
        tileArray[14][i + 12].isEmpty = false;

        tileArray[13][i + 18].isEmpty = false;
        tileArray[14][i + 18].isEmpty = false;
    }
    for (int i = 6; i <= 13; i++)
    {
        tileArray[7][i].isEmpty = false;
        tileArray[8][i].isEmpty = false;

        tileArray[7 + 12][i].isEmpty = false;
        tileArray[8 + 12][i].isEmpty = false;
    }
    for (int i = 1; i < 10; i++)
    {
        tileArray[0][i].isEmpty = false;
        tileArray[numberOfTilesX - 1][i].isEmpty = false;
    }
    for (int i = 19; i < 30; i++)
    {
        tileArray[0][i].isEmpty = false;
        tileArray[numberOfTilesX - 1][i].isEmpty = false;
    }
    for (int i = 0; i <= 5; i++)
    {
        tileArray[i][9].isEmpty = false;
        tileArray[i][9 + 4].isEmpty = false;
        tileArray[i][9 + 6].isEmpty = false;
        tileArray[i][9 + 10].isEmpty = false;

        tileArray[i + 22][9].isEmpty = false;
        tileArray[i + 22][9 + 4].isEmpty = false;
        tileArray[i + 22][9 + 6].isEmpty = false;
        tileArray[i + 22][9 + 10].isEmpty = false;
    }
}