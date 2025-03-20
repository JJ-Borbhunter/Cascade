#include "NPC.hpp"
#include "GridUtilities.hpp"

const int npc_animation_speed = 15;

NPC::NPC(glm::ivec2 pos, const char* spritesheet, const char* textbox) :
frames{
	spritesheet, 
	125, 
	125, 
	{1, 2}, 
	{
	    {0.0, 1.0,  0.0, 0.0,  1.0/3.0, 0.0,  1.0/3.0, 1.0},
	    {1.0/3.0, 1.0,  1.0/3.0, 0.0,  2.0/3.0, 0.0,  2.0/3.0, 1.0},
	    {2.0/3.0, 1.0,   2.0/3.0, 0.0,  1.0, 0.0,  1.0, 1.0}
	},
	npc_animation_speed
},
diologue{textbox, 900, 200} 
{
	diologue.setPos(0.0, -1 * (450 - (250/2)));
	frames.setPos(getScreenPosFromIndex(pos));
	talking = false;
}

void NPC::talk() {
	talking = true;
	frames.overwriteSequence({0});
}

void NPC::shutup() {
	talking = false;
	frames.overwriteSequence({1, 2});
}

void NPC::draw(const Camera& c){
	frames.draw(c);
	if (talking) {
		diologue.draw(c);
	}
}