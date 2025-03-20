#pragma once
#include "SimpleLoopingAnimatedTextRect.hpp"
#include "TextRect.hpp"

const int npc_talk_frame_length = 30 * 4;

class NPC
{
public:
	NPC(glm::ivec2 p, const char* spritesheet, const char* textbox);
	NPC(int x, int y, const char* spritesheet, const char* textbox) :
		NPC(glm::ivec2(x, y), spritesheet, textbox) {};
	void talk();
	void shutup();
	bool isTalking(){return talking;}
	void draw(const Camera& c);
	void reflect() {frames.reflect();}
	~NPC() {};
private:
	SimpleLoopingAnimatedTextRect frames;
	TextRect diologue;
	bool talking;
};