#include "level.hpp"
#include "framelimit.hpp"
#include "GridUtilities.hpp"
#include "mixer.hpp"
#include "Display.hpp"
#include "Camera.hpp"


Level title_screen(const Display& d, const Camera& c, const Sounds& mixer, Naida& naida, Savedata* savedata){
	Background image{"Resources/texture/title.png"};
	TextRect press_space{"Resources/texture/space.png", 150, 50};
	SDL_Event event;
	Level level = (Level)title_screen;
	int time = 0;

	press_space.setPos(0, -100);

	while(level == TITLE){
		while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) {
                level = nullptr;
                break;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_SPACE) {
                level = BOATHOUSE;
                naida.setPos(getScreenPosFromIndex(17,8));
                break;
            }
        }

        image.draw(c);
        if (time > 150) {
        	press_space.draw(c);
        }
        time++;

        d.update();
        framelimit();
	}


	return level;
}