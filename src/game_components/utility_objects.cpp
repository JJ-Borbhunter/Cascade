#include "utility_objects.hpp"
#include <iostream>

GLuint utility_object::utility_texture = -1;

utility_object::utility_object(glm::ivec2 p) :
	display{
		(utility_texture == -1) ? (utility_texture = texture_load::OGL_texture("Resources/texture/utilities.png")) : utility_texture,
		125, 125,
		{}
	}
{
	position = p;
	screenPos = glm::vec2((int)p.x, (int)p.y);
	change_single_index_to_screen_coordinates(screenPos);
	display.setPos(screenPos);
}

void utility_object::setPos(glm::ivec2 p){
	position = p;
	screenPos = glm::vec2((int)p.x, (int)p.y);
	change_single_index_to_screen_coordinates(screenPos);
	display.setPos(screenPos);
}


void utility_object::draw(const Camera& c){
	display.draw(c);
}



Button::Button(glm::ivec2 p, bool down) :
utility_object{p}
{
	if (down) {
		setPressed();
	} else {
		setUnpressed();
	}
	Pressed = down;
}

bool Button::checkPress(glm::vec2 pos) {
	if (position == getIndexFromScreenPos(pos) && !Pressed) {
		display.overwriteTexcoords({0.0, 0.25,  0.0, 0.0,  0.25, 0.0,  0.25, 0.25});
		Pressed = true;
		return true;
	}
	return false;
}


Door::Door(glm::ivec2 p, bool closed) :
	utility_object{p}
{
	isClosed = closed;
	display.overwriteTexcoords({0.75, 0.5,  0.75, 0.0,  1.0, 0.0, 1.0, 0.5});

	screenPos = glm::vec2((int)p.x, (int)p.y);
	change_single_index_to_screen_coordinates(screenPos);
	display.setPos(screenPos.x+30, screenPos.y+60);
	display.changeSize(glm::vec2(175/2, 175));
}


Lilypad::Lilypad(glm::ivec2 p, bool alive) :
	utility_object{p}
{
	isAlive = alive;
	if (alive) {
		display.overwriteTexcoords({0.5, 0.25,  0.5, 0.0,  0.75, 0.0, 0.75, 0.25});
	} else {
		display.overwriteTexcoords({0.5, 0.5,  0.5, 0.25,  0.75, 0.25, 0.75, 0.5});	
	}
}


single_listener::single_listener(glm::ivec2 p){
	pos = p;
	triggered = false;
}

bool single_listener::check(glm::vec2 p){
	if (pos == getIndexFromScreenPos(p) && !triggered) {
		triggered = true;
		return true;
	}
	return false;

}

repeated_listener::repeated_listener(glm::ivec2 p){
	pos = p;
	triggered = false;
}

bool repeated_listener::check(glm::vec2 p){
	if (pos == getIndexFromScreenPos(p) && !triggered) {
		triggered = true;
		return true;
	}
	if (triggered && pos != getIndexFromScreenPos(p)) {
		triggered = false;
	}
	return false;

}


Bridge::Bridge(glm::ivec2 p, Bridge_Direction dir) :
	utility_object{p},
	listener{p}
{
	switch (dir) {
	case UP_LEFT:
		display.overwriteTexcoords({0.0, 1.0,  0.0, 0.75,  0.25, 0.75, 0.25, 1.0});
		screenPos += glm::vec2(10, 35);
		break;		
	case UP_RIGHT:
		display.overwriteTexcoords({0.0, 1.0,  0.0, 0.75,  0.25, 0.75, 0.25, 1.0});
		screenPos += glm::vec2(10, 35);
		display.reflect();
		break;
	case DOWN_RIGHT: 
		display.overwriteTexcoords({0.0, 0.75,  0.0, 0.5,  0.25, 0.5, 0.25, 0.75});
		screenPos += glm::vec2(10, 15);
		break;
	case DOWN_LEFT:
		display.overwriteTexcoords({0.0, 0.75,  0.0, 0.5,  0.25, 0.5, 0.25, 0.75});
		screenPos += glm::vec2(10, 15);
		display.reflect();
		break;
	}
	_fallen = false;
	display.setPos(screenPos);
	direction = dir;
}

void Bridge::fall(){
	if (_fallen) {
		return;
	}
	glm::ivec2 down;
	switch (direction) {
	case UP_RIGHT:
		display.overwriteTexcoords({0.25, 1.0,  0.25, 0.75,  0.5, 0.75, 0.5, 1.0});
		down = glm::ivec2(-1, 0);
		break;        
	case UP_LEFT:
		display.overwriteTexcoords({0.25, 1.0,  0.25, 0.75,  0.5, 0.75, 0.5, 1.0});
		down = glm::vec2(-1, 0);
		break;
	case DOWN_RIGHT: 
		display.overwriteTexcoords({0.25, 0.75,  0.25, 0.5,  0.5, 0.5, 0.5, 0.75});
		down = glm::ivec2(1, 0);
		break;
	case DOWN_LEFT:
		display.overwriteTexcoords({0.25, 0.75,  0.25, 0.5,  0.5, 0.5, 0.5, 0.75});
		down = glm::ivec2(0, -1);
		break;
	}
	setPos(getPos() + down);
	_fallen = true;
}


Floodgate::Floodgate(glm::ivec2 p, bool open, WaterwheelDirection dir) :
	utility_object{p}
{
	if (open ){
		display.overwriteTexcoords({0.25, 0.5, 0.25, 0.25, 0.5, 0.25, 0.5, 0.5});
	} else {
		display.overwriteTexcoords({0.0, 0.5, 0.0, 0.25, 0.25, 0.25, 0.25, 0.5});
	}
	if (dir == RIGHT) {
		display.reflect();
	}
	isopen = open;
}

ToggleButton::ToggleButton(glm::ivec2 p, bool down) :
Button{p, down}
{
	state = false;
}

bool ToggleButton::checkPress(glm::vec2 pos) {
	glm::ivec2 test_pos = getIndexFromScreenPos(pos);
	if (!Pressed && position == test_pos) {
		display.overwriteTexcoords({0.0, 0.25,  0.0, 0.0,  0.25, 0.0,  0.25, 0.25});
		Pressed = true;
		state = !state;
		return true;
	}
	if(Pressed && position != test_pos) {
		Pressed = false;
		setUnpressed();
	}
	return false;	
}

