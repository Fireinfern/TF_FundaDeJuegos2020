#pragma once
#include <glm/glm.hpp>
#include "SpriteBacth.h"
#include <string>

#include "GLTexture.h"
#include "SpriteAnimation.h"

class Human;
class Zombie;

const float AGENT_WIDTH = 60.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;

class Agent
{
protected:
	glm::vec2 _position;
	std::string _sprite;
	SpriteAnimation spriteAnimation;
	float _speed;
	Color _color;
	void checkTilePosition(const std::vector<std::string>& levelData,
		std::vector<glm::vec2>& collidePosition, float x, float y);
	void collidWithTile(glm::vec2 tilePos);
	
	
public:
	Agent();
	virtual void update(const std::vector<std::string>& levelData,
					std::vector<Human*>& humans, std::vector<Zombie*>& zombies) = 0;
	virtual ~Agent();
	bool collideWithLevel(const std::vector<std::string>& levelData);
	bool collideWithAgent(Agent* agent);
	glm::vec2 getPosition()const { return _position; }
	virtual void draw(SpriteBacth& spriteBatch);
};

