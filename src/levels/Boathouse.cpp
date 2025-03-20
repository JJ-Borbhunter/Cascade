#include "Boathouse.hpp"
#include "Display.hpp"
#include "TextRect.hpp"
#include <iostream>


Boathouse::Boathouse(const Display& d) : 
	wheel{RIGHT, BACK, 195, 80, false, 6},
	background1{"Resources/texture/boathouse.png"},
	floor{},
	button{glm::ivec2(9, 5)},
	door{glm::ivec2(7, 8), true},
	stream{{-45.2227, 107.184,  1.74219, 134.414,  434.109, -121.844,  388.977, -147.332 }, false}
{
	//Floor Grid time
	floor.setWalkable(8, 10);
	floor.setWalkable(9, 10);
	floor.setWalkable(10, 10);
	floor.setWalkable(11, 10);
	floor.setWalkable(12, 10);
	floor.setWalkable(13, 10);
	floor.setWalkable(14, 10);
	floor.setWalkable(14, 9);
	floor.setWalkable(13, 9);
	floor.setWalkable(12, 9);
	floor.setWalkable(11, 9);
	floor.setWalkable(10, 9);
	floor.setWalkable(8, 9);
	floor.setWalkable(9, 9);
	floor.setWalkable(9, 8);
	floor.setWalkable(8, 8);
	floor.setWalkable(10, 8);
	floor.setWalkable(11, 8);
	floor.setWalkable(12, 8);
	floor.setWalkable(13, 8);
	floor.setWalkable(14, 8);
	floor.setWalkable(15, 8);
	floor.setWalkable(16, 8);
	floor.setWalkable(17, 8);
	floor.setWalkable(17, 7);
	floor.setWalkable(16, 7);
	floor.setWalkable(15, 7);
	floor.setWalkable(14, 7);
	floor.setWalkable(13, 7);
	floor.setWalkable(12, 7);
	floor.setWalkable(11, 7);
	floor.setWalkable(10, 7);
	floor.setWalkable(9, 7);
	floor.setWalkable(8, 7);
	floor.setWalkable(8, 6);
	floor.setWalkable(9, 6);
	floor.setWalkable(10, 6);
	floor.setWalkable(11, 6);
	floor.setWalkable(12, 6);
	floor.setWalkable(13, 6);
	floor.setWalkable(14, 6);
	floor.setWalkable(14, 5);
	floor.setWalkable(13, 5);
	floor.setWalkable(12, 5);
	floor.setWalkable(11, 5);
	floor.setWalkable(10, 5);
	floor.setWalkable(9, 5);
}

void Boathouse::render(const Camera& cam){
	background1.draw(cam);
	stream.draw(cam);
	wheel.draw(cam);
	button.draw(cam);
	door.draw(cam);
}


Boathouse::~Boathouse(){

	//nothing yet
}


