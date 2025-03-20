#pragma once
#include "TextRect.hpp"
#include "SimpleLoopingAnimatedTextRect.hpp"
#include "Camera.hpp"
#include <iostream>

enum waterwheel_direction {LEFT, RIGHT};
typedef enum waterwheel_direction WaterwheelDirection;

enum waterwheel_rotation {FORWARD, BACK};
typedef enum waterwheel_rotation WaterwheelRotation;


class Waterwheel {
public:
	Waterwheel(): Waterwheel(LEFT, FORWARD, 0, 0, false, 6) {} ;
	Waterwheel(WaterwheelDirection dir, WaterwheelRotation rot, float x, float y, bool active, int slowness);
	void setPos(float x, float y);
	void draw(const Camera& c);

	void setActive() { 	
		active.overwriteSequence({7, 6, 5, 4, 3, 2, 1, 0});
		if (rotation == BACK) {
			active.reverse();
		}
		isactive = true;
	}
	void setInactive() { isactive = false; active.overwriteSequence({0}); }

	void toggleActive() {
		if(isactive){
			setInactive();
		} else {
			setActive();	
		}
	}

	~Waterwheel();
private:
	waterwheel_rotation rotation;
	SimpleLoopingAnimatedTextRect active;
	bool isactive;
};