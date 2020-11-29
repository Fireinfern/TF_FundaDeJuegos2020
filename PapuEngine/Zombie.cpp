#include "Zombie.h"
#include "Human.h"
#include "ResourceManager.h"

Zombie::Zombie() {

}

Zombie::~Zombie() {

}

void Zombie::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans, std::vector<Zombie*>& zombies){
	for (size_t i = 0; i < zombies.size(); i++) {
		if (!(zombies[i]->getPosition() == getPosition())) {
			collideWithAgent(zombies[i]);
		}
	}
	collideWithLevel(levelData);
	for (size_t i = 0; i < humans.size(); i++) {
		if (collideWithAgent(humans[i])) {
			// delete(humans[i]);
			Zombie* newZombie = new Zombie();
			newZombie->init(1.3f, humans[i]->getPosition());
			zombies.push_back(newZombie);
			humans.erase(humans.begin() + i);
			break;
		}
	}
	Human* closeHuman = getNearestHuman(humans);
	if (closeHuman != nullptr) {
		glm::vec2 direction = glm::normalize(
			closeHuman->getPosition() - _position
		);
		_position += direction * _speed;
	}
}

Human* Zombie::getNearestHuman(std::vector<Human*>& humans) {
	Human* closestHuman = nullptr;
	float smallestDistance = 888888.0f;
	for (size_t i = 0; i < humans.size(); i++)
	{
		glm::vec2 dist = humans[i]->getPosition() - _position;
		float distance = glm::length(dist);
		if (distance < smallestDistance) {
			smallestDistance = distance;
			closestHuman = humans[i];
		}
	}
	return closestHuman;
}

void Zombie::draw(SpriteBacth& spriteBatch)
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

void Zombie::init(float speed, glm::vec2 position) {
	_speed = speed;
	_position = position;
	_color.set(255, 255, 255, 255);
	spriteAnimation.init(States::IDLE, 50,
		{
			"Textures/Character_animation/monsters_idle/skeleton1/v1/skeleton_v1_1.png",
			"Textures/Character_animation/monsters_idle/skeleton1/v1/skeleton_v1_2.png",
			"Textures/Character_animation/monsters_idle/skeleton1/v1/skeleton_v1_3.png",
			"Textures/Character_animation/monsters_idle/skeleton1/v1/skeleton_v1_4.png"
		},
		{
			"Textures/Character_animation/monsters_idle/skeleton1/v2/skeleton_v2_1.png",
			"Textures/Character_animation/monsters_idle/skeleton1/v2/skeleton_v2_2.png",
			"Textures/Character_animation/monsters_idle/skeleton1/v2/skeleton_v2_3.png",
			"Textures/Character_animation/monsters_idle/skeleton1/v2/skeleton_v2_4.png"
		},
		{
			"Textures/Character_animation/monsters_idle/skeleton2/v1/skeleton2_v1_1.png",
			"Textures/Character_animation/monsters_idle/skeleton2/v1/skeleton2_v1_2.png",
			"Textures/Character_animation/monsters_idle/skeleton2/v1/skeleton2_v1_3.png",
			"Textures/Character_animation/monsters_idle/skeleton2/v1/skeleton2_v1_4.png"
		});
}