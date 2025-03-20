#include "level.hpp"


Level end_mainloop(const Display& d, const Camera& c, const Sounds& sounds, Naida& naida, Savedata* savedata){
	SDL_Event event;
	Level level = END;
	Background bkg("Resources/texture/end.png");
	TextRect end("Resources/texture/theend.png", 100, 30);
	end.setPos(400, -200);
	int time = 0;

	while(level == END){
		while(SDL_PollEvent(&event)){
			if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) {
                level = nullptr;
                break;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_SPACE) {
                level = nullptr;
                break;
            }
            // if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            // 	level = nullptr;
            // 	break;
            // }
		}

		bkg.draw(c);
		if(time > 10*30) {
			end.draw(c);
		} else {
			time++;
		}
		d.update();
		framelimit();
	}
	return level;
}