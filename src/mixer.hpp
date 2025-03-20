#pragma once
#include <SDL3/SDL.h>
#include <SDL_mixer.h>
#include <vector>

typedef uint32_t Sound_Effect;
#define SOUND_EFFECT_NULL -1
typedef uint32_t Song;
#define SONG_NULL -1


class Mixer
{
public:
	Mixer();
	~Mixer();
	Sound_Effect register_sound_effect(const char* path);
	Song register_music(const char* path);
	int play_sound_effect(const Sound_Effect effect) const;
	int play_song(const Song song) const;
private:
	std::vector<Mix_Chunk*> vSoundEffects;
	std::vector<Mix_Music*> vSongs;
	bool valid;
};