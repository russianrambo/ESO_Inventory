#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <string>
#include "library.h"

using namespace std;
using namespace sf;
using namespace mySpace;

class Toggle
{
private:
	/* Sprite and Texture */
	Sprite spr_toggle;
	Texture texture_toggle;
	/* Text */
	Text toggle_number;
	/* States */
	bool isActive;//can only be active when there is at least one weapon is slotted in each of the two equipment sets(main_hand, off_hand, poison)
	bool isHovered;
public:
	/* Default constructor. */
	Toggle();
	/* filename is the complete path to an image file including the file's extension. */
	Toggle(string filename, Vector2f position, Font &font, int size);
	void adjustState();
	void switchNumber();
	Sprite getSprite();
	Text getText();
	bool getActive();
	bool getHovered();
	void setActive(bool flag);
	void setHovered(bool flag);
};