#include "level.hpp"

void setup_garden_floor(FloorGrid75& floor);

Level garden1_mainloop(const Display& d, const Camera& c, const Sounds& sounds, Naida& naida, Savedata* savedata) {
	SDL_Event event;
	unsigned int goal;
	std::vector<glm::vec2> v;
	Level level = GARDEN1;
	FloorGrid75 floor;
	single_listener back{11, 3};
	single_listener forward{11, 12};

	Background bkg("Resources/texture/garden1.png");
	Button button1{8, 5, false};
	Button button2{12, 5, false};
	Button button3{15, 5, false};
	std::array<Lilypad, 2> lilypad1 = {
		Lilypad{13, 6, false},
		Lilypad{10, 6, false}
	};
	std::array<Lilypad, 2> lilypad2 = {
		Lilypad{11, 8, false},
		Lilypad{9, 8, false}
	};
	std::array<Lilypad, 2> lilypad3 = {
		Lilypad{12, 10, false},
		Lilypad{10, 10, false}
	};
	Water stream1{{-380.855, -78.7031,
	-325.449, -48.0156,
	185.246, -346.023,
	128.949, -376.414},
	false
	};
	Water stream2{{-250, -1.55078,
	-195.355, 27.668,
	313.832, -271.262,
	260.91, -301.848},
	false
	};
	Water stream3{
		{-118.094, 72.5352,
		-62.5508, 103.281,
		445.379, -196.707,
		391.238, -226.398,},
		false
	};

	setup_garden_floor(floor);
	bool update_states = false;
	int i;

	if(savedata->garden1_solved){
		for (i = 0; i < 2; ++i) {
			lilypad1[i].setAlive();
			lilypad2[i].setAlive();
			lilypad3[i].setAlive();
			floor.setWalkable(lilypad1[i].getPos());
			floor.setWalkable(lilypad2[i].getPos());
			floor.setWalkable(lilypad3[i].getPos());
		}
		stream1.flow();
		stream2.flow();
		stream3.flow();
	}

	while(level == GARDEN1) {
		while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) {
                level = nullptr;
                break;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_SPACE) {
            	
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

        if(!naida.Running()) {
	        if (button1.checkPress(naida.getPos())) {
	        	button2.setUnpressed();
	        	button3.setUnpressed();
	        	update_states = true;
	        	sounds.button_sound();
	        }
	        if (button2.checkPress(naida.getPos())) {
	        	button1.togglePressed();
	        	button3.setUnpressed();
	        	update_states = true;
	        	sounds.button_sound();
	        }
	        if (button3.checkPress(naida.getPos())) {
	        	button2.togglePressed();
	        	update_states = true;
	        	sounds.button_sound();
	        }
	    }


	    if (update_states) {
	    	if (button1.pressed()) {
	    		stream1.flow();
	    		for (i = 0; i < lilypad1.size(); ++i) {
	    			lilypad1[i].setAlive();
	    			floor.setWalkable(lilypad1[i].getPos());
	    		}
	    	} else {
	    		stream1.cease();
	    		for (i = 0; i < lilypad1.size(); ++i) {
	    			lilypad1[i].setDead();
	    			floor.setUnwalkable(lilypad1[i].getPos());
	    		}
	    	}
	        if (button2.pressed()) {
	    		stream2.flow();
	    		for (i = 0; i < lilypad2.size(); ++i) {
	    			lilypad2[i].setAlive();
	    			floor.setWalkable(lilypad2[i].getPos());
	    		}
	    	} else {
	    		stream2.cease();
	    		for (i = 0; i < lilypad2.size(); ++i) {
	    			lilypad2[i].setDead();
	    			floor.setUnwalkable(lilypad2[i].getPos());
	    		}
	    	}
	    	if (button3.pressed()) {
	    		stream3.flow();
	    		for (i = 0; i < lilypad3.size(); ++i) {
	    			lilypad3[i].setAlive();
	    			floor.setWalkable(lilypad3[i].getPos());
	    		}
	    	} else {
	    		stream3.cease();
	    		for (i = 0; i < lilypad3.size(); ++i) {
	    			lilypad3[i].setDead();
	    			floor.setUnwalkable(lilypad3[i].getPos());
	    		}
	    	}
	    	if(stream1.flowing() && stream2.flowing() && stream3.flowing()) {
	    		savedata->garden1_solved = true;
	    	}
	    }
	    update_states = false;


        bkg.draw(c);
        stream1.draw(c);
        stream2.draw(c);
        stream3.draw(c);
        for (i = 0; i < lilypad1.size(); ++i) {
        	lilypad1[i].draw(c);
        }
        for (i = 0; i < lilypad2.size(); ++i) {
        	lilypad2[i].draw(c);
        }
        for (i = 0; i < lilypad3.size(); ++i) {
        	lilypad3[i].draw(c);
        }
        button1.draw(c);
        button2.draw(c);
        button3.draw(c);
        naida.render(c);

        d.update();
        framelimit();


        if(back.check(naida.getPos())){
        	level = YARD;
        	naida.setPos(getScreenPosFromIndex(8, 17));
        }
        if(forward.check(naida.getPos())){
        	level = GARDEN2;
        	naida.setPos(getScreenPosFromIndex(11, 3));
        }
	}
	return level;
}






void setup_garden_floor(FloorGrid75& floor){
	floor.setWalkable(8, 4);
	floor.setWalkable(9, 4);
	floor.setWalkable(10, 4);
	floor.setWalkable(11, 4);
	floor.setWalkable(11, 3);
	floor.setWalkable(12, 4);
	floor.setWalkable(13, 4);
	floor.setWalkable(14, 4);
	floor.setWalkable(15, 4);
	floor.setWalkable(15, 5);
	floor.setWalkable(14, 5);
	floor.setWalkable(13, 5);
	floor.setWalkable(12, 5);
	floor.setWalkable(11, 5);
	floor.setWalkable(10, 5);
	floor.setWalkable(9, 5);
	floor.setWalkable(8, 5);
	floor.setWalkable(8, 7);
	floor.setWalkable(9, 7);
	floor.setWalkable(10, 7);
	floor.setWalkable(11, 7);
	floor.setWalkable(12, 7);
	floor.setWalkable(13, 7);
	floor.setWalkable(14, 7);
	floor.setWalkable(15, 7);
	floor.setWalkable(15, 9);
	floor.setWalkable(14, 9);
	floor.setWalkable(13, 9);
	floor.setWalkable(12, 9);
	floor.setWalkable(11, 9);
	floor.setWalkable(10, 9);
	floor.setWalkable(9, 9);
	floor.setWalkable(8, 9);
	floor.setWalkable(8, 11);
	floor.setWalkable(9, 11);
	floor.setWalkable(10, 11);
	floor.setWalkable(11, 11);
	floor.setWalkable(12, 11);
	floor.setWalkable(13, 11);
	floor.setWalkable(14, 11);
	floor.setWalkable(15, 11);
	floor.setWalkable(11, 12);
}


