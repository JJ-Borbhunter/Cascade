#include "Boathouse.hpp"
#include "level.hpp"
#include "framelimit.hpp"
#include "GridUtilities.hpp"
#include "mixer.hpp"
#include "Display.hpp"
#include "Camera.hpp"
#include "NPC.hpp"

#include <SDL3/SDL.h>
#include <iostream>
#include "savedata.hpp"


//17,8 starting location
//7, 8 door
Level boathouse_mainloop(const Display& d, const Camera& c, const Sounds& sounds, Naida& naida, Savedata* savedata){
	Boathouse stage(d);
	SDL_Event event;
	Level level = (Level)boathouse_mainloop;
	std::vector<glm::vec2> v;
	single_listener listener(7, 8);

	NPC uncle{13, 10, "Resources/texture/uncle.png", "Resources/texture/uncletext.png"};
	uncle.reflect();
	repeated_listener uncletalk(13, 10);

	int goal;

	if (savedata->boathouse_waterwheel_activated == true) {
		stage.button.setPressed();
		stage.stream.flow();
		stage.door.open();
		stage.floor.setWalkable(stage.door.getPos());
		stage.wheel.setActive();
	}

	while(level == BOATHOUSE){
		while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) {
                level = nullptr;
                break;
            }
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            	if (uncle.isTalking()) {
            		uncle.shutup();
            	} else if( !naida.Running() ){
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
        	stage.floor.setWalkable(stage.door.getPos());
        	stage.wheel.setActive();
        	savedata->boathouse_waterwheel_activated = true;
        	stage.stream.flow();
        	stage.door.open();
        	sounds.button_sound();
        }


        stage.render(c);
        naida.render(c);
        uncle.draw(c);

        d.update();
        framelimit();


        if (listener.check(naida.getPos())) {
        	level = YARD;
        	naida.setPos(getScreenPosFromIndex(18,8));
        	break;
        }
        if(uncletalk.check(naida.getPos())) {
        	naida.setPos(getScreenPosFromIndex(13, 9));
        	naida.setStationary();
        	naida.setDirection(true);
        	uncle.talk();
        }
	}

	return level;
}