#pragma once

#include "SimpleLoopingAnimatedTextRect.hpp"

#include <array>
#include <GL/gl3w.h>

class Water
{
public:
	Water(std::array<float, 8> positions, bool flow);
	void draw(const Camera& c) { if(_flowing) stream.draw(c); }
	bool flowing() const {return _flowing; }
	void flow() { _flowing = true; }
	void cease() {_flowing = false; }
	void toggleFlow() { _flowing = !_flowing; }
	~Water() {};
private:
	static GLuint WaterTexture;
	SimpleLoopingAnimatedTextRect stream;
	bool _flowing;
};