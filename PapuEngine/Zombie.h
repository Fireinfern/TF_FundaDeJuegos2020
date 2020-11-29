#pragma once
#include "Agent.h"
class Zombie : public Agent
{
protected:
	glm::vec2 direction;
public:
	Zombie();
	~Zombie();
	void init(float speed, glm::vec2 position);
	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans, std::vector<Zombie*>& zombies);
	Human* getNearestHuman(std::vector<Human*>& humans);
	void draw(SpriteBacth& spriteBatch);
};

