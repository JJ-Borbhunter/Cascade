#pragma once

class Sounds {
public:
	Sounds(Mixer& m) {
		Button = m.register_sound_effect("Resources/sounds/button.wav");
		Bridge = m.register_sound_effect("Resources/sounds/bridge.wav");
		mix = &m;
	};

	void button_sound() const {mix->play_sound_effect(Button); }
	void bridge_sound() const {mix->play_sound_effect(Bridge); }

	~Sounds() {};
private:
	Sound_Effect Button;
	Sound_Effect Bridge;
	const Mixer* mix;
};