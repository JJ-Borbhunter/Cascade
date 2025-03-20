#pragma once
#include "Display.hpp"
#include "TextRect.hpp"
#include "SimpleLoopingAnimatedTextRect.hpp"
#include "Waterwheel.hpp"
#include "FloorGrid75.hpp"
#include "utility_objects.hpp"
#include "Water.hpp"

class Boathouse {
public:
	Boathouse(const Display& d);
	~Boathouse();
	void render(const Camera& cam);
	FloorGrid75 floor;
	Waterwheel wheel;
	Button button;
	Water stream;
	Door door;
private:
	Background background1;
};