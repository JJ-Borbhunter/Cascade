#include "level.hpp"
#include "NPC.hpp"


void setupGarden2Floor(FloorGrid75& floor);


Level garden2_mainloop(const Display& d, const Camera& c, const Sounds& sounds, Naida& naida, Savedata* savedata) {

	SDL_Event event;
	unsigned int goal;
	std::vector<glm::vec2> v;
	Level level = GARDEN2;
	FloorGrid75 floor;

	naida.setPos(getScreenPosFromIndex(11,4));
	setupGarden2Floor(floor);

	Background bkg {"Resources/texture/garden2.png"};
	single_listener back{11, 3};

	std::array<ToggleButton, 5> buttons = {
		ToggleButton{15, 12, false},
		ToggleButton{9, 5, false},
		ToggleButton{7, 7, false},
		ToggleButton{10, 12, false},
		ToggleButton{12, 12, false}
	};

	Bridge bridge1{10, 9, UP_LEFT};
	Bridge bridge2{12, 11, DOWN_RIGHT};

	std::array<Lilypad, 6> lilypads = {
		Lilypad{13,6, true},
		Lilypad{14,8, false},
		Lilypad{15,10, false},
		Lilypad{11,11, false},
		Lilypad{9,7, true},
		Lilypad{7, 10, true}
	};
	floor.setWalkable(lilypads[0].getPos());
	floor.setUnwalkable(lilypads[1].getPos());
	floor.setUnwalkable(lilypads[2].getPos());
	floor.setUnwalkable(lilypads[3].getPos());
	floor.setWalkable(lilypads[4].getPos());
	floor.setWalkable(lilypads[5].getPos());


	std::array<Weeds, 5> weeds = {
		Weeds{13, 9, true},
		Weeds{10, 8, true},
		Weeds{10, 10, true},
		Weeds{8, 8, true},
		Weeds{7, 8, true}
	};

	std::array<Water, 11> streams = {
		Water({0.121094, 69.5547, 64.4141, 37.8594, -196.375, -121.316, -260.773, -83.5508}, true),
		Water({-56.9922, 31.4883, -0.484375, 65.5547, -128.953, 138.547, -181.371, 109.797}, true),
		Water({-0.644531, 65.5625, 65.2109, 36.8164, 188.875, 110.527, 133.285, 140.984}, false),
		Water({-261.176, -83.75, -328.742, -113.883, 134.809, -381.504, 190.715, -349.68}, true),
		Water({319.672, 35.3672, 265.883, 63.9219, -53.543, -117.781, -1.76562, -151.379}, false),
		Water({57.7734, -119.996, -1.37891, -151.855, 267.383, -305.207, 320.105, -273.816}, false),
		Water({398.723, -13.0859, 211.824, -116.426, 266.836, -154.539, 454.66, -44.2266}, false),
		Water({321.859, -122.375, 266.902, -153.395, 398.484, -231.371, 451.34, -200.301}, false),
		Water({-451.367, -42.4727, -328.926, -113.168, -262.957, -84.5273, -392.797, -7.84766}, false),
		Water({-451.941, -43.8867, -394.934, -75.2188, -526.734, -150.664, -587.148, -117.785}, false),
		Water({-394.211, -8.94531, -454.723, -43.4258, -463.434, 97.8516, -394.906, 135.27}, false)
	}; 

	Waterwheel wheel{LEFT, BACK, -475, -7, false, 6};
	Floodgate final_gate{9, 10, true, RIGHT};
	NPC bob{8, 12, "Resources/texture/bob.png", "Resources/texture/bobtext.png"};
	bob.reflect();
	repeated_listener bobtalk{8, 12};

	int i;
	bool update = true;

	while(level == GARDEN2) {
		while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) {
                level = nullptr;
                break;
            }
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            	if(bob.isTalking()){
            		bob.shutup();
            	} else if( !naida.Running() ){
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





        // start of state checking
        glm::vec2 p = naida.getPos();
        if (buttons[0].checkPress(p)) {
        	sounds.button_sound();
        	update = true;
        	//source d
        	streams[10].toggleFlow();
        	streams[9].toggleFlow();
        	streams[8].toggleFlow();
        	wheel.toggleActive();
        	//source a
        	streams[6].toggleFlow();
        	streams[7].toggleFlow();
        	lilypads[2].toggleAlive();
        	floor.toggleWalkable(lilypads[2].getPos());
        }
        if (buttons[1].checkPress(p)) {
        	sounds.button_sound();
        	update = true;
        	//source c
        	streams[2].toggleFlow();
        }
        if (buttons[2].checkPress(p)) {
        	sounds.button_sound();
        	update = true;
        	//source e
        	streams[1].toggleFlow();
        	lilypads[5].toggleAlive();
        	floor.toggleWalkable(lilypads[5].getPos());
        	//source b
        	streams[4].toggleFlow();
        	streams[5].toggleFlow();
        	lilypads[3].toggleAlive();
        	floor.toggleWalkable(lilypads[3].getPos());
        	lilypads[1].toggleAlive();
        	floor.toggleWalkable(lilypads[1].getPos());
        }
        if (buttons[3].checkPress(p)) {
        	sounds.button_sound();
        	update = true;
        	final_gate.close();
        }
        if (buttons[4].checkPress(p)) {
        	sounds.button_sound();
        	update = true;
        	//source a
        	streams[6].toggleFlow();
        	streams[7].toggleFlow();
        	lilypads[2].toggleAlive();
        	floor.toggleWalkable(lilypads[2].getPos());
        }
        if(bridge1.check(p)){
        	bridge1.fall();
        	floor.setWalkable(bridge1.getPos());
        	sounds.bridge_sound();
        }
        if(bridge2.check(p)){
        	bridge2.fall();
        	floor.setWalkable(bridge2.getPos());
        	sounds.bridge_sound();
        }


        if (update) {
        	if((streams[1].flowing() && final_gate.isOpen()) || streams[2].flowing()){
        		streams[0].flow();
        		lilypads[4].setAlive();
        		floor.setWalkable(lilypads[4].getPos());
        	} else {
        		streams[0].cease();
        		lilypads[4].setDead();
        		floor.setUnwalkable(lilypads[4].getPos());
        	}

        	if(streams[0].flowing() || streams[8].flowing()){
        		streams[3].flow();
        		lilypads[0].setAlive();
        		floor.setWalkable(lilypads[0].getPos());
        	} else {
        		streams[3].cease();
        		lilypads[0].setDead();
        		floor.setUnwalkable(lilypads[0].getPos());
        	}

        	if(streams[0].flowing()){
        		weeds[3].setAlive();
        		floor.setUnwalkable(weeds[3].getPos());
        		weeds[4].setAlive();
        		floor.setUnwalkable(weeds[4].getPos());
        		weeds[1].setAlive();
        		floor.setUnwalkable(weeds[1].getPos());
        		weeds[2].setAlive();
        		floor.setUnwalkable(weeds[2].getPos());
        	} else {
        		weeds[3].setDead();
        		floor.setWalkable(weeds[3].getPos());
        		weeds[4].setDead();
        		floor.setWalkable(weeds[4].getPos());
        		weeds[1].setDead();
        		floor.setWalkable(weeds[1].getPos());
        		weeds[2].setDead();
        		floor.setWalkable(weeds[2].getPos());
        	}
        	if(streams[4].flowing()){
        		weeds[3].setAlive();
        		floor.setUnwalkable(weeds[3].getPos());
        		weeds[4].setAlive();
        		floor.setUnwalkable(weeds[4].getPos());
        	}
        	if(streams[6].flowing()){
        		weeds[0].setAlive();
        		floor.setUnwalkable(weeds[0].getPos());
        	} else {
        		weeds[0].setDead();
        		floor.setWalkable(weeds[0].getPos());
        	}
        }


        bkg.draw(c);
        for (i = 0; i < streams.size(); ++i) {
        	streams[i].draw(c);
        }
        for (i = 0; i < buttons.size(); ++i) {
        	buttons[i].draw(c);
        }
        for (i = 0; i < lilypads.size(); ++i) {
        	lilypads[i].draw(c);
        }
        for (i = 0; i < weeds.size(); ++i) {
        	weeds[i].draw(c);
        }
        final_gate.draw(c);
        bridge1.draw(c);
        bridge2.draw(c);
        wheel.draw(c);
        naida.render(c);
        bob.draw(c);

        d.update();
        framelimit();

        if (back.check(naida.getPos()))  {
        	level = GARDEN1;
        	naida.setPos(getScreenPosFromIndex(11, 11));
        }
        if(bobtalk.check(naida.getPos())){
        	naida.setPos(getScreenPosFromIndex(8, 11));
        	naida.setStationary();
        	bob.talk();
        	savedata->talked_to_Bob = true;
        }
	}

	return level;
}



void setupGarden2Floor(FloorGrid75& floor){
	floor.setWalkable(11, 3);
	floor.setWalkable(8, 4);
	floor.setWalkable(9, 4);
	floor.setWalkable(10, 4);
	floor.setWalkable(11, 4);
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
	floor.setWalkable(10, 12);
	floor.setWalkable(10, 11);
	floor.setWalkable(10, 10);
	floor.setWalkable(10, 9);
	floor.setWalkable(10, 8);
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
	floor.setWalkable(12, 10);
	floor.setWalkable(12, 11);
	floor.setWalkable(12, 12);
	floor.setWalkable(14, 12);
	floor.setWalkable(14, 11);
	floor.setWalkable(15, 11);
	floor.setWalkable(15, 12);
	floor.setWalkable(8, 12);
	floor.setWalkable(8, 11);
	floor.setWalkable(7, 12);
	floor.setWalkable(7, 11);
	floor.setWalkable(7, 9);
	floor.setWalkable(8, 9);
	floor.setWalkable(8, 8);
	floor.setWalkable(7, 8);
	floor.setWalkable(7, 7);
	floor.setWalkable(8, 7);

}


