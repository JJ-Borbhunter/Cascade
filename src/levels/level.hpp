#pragma once
#include "Display.hpp"
#include "Camera.hpp"
#include "mixer.hpp"
#include "Sounds.hpp"
#include "framelimit.hpp"

#include "Boathouse.hpp"
#include "Naida.hpp"
#include "savedata.hpp"

#include <SDL3/SDL.h>
#include <glm/glm.hpp>


typedef void* (*Level)(const Display& d, const Camera& c, const Sounds& sounds, Naida& naida, Savedata* savedata); 

Level boathouse_mainloop(const Display& d, const Camera& c, const Sounds& sounds, Naida& naida, Savedata* savedata);
Level title_screen(const Display& d, const Camera& c, const Sounds& sounds, Naida& naida, Savedata* savedata);
Level yard_mainloop(const Display& d, const Camera& c, const Sounds& sounds, Naida& naida, Savedata* savedata);
Level garden1_mainloop(const Display& d, const Camera& c, const Sounds& sounds, Naida& naida, Savedata* savedata);
Level garden2_mainloop(const Display& d, const Camera& c, const Sounds& sounds, Naida& naida, Savedata* savedata);
Level tower1_mainloop(const Display& d, const Camera& c, const Sounds& sounds, Naida& naida, Savedata* savedata);
Level tower2_mainloop(const Display& d, const Camera& c, const Sounds& sounds, Naida& naida, Savedata* savedata);
Level end_mainloop(const Display& d, const Camera& c, const Sounds& sounds, Naida& naida, Savedata* savedata);


const Level BOATHOUSE = (Level)boathouse_mainloop;
const Level TITLE = (Level)title_screen;
const Level YARD = (Level)yard_mainloop;
const Level GARDEN1 = (Level)garden1_mainloop;
const Level GARDEN2 = (Level)garden2_mainloop;
const Level TOWER1 = (Level)tower1_mainloop;
const Level TOWER2 = (Level)tower2_mainloop;
const Level END = (Level)end_mainloop;