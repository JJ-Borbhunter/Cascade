#include "level.hpp"


void tower2_setup_floor(FloorGrid75& floor);


Level tower2_mainloop(const Display& d, const Camera& c, const Sounds& sounds, Naida& naida, Savedata* savedata){
	SDL_Event event;
	Level level = (Level)tower2_mainloop;
	std::vector<glm::vec2> v;
	single_listener listener(15, 8);
	single_listener up(8, 7);

	FloorGrid75 floor;
	tower2_setup_floor(floor);

	Button water_button(8, 10);
	ToggleButton reset_button(13, 5);
	std::array<ToggleButton, 4> buttons = {
		ToggleButton{13, 7},
		ToggleButton{13, 8},
		ToggleButton{13, 9},
		ToggleButton{13, 10}
	};
	std::array<Floodgate, 4> gates = {
		Floodgate{14,7, false, LEFT},
		Floodgate{14,8, false, LEFT},
		Floodgate{14,9, false, LEFT},
		Floodgate{14,10, false, LEFT}
	};

    std::array<Water, 3> streams = {
    	Water({22.3516, 64.293, 73.8672, 91.7188, 455.137, -121.066, 395.875, -154.043}, false),
    	Water({395.875, -154.043, 340.879, -130.445, -62.2344, -350.008, -4.65234, -385.715}, false),
    	Water({-4.65234, -385.715, -6.36719, -448.23, -62.3047, -447.68, -62.4453, -352.695}, false)
    };

	Background bkg{"Resources/texture/tower2.png"};

	int goal;
	int i;


	if(savedata->windmill_puzzle_solved){
		for (i = 0; i < gates.size(); ++i) {
			gates[i].open();
		}
		streams[0].flow();
	}


	while(level == TOWER2){
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



        glm::vec2 p = naida.getPos();

        if(water_button.checkPress(p)){
        	streams[0].flow();
        	sounds.button_sound();
        }

        if(!savedata->windmill_puzzle_solved && !naida.Running()){
        	if (reset_button.checkPress(p)) {
        		sounds.button_sound();
        		for (i = 0; i < gates.size(); ++i) {
        			gates[i].close();
        		}
        	}
			if (buttons[0].checkPress(p)) {
				gates[0].toggle();
				gates[3].toggle();
			    sounds.button_sound();
			}
			if (buttons[1].checkPress(p)) {
				gates[0].toggle();
			    gates[1].toggle();
			    gates[2].toggle();
			    sounds.button_sound();
			}
			if (buttons[2].checkPress(p)) {
			    gates[0].toggle();
			    gates[2].toggle();
			    sounds.button_sound();
			}
			if (buttons[3].checkPress(p)) {
			    gates[0].toggle();
			    sounds.button_sound();
			}
        }


        if(
        	gates[0].isOpen() && 
        	gates[1].isOpen() && 
        	gates[2].isOpen() && 
        	gates[3].isOpen() &&
        	streams[0].flowing()) {
        	savedata->windmill_puzzle_solved = true;
        	streams[1].flow();
        	streams[2].flow();
        }



        bkg.draw(c);
        water_button.draw(c);
        reset_button.draw(c);
        for (i = 0; i < streams.size(); ++i) {
        	streams[i].draw(c);
        }
        for(i = 0; i < buttons.size(); i++){
        	buttons[i].draw(c);
        	gates[i].draw(c);
        }
        naida.render(c);

        d.update();
        framelimit();


        if (listener.check(naida.getPos())) {
        	level = YARD;
        	naida.setPos(getScreenPosFromIndex(8,13));
        	break;
        }
        if(up.check(naida.getPos())){
        	level = TOWER1;
        	naida.setPos(getScreenPosFromIndex(9, 7));
        }
	}

	return level;
}





void tower2_setup_floor(FloorGrid75& floor){
	floor.setWalkable(8, 10);
	floor.setWalkable(8, 9);
	floor.setWalkable(8, 8);
	floor.setWalkable(8, 7);
	floor.setWalkable(8, 6);
	floor.setWalkable(8, 5);
	floor.setWalkable(9, 5);
	floor.setWalkable(9, 6);
	floor.setWalkable(9, 7);
	floor.setWalkable(9, 8);
	floor.setWalkable(9, 9);
	floor.setWalkable(9, 10);
	floor.setWalkable(10, 10);
	floor.setWalkable(10, 9);
	floor.setWalkable(10, 8);
	floor.setWalkable(10, 7);
	floor.setWalkable(10, 6);
	floor.setWalkable(10, 5);
	floor.setWalkable(11, 5);
	floor.setWalkable(11, 6);
	floor.setWalkable(11, 8);
	floor.setWalkable(11, 9);
	floor.setWalkable(11, 10);
	floor.setWalkable(12, 10);
	floor.setWalkable(12, 9);
	floor.setWalkable(12, 8);
	floor.setWalkable(12, 7);
	floor.setWalkable(12, 6);
	floor.setWalkable(12, 5);
	floor.setWalkable(13, 5);
	floor.setWalkable(13, 6);
	floor.setWalkable(13, 7);
	floor.setWalkable(13, 8);
	floor.setWalkable(13, 9);
	floor.setWalkable(13, 10);
}