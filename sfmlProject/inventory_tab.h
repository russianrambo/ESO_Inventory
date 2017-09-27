#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include "inventory_slot.h"

using namespace std;
using namespace sf;

/* There are 10 types of inventory tabs. */
enum TabState { ALL, WEAPON, APPAREL, CONSUMABLE, MATERIALS, FURNISHINGS, MISCELLANEOUS, QUEST, JUNK };

class InventoryTab
{
private:
	int itemCount;
	TabState state;
	array<Texture, 3> textures;//3 for now
	Texture texture_rating;//either damage or armor
	Sprite spr_rating;
public:
	InventoryTab();
	/* State determines which tab is active by default. */
	InventoryTab(TabState state);
	/* Array of Inventory Slots. */
	vector<InventorySlot*> slots;
	array<Sprite, 3> icons;//3 for now(all, weapons, apparel)
	/* Getters and Setters. */
	void setItemCount(int newCount);
	int getItemCount();
	void setHovered(int index);
	/* Returns a calculated position of the last slot in the tab. */
	Vector2f getLastSlotPosition();
	/* Adds a new inventory slot to the tab. */
	void addNewSlot(string name, string filename, ItemType type, string rating, string value, ItemRarity rarity, Font &font);
	/* Removes a slot from the inventory tab. Also adjusts the position of each slot inside of the tab. */
	void removeSlot(InventorySlot * item);
	/* Adjusts icons' textures depending on the state of the tab. */
	void adjustState();
	TabState getState();
	void setState(TabState newState);
	/* Loads a new texture into texture_rating depending on the Tab's state. */
	void adjustSprite();
	Sprite getRatingSprite();
};
