#pragma once
#include "Enemy.h"
class Inky : public Enemy
{
public:
	Inky(sf::Vector2i gridPos);
	~Inky();
private:
	//sf::Vector2i GetChaseTargetPosition() override;
};

