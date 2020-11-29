#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(): state(States::IDLE)
{
}

SpriteAnimation::~SpriteAnimation()
{
}

void SpriteAnimation::init(States _state, int _sep, std::vector<std::string> _run, std::vector<std::string> _idle, std::vector<std::string> _attack)
{
	state = _state;
	sep = _sep;
	run = _run;
	idle = _idle;
	attack = _attack;
	animIndex = 0;
	spriteIndex = 0;
}

std::string SpriteAnimation::GetCurrentAnimation()
{
	std::string _sprite;
	switch (state) {
	case IDLE:
		_sprite = idle[animIndex];
		break;
	case RUN:
		_sprite = run[animIndex];
		break;
	case ATTACK:
		_sprite = attack[animIndex];
		break;
	}
	spriteIndex++;
	if (spriteIndex >= sep) {
		animIndex++;
		spriteIndex = 0;
	}
	if (animIndex > idle.size() - 1) {
		animIndex = 0;
		setAnimationState(States::IDLE);
	}
	return _sprite;
}

void SpriteAnimation::setRun(std::vector<std::string> _run)
{
	run = _run;
}

void SpriteAnimation::setIdle(std::vector<std::string> _idle)
{
	idle = _idle;
}

void SpriteAnimation::setAttack(std::vector<std::string> _attack)
{
	attack = _attack;
}

void SpriteAnimation::setAnimationState(States _state)
{
	if (state != state) {
		animIndex = 0;
		spriteIndex = 0;
	}
	state = _state;
}
