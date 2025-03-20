#include "level.hpp"
#include "Yard.hpp"
#include "framelimit.hpp"

Level yard_mainloop(const Display& d, const Camera& c, const Sounds& sounds, Naida& naida, Savedata* savedata) {
	SDL_Event event;

	Yard stage;
	unsigned int goal;
	std::vector<glm::vec2> v;
	Level level = YARD;
	bool left_loading_zone = false;

	TextRect gate("Resources/texture/wood.png", 100, 100);
	gate.overwritePositions({-582.254, -85.5938, -584.406, 25.3359, -346.832, 164.969, -348.371, 53.5078 });

	single_listener to_tower{7, 13};

	if (savedata->yard_button_pressed) {
		if (!savedata->windmill_puzzle_solved) {
			stage.lilypad.setAlive();
	        stage.floor.setWalkable(15, 11); //lilypad space
	        stage.stream.flow();
		}
        stage.gate.open();
        stage.button.setPressed();
	}
	if (savedata->yard_bridge_down) {
		stage.bridge.fall();
		stage.floor.setWalkable(stage.bridge.getPos());
	}
	if (savedata->talked_to_Bob) {
		stage.door.open();
		stage.floor.setWalkable(stage.door.getPos());
	}

	if(savedata->windmill_puzzle_solved){
		stage.stream2.flow();
		stage.stream3.flow();
		stage.wheel.setActive();
		gate.overwritePositions({-577.359, 184.066, -576.234, 310.707, -350.707, 162.613, -351.785, 53.7617});
        stage.floor.setWalkable(6, 7);
		stage.floor.setWalkable(6, 6);
		stage.floor.setWalkable(6, 5);
		stage.floor.setWalkable(6, 4);
	}

	while(level == YARD){
		while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) {
                level = nullptr;
                break;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_SPACE) {
            	
            }
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            	if( !naida.Running() ){
            		if(stage.floor.resolve_click(event.button.x, event.button.y, d, getIndexFromScreenPos(naida.getPos()), v)){
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

        if(stage.button.checkPress(naida.getPos())){
        	stage.lilypad.setAlive();
        	stage.floor.setWalkable(15, 11); //lilypad space
        	stage.stream.flow();
        	savedata->yard_button_pressed = true;
        	stage.gate.open();
        	sounds.button_sound();
        }
        if(stage.bridge.check(naida.getPos())){
        	stage.floor.setWalkable(stage.bridge.getPos());
        	savedata->yard_bridge_down = true;
        	sounds.bridge_sound();
        }




        stage.render(c);
        gate.draw(c);
        naida.render(c);
        stage.render_after(c);

        d.update();
        framelimit();

        if (getIndexFromScreenPos(naida.getPos()).x >= 18) {
        	if(left_loading_zone) {
	            level = BOATHOUSE;
	            naida.setPos(getScreenPosFromIndex(8, 8));
	        	break;
	        }
        } else {
        	left_loading_zone = true;
        }
        if (getIndexFromScreenPos(naida.getPos()).y >= 18) {
        	level = GARDEN1;
        	naida.setPos(getScreenPosFromIndex(11, 4));
        }
        if(to_tower.check(naida.getPos())){
        	level = TOWER1;
        	naida.setPos(getScreenPosFromIndex(14, 8));
        }
        if (getIndexFromScreenPos(naida.getPos()).x <= 6) {
        	level = END;
        }
	}
	return level;
}