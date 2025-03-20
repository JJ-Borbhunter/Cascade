#pragma once
#include "SimpleLoopingAnimatedTextRect.hpp"
#include "TextRect.hpp"

const int NaidaSlowness = 5;
const float NaidaHeight = 30;

class Naida {
public:
	Naida();
	void setPos(float x, float y) { position = glm::vec2(x, y); }
	void setPos(glm::vec2 p) { position = p; }
	glm::vec2 getPos() const { return position; }
	void addPos(float x, float y) { position.x += x; position.y += y; }
	void addPos(glm::vec2 p) { position += p; }
	bool moveTowards(glm::vec2 loc);

	void setRunning();
	void setStationary();
	bool Running() { return isRunning; }
	void setDirection (bool right) {isRight = right;}

	void render(const Camera& c);
	~Naida() {};
private:
	bool isUp;
	bool prevUp;
	bool isRight;
	glm::vec2 position;
	bool isRunning;
	SimpleLoopingAnimatedTextRect running;

	//move towards vars
	int movetime;
};