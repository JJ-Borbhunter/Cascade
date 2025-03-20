#pragma once
#include "TextRect.hpp"
#include <vector>
#include <cstddef>
#include <array>

class SimpleLoopingAnimatedTextRect : public TextRect {
public:
	SimpleLoopingAnimatedTextRect() {};
	SimpleLoopingAnimatedTextRect(
		const char* pathname, 
		int width, 
		int height, 
		std::vector<uint8_t> sequence, 
		std::vector<std::array<float, 8>> tcoords,
		int animation_Rate
	);
	SimpleLoopingAnimatedTextRect(
		GLuint tID, 
		int width, 
		int height, 
		std::vector<uint8_t> sequence, 
		std::vector<std::array<float, 8>> tcoords,
		int animation_Rate
	);
	void reverse();
	void draw(const Camera& c) override;

	void overwriteSequence(std::vector<uint8_t> s, bool reset_time) { 
		animation_order = s; 
		if (reset_time) {
			time = 0;
			subtime = 0;
		}
	}
	void overwriteSequence(std::vector<uint8_t> s) { overwriteSequence(s, true); }

	~SimpleLoopingAnimatedTextRect();
private:
	int time;
	std::vector<uint8_t> animation_order;
	uint8_t previous_index;
	std::vector<std::array<float, 8>> texcoords;
	int rate;
	int subtime;
};