#include "Yard.hpp"


Yard::Yard() :
lilypad {15, 11, false}, 
door {7, 13, true},
button{8, 10, false},
bkg{"Resources/texture/yard.png"},
stream{{-47.9453, 107.402, 3.29688, 134.809, 595.598, -214.93, 595.746, -270.562}, false},
stream2{{-189.742, 98.3477, -194.055, 264.867, -131.496, 231.109, -140.488, 73.8789}, false},
stream3{{-142.707, 72.1953, -262.871, 3.37891, -315.82, 32.4023, -183.395, 96.8477}, false},
wheel{LEFT, BACK, -225, 137.5, false, 6},
bridge{12, 12, DOWN_LEFT},
gate{8, 11, false, RIGHT},
floor{}
{
	floor.setWalkable(7, 7);
	floor.setWalkable(7, 6);
	floor.setWalkable(7, 5);
	floor.setWalkable(7, 4);
	floor.setWalkable(7, 3);
	floor.setWalkable(8, 3);
	floor.setWalkable(8, 4);
	floor.setWalkable(8, 5);
	floor.setWalkable(8, 6);
	floor.setWalkable(8, 7);
	floor.setWalkable(8, 8);
	floor.setWalkable(8, 9);
	floor.setWalkable(8, 10);
	floor.setWalkable(9, 10);
	floor.setWalkable(9, 9);
	floor.setWalkable(9, 8);
	floor.setWalkable(9, 7);
	floor.setWalkable(9, 6);
	floor.setWalkable(9, 5);
	floor.setWalkable(9, 4);
	floor.setWalkable(9, 3);
	floor.setWalkable(10, 3);
	floor.setWalkable(10, 4);
	floor.setWalkable(10, 5);
	floor.setWalkable(10, 6);
	floor.setWalkable(10, 7);
	floor.setWalkable(10, 8);
	floor.setWalkable(10, 9);
	floor.setWalkable(10, 10);
	floor.setWalkable(11, 10);
	floor.setWalkable(11, 9);
	floor.setWalkable(11, 8);
	floor.setWalkable(11, 7);
	floor.setWalkable(11, 6);
	floor.setWalkable(11, 5);
	floor.setWalkable(11, 4);
	floor.setWalkable(11, 3);
	floor.setWalkable(12, 3);
	floor.setWalkable(12, 4);
	floor.setWalkable(12, 5);
	floor.setWalkable(12, 6);
	floor.setWalkable(12, 7);
	floor.setWalkable(12, 8);
	floor.setWalkable(12, 9);
	floor.setWalkable(12, 10);
	floor.setWalkable(13, 10);
	floor.setWalkable(13, 9);
	floor.setWalkable(13, 8);
	floor.setWalkable(13, 7);
	floor.setWalkable(13, 6);
	floor.setWalkable(13, 5);
	floor.setWalkable(13, 4);
	floor.setWalkable(13, 3);
	floor.setWalkable(14, 3);
	floor.setWalkable(14, 4);
	floor.setWalkable(14, 5);
	floor.setWalkable(14, 6);
	floor.setWalkable(14, 7);
	floor.setWalkable(14, 8);
	floor.setWalkable(14, 9);
	floor.setWalkable(14, 10);
	floor.setWalkable(15, 10);
	floor.setWalkable(15, 9);
	floor.setWalkable(15, 8);
	floor.setWalkable(15, 7);
	floor.setWalkable(15, 6);
	floor.setWalkable(15, 5);
	floor.setWalkable(15, 4);
	floor.setWalkable(16, 5);
	floor.setWalkable(16, 6);
	floor.setWalkable(16, 7);
	floor.setWalkable(16, 8);
	floor.setWalkable(16, 9);
	floor.setWalkable(16, 10);
	floor.setWalkable(17, 10);
	floor.setWalkable(17, 9);
	floor.setWalkable(17, 8);
	floor.setWalkable(17, 7);
	floor.setWalkable(17, 6);
	floor.setWalkable(18, 7);
	floor.setWalkable(18, 8);
	floor.setWalkable(18, 9);
	floor.setWalkable(18, 10);
	floor.setWalkable(16, 12);
	floor.setWalkable(15, 12);
	floor.setWalkable(14, 12);
	floor.setWalkable(13, 12);
	floor.setWalkable(12, 12);
	floor.setWalkable(11, 12);
	floor.setWalkable(10, 12);
	floor.setWalkable(9, 12);
	floor.setWalkable(8, 12);
	floor.setWalkable(8, 13);
	floor.setWalkable(9, 13);
	floor.setWalkable(10, 13);
	floor.setWalkable(11, 13);
	floor.setWalkable(12, 13);
	floor.setWalkable(13, 13);
	floor.setWalkable(14, 13);
	floor.setWalkable(15, 13);
	floor.setWalkable(14, 14);
	floor.setWalkable(13, 14);
	floor.setWalkable(12, 14);
	floor.setWalkable(11, 14);
	floor.setWalkable(10, 14);
	floor.setWalkable(9, 14);
	floor.setWalkable(8, 14);
	floor.setWalkable(8, 15);
	floor.setWalkable(9, 15);
	floor.setWalkable(10, 15);
	floor.setWalkable(11, 15);
	floor.setWalkable(12, 15);
	floor.setWalkable(13, 15);
	floor.setWalkable(12, 16);
	floor.setWalkable(11, 16);
	floor.setWalkable(10, 16);
	floor.setWalkable(9, 16);
	floor.setWalkable(8, 16);
	floor.setWalkable(8, 17);
	floor.setWalkable(9, 17);
	floor.setWalkable(10, 17);
	floor.setWalkable(11, 17);
	floor.setWalkable(10, 18);
	floor.setWalkable(9, 18);
	floor.setWalkable(8, 18);
	floor.setWalkable(5, 5);
	floor.setWalkable(5, 6);
	floor.setWalkable(5, 7);
	floor.setWalkable(5, 8);
	floor.setWalkable(4, 9);
	floor.setWalkable(4, 8);
	floor.setWalkable(4, 7);
	floor.setWalkable(4, 6);
	floor.setWalkable(3, 7);
	floor.setWalkable(3, 8);
	floor.setWalkable(3, 9);
	floor.setWalkable(2, 9);
	floor.setWalkable(2, 8);
}


void Yard::render(const Camera& c){
	bkg.draw(c);
	door.draw(c);
	gate.draw(c);
	stream.draw(c);
	lilypad.draw(c);
	button.draw(c);
	stream2.draw(c);
	stream3.draw(c);
	wheel.draw(c);
	if (bridge.fallen()) bridge.draw(c);
}

void Yard::render_after(const Camera& c){
	if (!bridge.fallen()) bridge.draw(c);
}

