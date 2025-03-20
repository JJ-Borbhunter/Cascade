#pragma once

struct _savedata
{
	bool boathouse_waterwheel_activated = false;
	bool yard_button_pressed = false;
	bool yard_bridge_down = false;
	bool windmill_puzzle_solved = false;
	bool garden1_solved = false;
	bool talked_to_Bob = false;
};
typedef struct _savedata Savedata;
