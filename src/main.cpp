// +JMJ+
// A water-themed puzzle game for the 2025 UMass Lowell Game Jam

#include <iostream>
#include <GL/gl3w.h>

#include "Display.hpp"
#include "mixer.hpp"
#include "TextRect.hpp"
#include "Camera.hpp"
#include "error.hpp"
#include "FloorGrid75.hpp"

#include "level.hpp"
#include "savedata.hpp"
#include "Naida.hpp"

#include "Boathouse.hpp"
using namespace std;

const char* appname = "Cascade";


int main(int argc, char const *argv[])
{
	{
	Display d(appname, 3, 3);
	Camera camera(d);
	Mixer mixer;
	Song BGM = mixer.register_music("Resources/music/cascade.mp3");
	Sounds sounds(mixer);

	SDL_Event event;
	glClearColor(135.0f / 255.0f, 206.0f / 255.0f, 250.0f / 255.0f, 1.0f);
	Level level = TITLE;
	Naida naida;
	Savedata* savedata = new Savedata;


	mixer.play_song(BGM);
	while(level != nullptr){
		naida.setStationary();
		level = (Level)level(d, camera, sounds, naida, savedata);
	}

	delete savedata;
	enumerate_opengl_errors();

	}
	SDL_Quit();

	return 0;
}




//###########################################################################//
//                                                                           //
//    Ave Maria, gratia plena, Dominus tecum.                                //
//    Benedicta tu in mulieribus, et benedictus fructus ventris tuis, Iesus. //
//    Sancta Maria, Mater Dei.                                               //
//    Ora pronobis pecatoribus, nunc et in hora mortis nostrae.              //
//    Amen.                                                                  //
//	                                                                         //
//###########################################################################//