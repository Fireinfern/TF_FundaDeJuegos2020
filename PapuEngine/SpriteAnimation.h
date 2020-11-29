#pragma once
#include<string>
#include<vector>

enum States{
	IDLE,
	RUN,
	ATTACK
};

class SpriteAnimation
{
private:
	States state;
	int sep;
	int animIndex;
	int spriteIndex;
	std::vector<std::string> run;
	std::vector<std::string> idle;
	std::vector<std::string> attack;
public:
	SpriteAnimation();
	~SpriteAnimation();
	void init(States _state, int _sep, std::vector<std::string> _run, std::vector<std::string> _idle, std::vector<std::string> _attack);
	std::string GetCurrentAnimation();
	void setRun(std::vector<std::string> _run);
	void setIdle(std::vector<std::string> _idle);
	void setAttack(std::vector<std::string> _attack);
	void setAnimationState(States _state);
};

