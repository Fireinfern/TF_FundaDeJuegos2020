#include "Agent.h"

#include "ResourceManager.h"
#include "Level.h"



void Agent::checkTilePosition(const std::vector<std::string>& levelData, std::vector<glm::vec2>& collidePosition, float x, float y)
{
	glm::vec2 cornerPos = glm::vec2(floor(x / (float)TILE_WIDTH)
						, floor(y / (float)TILE_WIDTH));
	if (cornerPos.x < 0 || cornerPos.x >= levelData[0].size() ||
		cornerPos.y < 0 || cornerPos.y >= levelData.size()) {
		return;
	}
	if (levelData[cornerPos.y][cornerPos.x] != '.') {
		collidePosition.push_back(cornerPos * (float)TILE_WIDTH 
							+ glm::vec2((float)TILE_WIDTH / 2.0f));
	}
}

void Agent::collidWithTile(glm::vec2 tilePos)
{
	const float TILE_RADIUS = (float)TILE_WIDTH / 2.0f;
	const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;

	glm::vec2 centerPosition = _position + glm::vec2(AGENT_RADIUS);
	glm::vec2 distVec = centerPosition - tilePos;
	float xdepth = MIN_DISTANCE - abs(distVec.x);
	float ydepth = MIN_DISTANCE - abs(distVec.y);
	if (xdepth > 0 || ydepth > 0) {
		if (std::max(xdepth,0.0f) < std::max(ydepth,0.0f)) {
			if (distVec.x < 0) {
				_position.x -= xdepth;
			}
			else {
				_position.x += xdepth;
			}
		}
		else {
			if (distVec.y < 0) {
				_position.y -= ydepth;
			}
			else {
				_position.y += ydepth;
			}
		}
	}
}

Agent::Agent()
{
}

Agent::~Agent()
{
}

bool Agent::collideWithLevel(const std::vector<std::string>& levelData)
{
	std::vector<glm::vec2> collideTilePosition;
	checkTilePosition(levelData, collideTilePosition, _position.x, _position.y);
	checkTilePosition(levelData, collideTilePosition, _position.x + AGENT_WIDTH, _position.y);
	checkTilePosition(levelData, collideTilePosition, _position.x, _position.y+ AGENT_WIDTH);
	checkTilePosition(levelData, collideTilePosition, _position.x + AGENT_WIDTH, _position.y + AGENT_WIDTH);
	if (collideTilePosition.size() == 0)return false;
	for (size_t i = 0; i < collideTilePosition.size(); i++)
	{
		collidWithTile(collideTilePosition[i]);
	}
	return true;
}

bool Agent::collideWithAgent(Agent* agent)
{
	glm::vec2 centerPosA = _position + glm::vec2(AGENT_WIDTH / 2);
	glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_WIDTH / 2);
	glm::vec2 dist = centerPosA - centerPosB;
	const float MIN_DISTANCE = AGENT_RADIUS * 2;
	float distance = glm::length(dist);
	float collisionDepth = MIN_DISTANCE - distance;
	if (collisionDepth > 0) {
		glm::vec2 collisionDepthVec = glm::normalize(dist) * collisionDepth;
		_position += collisionDepth / 2.0f;
		agent->getPosition() -= collisionDepth / 2.0f;
		return true;
	}
	return false;
}

void Agent::draw(SpriteBacth& spriteBatch)
{
	static int textureID;
	GLTexture texture;
	glm::vec4 uvRect;
	if (_sprite == "") {
		texture = ResourceManager::getTexture("Textures/circle.png");
		uvRect = glm::vec4(0.f, 0.f, 1.f, 1.f);
	}
	else {
		texture = ResourceManager::getTexture(_sprite);
		// 2.574f
		uvRect = glm::vec4(112.f / 7.f, 0.5f, 0.14f, 0.5f);
	}
	textureID = texture.id;
	//const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(_position.x, _position.y, AGENT_WIDTH, AGENT_WIDTH);
	spriteBatch.draw(destRect, uvRect, textureID, 0.0f, _color);

}
