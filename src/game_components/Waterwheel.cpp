#include "Waterwheel.hpp"
#include <iostream>

Waterwheel::Waterwheel(WaterwheelDirection dir, WaterwheelRotation rot, float x, float y, bool is_active, int slowness) : 
	active {
		"Resources/texture/waterwheel.png",
		300,
		300,
		//forward, don't ask why lol
		{0},
		{ //left water wheel 0,1,  0,0  1,0  1,1
			{0.00, 0.50,  0.00, 0.00,  0.25, 0.00,  0.25, 0.50},
			{0.25, 0.50,  0.25, 0.00,  0.50, 0.00,  0.50, 0.50},
			{0.50, 0.50,  0.50, 0.00,  0.75, 0.00,  0.75, 0.50},
			{0.75, 0.50,  0.75, 0.00,  1.00, 0.00,  1.00, 0.50},
			{0.00, 1.00,  0.00, 0.50,  0.25, 0.50,  0.25, 1.00},
			{0.25, 1.00,  0.25, 0.50,  0.50, 0.50,  0.50, 1.00},
			{0.50, 1.00,  0.50, 0.50,  0.75, 0.50,  0.75, 1.00},
			{0.75, 1.00,  0.75, 0.50,  1.00, 0.50,  1.00, 1.00}
		},
		slowness
	}
{

	if(dir == RIGHT){
		active.reflect();
	}
	active.setPos(x, y);
	if (is_active) {
		active.overwriteSequence({7, 6, 5, 4, 3, 2, 1});
		if (rot == BACK) {
			active.reverse();
		}
	}
	rotation = rot;
	isactive = is_active;
}


void Waterwheel::draw(const Camera& c){
	active.draw(c);
}

Waterwheel::~Waterwheel(){

}