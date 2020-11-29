#pragma once
#include "Human.h"
#include "InputManager.h"
class Player : public Human
{
private:
	InputManager* _inputManager;
	const float spriteWidth = 112.f;
	const float spriteHeight = 32.f;
public:
	Player();
	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans, std::vector<Zombie*>& zombies);
	~Player();
	void init(float speed, glm::vec2 position, InputManager* inputManager);
	void draw(SpriteBacth& spriteBatch);
};

