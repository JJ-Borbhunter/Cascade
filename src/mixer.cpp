#include <SDL3/SDL.h>
#include <SDL_mixer.h>
#include "mixer.hpp"
#include "error.hpp"
#include <iostream>

Mixer::Mixer(){
	SDL_Init(SDL_INIT_AUDIO);
	if(Mix_OpenAudio(0, nullptr) == false){
		error_raise("Audio decided to panic.\n", "");
		valid = false;
	}
	valid = true;
	//Mix_Volume(-1, 128);
	Mix_VolumeMusic(48);
}


Sound_Effect Mixer::register_sound_effect(const char* path){
	if(!valid) return -1;
	Mix_Chunk* sound = Mix_LoadWAV(path);
	if (sound == nullptr) {
		std::cout << "Failed to load sound: " << path << std::endl;
		return -1;
	}
	vSoundEffects.push_back(sound);
	return vSoundEffects.size() - 1; //end. It will always be the end. 
}

Song Mixer::register_music(const char* path){
	if(!valid) return -1;
	Mix_Music* song = Mix_LoadMUS(path);
	if (song == nullptr) {
		std::cout << "Failed to load sound: " << path << std::endl;
		return -1;
	}
	vSongs.push_back(song);
	return vSongs.size() - 1;
}

int Mixer::play_sound_effect(const Sound_Effect effect) const{
	if(!valid) return -1;
	return Mix_PlayChannel(-1, vSoundEffects[effect], 0);
}


int Mixer::play_song(const Song song) const{
	if (!valid) return -1;
	return Mix_PlayMusic( vSongs[song], -1 );
}






Mixer::~Mixer(){
	//std::cout << vSoundEffects.size() << std::endl;
    for (int i = 0; i < vSoundEffects.size(); ++i) {
        if (vSoundEffects[i] != nullptr) {
            Mix_FreeChunk(vSoundEffects[i]);
        }
    }
	for (int i = 0; i < vSongs.size(); ++i) {
		Mix_FreeMusic(vSongs[i]);
	}
	Mix_Quit();
}