#include "Human.h"
#include <random>
#include <ctime>
#include <glm\gtx\rotate_vector.hpp>
#include "Zombie.h"
#include "ResourceManager.h"

Human::Human()
{
}

void Human::init(float speed, glm::vec2 position)
{
	_speed = speed;
	_position = position;
	_color.set(255, 255, 255, 255);
	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float>randDir(-1.0f, 1.0f);

	_direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	if (_direction.length() == 0) {
		_direction = glm::vec2(1.0f, 1.0f);
	}
	spriteAnimation.init(States::IDLE, 50,
		{
		"Textures/Character_animation/monsters_idle/vampire/v1/vampire_v1_1.png",
		"Textures/Character_animation/monsters_idle/vampire/v1/vampire_v1_2.png",
		"Textures/Character_animation/monsters_idle/vampire/v1/vampire_v1_3.png",
		"Textures/Character_animation/monsters_idle/vampire/v1/vampire_v1_4.png"
		},
		{
		"Textures/Character_animation/monsters_idle/vampire/v2/vampire_v2_1.png",
		"Textures/Character_animation/monsters_idle/vampire/v2/vampire_v2_2.png",
		"Textures/Character_animation/monsters_idle/vampire/v2/vampire_v2_3.png",
		"Textures/Character_animation/monsters_idle/vampire/v2/vampire_v2_4.png"
		},
		{
		"Textures/Character_animation/monsters_idle/vampire/v1/vampire_v1_1.png",
		"Textures/Character_animation/monsters_idle/vampire/v1/vampire_v1_2.png",
		"Textures/Character_animation/monsters_idle/vampire/v1/vampire_v1_3.png",
		"Textures/Character_animation/monsters_idle/vampire/v1/vampire_v1_4.png"
		});

}

void Human::draw(SpriteBacth& spriteBatch)
{
	static int textureID;
	GLTexture texture;
	_sprite = spriteAnimation.GetCurrentAnimation();
	texture = ResourceManager::getTexture(_sprite);
	textureID = texture.id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(_position.x, _position.y, AGENT_WIDTH, AGENT_WIDTH);
	spriteBatch.draw(destRect, uvRect, textureID, 0.0f, _color);
}

void Human::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans, std::vector<Zombie*>& zombies) {
	
	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float>randDir(-1.0f, 1.0f);
	_position += _direction * _speed;
	if (collideWithLevel(levelData)) {
		_direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	}
	//for (auto zombie : zombies) {
	//	if (collideWithAgent(zombie)) {
	//		Zombie* newZombie = new Zombie();
	//		newZombie->init(1.3f, getPosition());
	//		zombies.push_back(newZombie);
	//		//delete(this);
	//	}
	//}
}

Human::~Human()
{
}
