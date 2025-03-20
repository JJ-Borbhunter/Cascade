#include "level.hpp"


void tower1_setup_floor(FloorGrid75& floor);


Level tower1_mainloop(const Display& d, const Camera& c, const Sounds& sounds, Naida& naida, Savedata* savedata){
	SDL_Event event;
	Level level = (Level)tower1_mainloop;
	std::vector<glm::vec2> v;
	single_listener listener(15, 8);
	single_listener up(8, 7);

	FloorGrid75 floor;
	tower1_setup_floor(floor);

	std::array<Water, 4> happy_streams = {
		Water{{-107.844, 72.2305, 3.92578, 5.33594, 3.92578, -66.6562, -181.883, 34.3867}, true},
		Water{{122.07, 70.1133, 190.07, 36.2266, 6.23438, -67.6953, 4.80469, 4.42188}, true},
		Water{{-62.7773, -50.6445, -321.742, -197.457, -199.219, -188.652, 6.16406, -70.8086}, true},
		Water{{-200.312, -188.758, -321.359, -196.012, 0.878906, -374.531, 66.4961, -337.84}, true}
	};
	std::array<Water, 2> sad_streams = {
		Water{{-59.4023, 104.438, -109.711, 72.8281, -3.01172, 0.9375, 3.77734, 66.6367}, true},
		Water{{3.77734, 66.6367, -0.28125, 1.52344, 124.723, 70.1641, 71.3281, 103.352}, true}
	};


	Background bkg{"Resources/texture/tower1.png"};
	Lilypad lilypad{10, 6, false};
	Bridge bridge{9, 7, DOWN_RIGHT};

	int goal;
	int i;

	if(!savedata->windmill_puzzle_solved){
		lilypad.setAlive();
		floor.setWalkable(lilypad.getPos());
	}

	while(level == TOWER1){
		while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) {
                level = nullptr;
                break;
            }
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            	if( !naida.Running() ){
            		if(floor.resolve_click(event.button.x, event.button.y, d, getIndexFromScreenPos(naida.getPos()), v)){
            			goal = 0;
            			naida.setRunning();
            		}
            	}
            }
        }

        if (naida.Running()) {
        	if (goal == v.size()){
        		naida.setStationary();
        		naida.setPos(v.back());
        	} else if (naida.moveTowards(v[goal])) {
        		goal++;
        	}
        }

        if(bridge.check(naida.getPos())){
        	bridge.fall();
        	floor.setWalkable(bridge.getPos());
        	sounds.bridge_sound();
        }



        bkg.draw(c);
        if(!savedata->windmill_puzzle_solved){
        	for (i = 0; i < happy_streams.size(); ++i) {
        		happy_streams[i].draw(c);
        	}
        }
        sad_streams[0].draw(c);
        sad_streams[1].draw(c);
        lilypad.draw(c);
        bridge.draw(c);

        naida.render(c);

        d.update();
        framelimit();


        if (listener.check(naida.getPos())) {
        	level = YARD;
        	naida.setPos(getScreenPosFromIndex(8,13));
        	break;
        }
        if(up.check(naida.getPos())){
        	level = TOWER2;
        	naida.setPos(getScreenPosFromIndex(10, 7));
        }
	}

	return level;
}





void tower1_setup_floor(FloorGrid75& floor){
	floor.setWalkable(9, 7);
	floor.setWalkable(9, 7);
	floor.setWalkable(9, 8);
	floor.setWalkable(8, 8);
	floor.setWalkable(8, 7);
	floor.setWalkable(8, 6);
	floor.setWalkable(8, 5);
	floor.setWalkable(9, 5);
	floor.setWalkable(9, 6);
	floor.setWalkable(11, 6);
	floor.setWalkable(13, 6);
	floor.setWalkable(14, 6);
	floor.setWalkable(14, 7);
	floor.setWalkable(13, 7);
	floor.setWalkable(12, 7);
	floor.setWalkable(11, 7);
	floor.setWalkable(11, 8);
	floor.setWalkable(12, 8);
	floor.setWalkable(12, 8);
	floor.setWalkable(13, 8);
	floor.setWalkable(14, 8);
	floor.setWalkable(15, 8);
	floor.setWalkable(11, 9);
	floor.setWalkable(12, 9);
	floor.setWalkable(13, 9);
	floor.setWalkable(14, 9);
	floor.setWalkable(14, 10);
	floor.setWalkable(13, 10);
	floor.setWalkable(12, 10);
	floor.setWalkable(11, 10);
	floor.setWalkable(11, 11);
	floor.setWalkable(12, 11);
	floor.setWalkable(13, 11);
	floor.setWalkable(13, 11);
	floor.setWalkable(14, 11);

}