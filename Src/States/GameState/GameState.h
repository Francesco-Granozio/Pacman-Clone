#pragma once

#include "../State.h"
#include "../../Tile.h"
#include "../../Entity/Snack/Snack.h"
#include "../../Audio/AudioManager.h"

class Enemy;
class Pacman;

#define NumberOfTilesX 28
#define NumberOfTilesY 31

class GameState : public State
{
public:
	Pacman* pacman;
	Enemy* enemys[4];
	sTile tileArray[NumberOfTilesX][NumberOfTilesY];
	std::vector<Snack*> SnackList;
	sf::Sprite mapSprite;
	sf::Texture mapTexture;
	AudioManager audioManager;

	float tileWidth = 800 / (float)NumberOfTilesX;
	float tileHeight = 800 / (float)NumberOfTilesY;


	GameState(sf::RenderWindow* window, std::stack<State*>* states, GameManager* gameManager);
	~GameState();
	void Update(const float& deltaTime);
	void Draw();
	int FindSnackID(sf::Vector2i snackPos);
	void DeleteSnack(sf::Vector2i snackPos);
	void ScareEnemys();
	void StopPowerSnackSound();
	Enemy* FindEnemyByPosition(sf::Vector2i pos);
private:
	void LoadMap();
	void CreateMapColliders();
	void CreateSnacks();
	void DeleteSnacks();
};
