#pragma once
#include "TextRect.hpp"
#include "texture_load.hpp"
#include "GridUtilities.hpp"
#include "Camera.hpp"
#include <iostream>
#include "Waterwheel.hpp"


enum bridge_direction {UP_RIGHT, UP_LEFT, DOWN_RIGHT, DOWN_LEFT};
typedef enum bridge_direction Bridge_Direction;

class utility_object {
public: 
	utility_object() : utility_object(glm::ivec2(5, 5)) {};
	utility_object(glm::ivec2 p);

	virtual void draw(const Camera& c);
	void reflect() { display.reflect(); }
	glm::ivec2 getPos() { return position; };
	void setPos(glm::ivec2 p);

	~utility_object() {}
protected:
	static GLuint utility_texture;
	TextRect display;
	glm::ivec2 position;
	glm::vec2 screenPos;
};


class Button : public utility_object {
public:
	Button() : Button(glm::ivec2(5,5), 0) {};
	Button(glm::ivec2 p) : Button(p, 0) {};
	Button(glm::ivec2 p, bool down);
	Button(int x, int y, bool down) : Button(glm::ivec2(x, y), down) {};
	Button(int x, int y) : Button(glm::ivec2(x, y), false) {};
	virtual bool checkPress(glm::vec2 pos);
	void togglePressed() {
		if (Pressed) {
			setUnpressed();
		} else {
			setPressed();
		}
	}
	void setUnpressed() { Pressed = false; display.overwriteTexcoords({0.25, 0.25,  0.25, 0.0,  0.50, 0.0,  0.50, 0.25}); }
	void setPressed() { Pressed = true; display.overwriteTexcoords({0.0, 0.25,  0.0, 0.0,  0.25, 0.0,  0.25, 0.25});
 }
	bool pressed() { return Pressed; }
protected:
	bool Pressed;
};


class Door : public utility_object {
public:
	Door() : Door(glm::ivec2(5, 5), true) {};
	Door(glm::ivec2 pos, bool isClosed);
	Door(int x, int y, bool isClosed) : Door(glm::ivec2(x, y), isClosed) {};
	void close() { isClosed = true; }
	void open() { isClosed = false; }

	glm::ivec2 getPos() { return position; }

	void draw(const Camera& c) { if(isClosed) display.draw(c); }
private:
	bool isClosed;
};


class Lilypad : public utility_object {
public:
	Lilypad();
	Lilypad(glm::ivec2 p, bool alive);
	Lilypad(int x, int y, bool alive) : Lilypad(glm::ivec2(x, y), alive) {};
	void setAlive() { isAlive = true; display.overwriteTexcoords({0.5, 0.25,  0.5, 0.0,  0.75, 0.0, 0.75, 0.25}); }
	void setDead() { isAlive = false; display.overwriteTexcoords({0.5, 0.5,  0.5, 0.25,  0.75, 0.25, 0.75, 0.5}); }
	void toggleAlive() {
		if (isAlive) {
			setDead();
		} else {
			setAlive();
		}
	}
	~Lilypad() {};
private:
	bool isAlive;
};

class Background : public TextRect {
public:
	Background(const char* pathname) : TextRect(pathname, 1200, 900) {};
	~Background() {};
};

class single_listener {
public:
	single_listener(glm::ivec2 p);
	single_listener(int x, int y) : single_listener(glm::ivec2(x, y)) {};
	~single_listener() {};
	bool check(glm::vec2 screenpos);
	bool beenTriggered() { return triggered; }
private:
	bool triggered;
	glm::ivec2 pos;
};

class repeated_listener {
public:
	repeated_listener(glm::ivec2 p);
	repeated_listener(int x, int y) : repeated_listener(glm::ivec2(x, y)) {};
	~repeated_listener() {};
	bool check(glm::vec2 screenpos);
	bool beenTriggered() { return triggered; }
private:
	bool triggered;
	glm::ivec2 pos;
};


class Bridge : public utility_object {
public:
	Bridge(glm::ivec2 p, Bridge_Direction dir);
	Bridge(int x, int y, Bridge_Direction dir) : Bridge(glm::ivec2(x, y), dir) {};
	void fall();
	bool fallen() { return _fallen; }
	bool check(glm::vec2 screenpos) {
		if (listener.check(screenpos) && !_fallen) {
			fall(); return true; 
		} 
		return false; 
	};
	~Bridge() {} ;
private:
	Bridge_Direction direction;
	bool _fallen;
	single_listener listener;
};


class Floodgate : public utility_object {
public:
	Floodgate(glm::ivec2 p, bool open, WaterwheelDirection dir);
	Floodgate(int x, int y, bool open, WaterwheelDirection dir) : Floodgate(glm::ivec2(x, y), open, dir) {};
	void open() {isopen = true; display.overwriteTexcoords({0.25, 0.5, 0.25, 0.25, 0.5, 0.25, 0.5, 0.5}); }
	void close() {isopen = false; display.overwriteTexcoords({0.0, 0.5, 0.0, 0.25, 0.25, 0.25, 0.25, 0.5}); }
	bool isOpen() { return isopen; }
	void toggle() { 
		if(isopen){
			close();
		} else {
			open();
		}
	}
private:
	bool isopen;
};



class Weeds : public utility_object {
public:
	Weeds(int x, int y, bool alive) : Weeds(glm::ivec2(x, y), alive) {};
	Weeds(glm::ivec2 p, bool alive) : utility_object{p}, isAlive(alive) {
		display.overwriteTexcoords({0.5, 0.75,  0.5, 0.5,  0.75, 0.5, 0.75, 0.75});
	};

	void setAlive() {isAlive = true;}
	void setDead() {isAlive = false;}

	void draw(const Camera& c) override { if(isAlive) display.draw(c); }

	~Weeds() {};
private:
	bool isAlive;
};


class ToggleButton : public Button {
public:
	ToggleButton(int x, int y, bool down) : ToggleButton(glm::ivec2(x, y), down) {};
	ToggleButton(glm::ivec2 p) : ToggleButton(p, false) {};
	ToggleButton(int x, int y) : ToggleButton(glm::ivec2(x, y), false) {};
	ToggleButton(glm::ivec2 p, bool down);
	bool checkPress(glm::vec2 pos) override;
	bool getState() { return state; }
	~ToggleButton() {};
private:
	bool state;
	bool pressed_last_frame;
};
