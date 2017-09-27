#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <string>
#include "library.h"

using namespace std;
using namespace sf;
using namespace mySpace;

/* There are 14 types of items and 17 equipment slots. As EquipmentSlot type ONE_HANDED can also be considered as MAIN_HAND. */
enum ItemType { HEAD, SHOULDERS, CHEST, HANDS, WAIST, LEGS, FEET, COSTUME, NECK, RING, ONE_HANDED, TWO_HANDED, OFF_HAND, POISON };

/* There are 5 types of item rarities. */
enum ItemRarity { NORMAL, FINE, SUPERIOR, EPIC, LEGENDARY };

class Slot
{
protected:
	/* Path to the sprite's texture. */
	string filename;
	/* type is the item's type such as 2h-weapon, 1h-weapon, head, feet, etc. */
	ItemType type;
	/* rarity determines the item name's text color(white, green, blue, purple, yellow). */
	ItemRarity rarity;
	/* Text. */
	Text name, rating, value;
	/* Sprite and Texture */
	Sprite spr_slot;
	Texture texture_slot;
	/* The state of a slot - hovered or not(normal). */
	bool hovered;
public:
	/* Default constructor. */
	Slot();
	/* filename is the complete path to an image file including the file's extension. */
	Slot(string name, string filename, ItemType type, string rating, string value, ItemRarity rarity);
	/* Sets the sprite. 'filename' is the texture's location. */
	void setBaseSprite(string filename);
	/* Getters and setters. */
	Sprite getBaseSprite();
	virtual string getFilename();
	virtual void setFilename(string filename);
	Text getName();
	void setName(string name);
	ItemType getType();
	void setType(ItemType type);
	Text getRating();
	void setRating(string rating);
	Text getValue();
	void setValue(string value);
	ItemRarity getRarity();
	void setRarity(ItemRarity rarity);
	bool getHovered();
	void setHovered(bool flag);
	/* Virtual function for setting the slot's position. */
	virtual void setPosition(Vector2f position);
	/* Virtual function for getting the slot's position. */
	virtual Vector2f Slot::getPosition();
};
