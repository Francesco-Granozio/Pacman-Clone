#include "Pacman.h"
#include "Tile.h"

extern GameManager* gameManager;

Pacman::Pacman(int tileX, int tileY) : body(sf::Vector2f(40, 40))
{
	tilePos = sf::Vector2i(tileX, tileY);
	gameManager->tileArray[tileX][tileY].isEmpty = false;
	gameManager->tileArray[tileX][tileY].tileType = Tile::Player;

	speed = 0.10f;

	if (texture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(230, 1, 13, 13)))
		body.setTexture(&texture);
	else
		std::cout << "texture not loaded correctly" << std::endl;

	body.move(sf::Vector2f(30 * tileX, 20 * tileY));
}

void Pacman::OnKeyPressed(sf::Event::KeyEvent key)
{
	if (key.code == sf::Keyboard::Key::W)
		nextDir = Up;
	else if (key.code == sf::Keyboard::Key::S)
		nextDir = Down;
	else if (key.code == sf::Keyboard::Key::A)
		nextDir = Left;
	else if (key.code == sf::Keyboard::Key::D)
		nextDir = Right;
}

void Pacman::Update()
{
	Move();
}

void Pacman::Move() 
{
	switch (currentDir)
	{
	case None:
		UpdatePlayerTilePosition();
		return;
	case Up:
		if (GetFinalPosition().y <= body.getPosition().y) 
			body.setPosition(body.getPosition().x, body.getPosition().y - speed);
		else
			UpdatePlayerTilePosition();
		break;
	case Down:
		if (GetFinalPosition().y >= body.getPosition().y)
			body.setPosition(body.getPosition().x, body.getPosition().y + speed);
		else
			UpdatePlayerTilePosition();
		break;
	case Left:
		if (GetFinalPosition().x <= body.getPosition().x)
			body.setPosition(body.getPosition().x - speed, body.getPosition().y);
		else
			UpdatePlayerTilePosition();
		break;
	case Right:
		if (GetFinalPosition().x >= body.getPosition().x)
			body.setPosition(body.getPosition().x + speed, body.getPosition().y);
		else
			UpdatePlayerTilePosition();
		break;
	}
}

sf::Vector2f Pacman::GetFinalPosition()
{
	return sf::Vector2f(tilePos.x * gameManager->tileWidth, tilePos.y * gameManager->tileHeight);
}

void Pacman::UpdatePlayerTilePosition()
{
	if (nextDir != None)
	{
		if(IsNeighbourTileAvailable(nextDir))
			currentDir = nextDir;

		nextDir = None;
	}

	if (IsNeighbourTileAvailable(currentDir))
	{
		switch (currentDir)
		{
		case Up:
			UpdateTileArray(sf::Vector2i(tilePos.x, tilePos.y - 1));
			break;
		case Down:
			UpdateTileArray(sf::Vector2i(tilePos.x, tilePos.y + 1));
			break;
		case Left:
			UpdateTileArray(sf::Vector2i(tilePos.x - 1, tilePos.y));
			break;
		case Right:
			UpdateTileArray(sf::Vector2i(tilePos.x + 1, tilePos.y));
			break;
		}
	}
}

void Pacman::UpdateTileArray(sf::Vector2i newPos) 
{
	gameManager->tileArray[tilePos.x][tilePos.y].isEmpty = true;
	gameManager->tileArray[tilePos.x][tilePos.y].tileType = Tile::None;
	tilePos = newPos;
	gameManager->tileArray[tilePos.x][tilePos.y].isEmpty = false;
	gameManager->tileArray[tilePos.x][tilePos.y].tileType = Tile::Player;
}

bool Pacman::IsNeighbourTileAvailable(Directions dir) 
{
	switch (dir)
	{
	case Up:
		if (gameManager->tileArray[tilePos.x][tilePos.y - 1].tileType != Tile::Wall)
			return true;
		break;
	case Down:
		if (gameManager->tileArray[tilePos.x][tilePos.y + 1].tileType != Tile::Wall)
			return true;
		break;
	case Left:
		if (gameManager->tileArray[tilePos.x - 1][tilePos.y].tileType != Tile::Wall)
			return true;
		break;
	case Right:
		if (gameManager->tileArray[tilePos.x + 1][tilePos.y].tileType != Tile::Wall)
			return true;
		break;
	}

	return false;
}