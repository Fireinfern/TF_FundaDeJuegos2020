#include "Player.h"
#include <SDL/SDL.h>
#include "ResourceManager.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::init(float speed, glm::vec2 position, 
	InputManager* inputManager)
{
	_speed = speed;
	_position = position;
	_color.set(255, 255, 255, 255);
	_inputManager = inputManager;
	_sprite = "";
	spriteAnimation.init(States::IDLE, 50, {
		"Textures/Character_animation/priests_idle/priest1/v1/priest1_v1_1.png",
		"Textures/Character_animation/priests_idle/priest1/v1/priest1_v1_2.png",
		"Textures/Character_animation/priests_idle/priest1/v1/priest1_v1_3.png",
		"Textures/Character_animation/priests_idle/priest1/v1/priest1_v1_4.png",
		},
		{
		"Textures/Character_animation/priests_idle/priest2/v1/priest2_v1_1.png",
		"Textures/Character_animation/priests_idle/priest2/v1/priest2_v1_2.png",
		"Textures/Character_animation/priests_idle/priest2/v1/priest2_v1_3.png",
		"Textures/Character_animation/priests_idle/priest2/v1/priest2_v1_4.png",
		},
		{
		"Textures/Character_animation/priests_idle/priest3/v1/priest3_v1_1.png",
		"Textures/Character_animation/priests_idle/priest3/v1/priest3_v1_2.png",
		"Textures/Character_animation/priests_idle/priest3/v1/priest3_v1_3.png",
		"Textures/Character_animation/priests_idle/priest3/v1/priest3_v1_4.png",
		});
}

void Player::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans, std::vector<Zombie*>& zombies) {
	if (_inputManager->isKeyPressed(SDLK_w)) {
		_position.y += _speed;
		spriteAnimation.setAnimationState(States::RUN);
	}
	if (_inputManager->isKeyPressed(SDLK_s)) {
		_position.y -= _speed;
		spriteAnimation.setAnimationState(States::RUN);
	}
	if (_inputManager->isKeyPressed(SDLK_a)) {
		_position.x -= _speed;
		spriteAnimation.setAnimationState(States::RUN);
	}
	if (_inputManager->isKeyPressed(SDLK_d)) {
		_position.x += _speed;
		spriteAnimation.setAnimationState(States::RUN);
	}
	collideWithLevel(levelData);
}

void Player::draw(SpriteBacth& spriteBatch) {
	static int textureID;
	GLTexture texture;
	_sprite = spriteAnimation.GetCurrentAnimation();
	texture = ResourceManager::getTexture(_sprite);
	textureID = texture.id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(_position.x, _position.y, AGENT_WIDTH, AGENT_WIDTH);
	spriteBatch.draw(destRect, uvRect, textureID, 0.0f, _color);
}
