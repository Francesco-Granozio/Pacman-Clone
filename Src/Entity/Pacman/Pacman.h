#pragma once
#include "../../Common.h"
#include "../../GameManager.h"
#include "../Entity.h"
#include "../../Animation/Animation.h"
#include "../../Animation/Animator.h"

class Pacman : public Entity
{
public:
	Pacman(int x, int y);
	~Pacman();
	void OnKeyPressed(sf::Event::KeyEvent key);
	void Update() override;
	void Draw(sf::RenderWindow& rw) override;
private:
	Animator* animator;
	Animation* animations[5];//left, right, up, down, death
	Directions nextDir = None;
	bool hasCompletedMovement = false;
	void Move() override;
	void EatSnack(sf::Vector2i snackGridPosition);
	void UpdatePlayerTilePosition();
	void UpdateTileArray(sf::Vector2i newPos);
	void SetupAnimations();
	void ChangeAnimation(Directions dir);
};

