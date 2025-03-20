#pragma once
#include "Display.hpp"
#include "TextRect.hpp"
#include "SimpleLoopingAnimatedTextRect.hpp"
#include "Waterwheel.hpp"
#include "FloorGrid75.hpp"
#include "utility_objects.hpp"
#include "Water.hpp"

class Yard
{
public:
	Yard();

	void render(const Camera& c);
	void render_after(const Camera& c);

	~Yard() {};
	Lilypad lilypad;
	Door door;
	Button button;
	FloorGrid75 floor;
	Water stream;
	Water stream2;
	Water stream3;
	Waterwheel wheel;
	Bridge bridge;
	Floodgate gate;
private:
	Background bkg;
};