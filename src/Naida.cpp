#include "Naida.hpp"
#include <iostream>


const int steps = 7;


Naida::Naida() :
	running{
		"Resources/texture/girl.png",
		100,
		100,
		{0},
		{
		    {0.00f, 0.25f,  0.00f, 0.00f,  0.25f, 0.00f,  0.25f, 0.25f}, 
		    {0.25f, 0.25f,  0.25f, 0.00f,  0.50f, 0.00f,  0.50f, 0.25f}, 
		    {0.50f, 0.25f,  0.50f, 0.00f,  0.75f, 0.00f,  0.75f, 0.25f}, 
		    {0.75f, 0.25f,  0.75f, 0.00f,  1.00f, 0.00f,  1.00f, 0.25f}, 

		    {0.00f, 0.50f,  0.00f, 0.25f,  0.25f, 0.25f,  0.25f, 0.50f}, 
		    {0.25f, 0.50f,  0.25f, 0.25f,  0.50f, 0.25f,  0.50f, 0.50f}, 
		    {0.50f, 0.50f,  0.50f, 0.25f,  0.75f, 0.25f,  0.75f, 0.50f}, 
		    {0.75f, 0.50f,  0.75f, 0.25f,  1.00f, 0.25f,  1.00f, 0.50f}, 

		    {0.00f, 0.75f,  0.00f, 0.50f,  0.25f, 0.50f,  0.25f, 0.75f}, 
		    {0.25f, 0.75f,  0.25f, 0.50f,  0.50f, 0.50f,  0.50f, 0.75f}, 
		    {0.50f, 0.75f,  0.50f, 0.50f,  0.75f, 0.50f,  0.75f, 0.75f}, 
		    {0.75f, 0.75f,  0.75f, 0.50f,  1.00f, 0.50f,  1.00f, 0.75f}, 

		    {0.00f, 1.00f,  0.00f, 0.75f,  0.25f, 0.75f,  0.25f, 1.00f}, 
		    {0.25f, 1.00f,  0.25f, 0.75f,  0.50f, 0.75f,  0.50f, 1.00f}, 
		    {0.50f, 1.00f,  0.50f, 0.75f,  0.75f, 0.75f,  0.75f, 1.00f}, 
		    {0.75f, 1.00f,  0.75f, 0.75f,  1.00f, 0.75f,  1.00f, 1.00f}  
		},
		NaidaSlowness
	}
{
	isRunning = false;
	isUp = true;
	prevUp = isUp;
	isRight = false;
	position = glm::vec2(0, 0);
	movetime = 0;
}


void Naida::setRunning(){
	isRunning = true;
	if (isUp) {
		running.overwriteSequence({9, 10, 11, 12, 13, 14, 15}, true);
	} else {
		running.overwriteSequence({1, 2, 3, 4, 5, 6, 7}, true);
	}
	if (isRight) {
		running.setUnreflected();
	} else {
		running.setReflected();
	}
}
void Naida::setStationary(){
	isRunning = false;
	if (isUp) {
		running.overwriteSequence({8}, true);
	} else {
		running.overwriteSequence({0}, true);
	}
}

bool Naida::moveTowards(glm::vec2 loc){

	if (movetime == 0) {
	    isUp = (loc.y > position.y);
	    isRight = (loc.x > position.x);
	}


	if (movetime == steps - 1) {
		position.x = loc.x;
		position.y = loc.y;
		movetime = 0;
		return true;
	}
	position.x += (loc.x - position.x) / (float)steps;
	position.y += (loc.y - position.y) / (float)steps;
	//std::cout << "~" << position.x << " " << position.y << std::endl;
	movetime++;
	return false;
}

void Naida::render(const Camera& c) {
	if (isRight) {
		running.setUnreflected();
	} else {
		running.setReflected();
	}
	if (prevUp != isUp && isRunning) {
		if (isUp) {
			running.overwriteSequence({9, 10, 11, 12, 13, 14, 15}, true);
		} else {
			running.overwriteSequence({1, 2, 3, 4, 5, 6, 7}, true);
		}
	}
	prevUp = isUp;
	running.setPos(position.x, position.y + NaidaHeight);
	running.draw(c);
}




