#pragma once

#include "slot.h"

class InventorySlot : public Slot
{
private:
	/* Sprite and Texture for the bar. The item bar's texture and sprite come with the superclass 'Slot'. */
	Sprite spr_bar;
	Texture texture_bar;
public:
	InventorySlot(string name, string filename, ItemType type, string rating, string value, ItemRarity rarity, Font &font, Vector2f position);
	Sprite getSprite();
	void setInvFont(Font &font);
	void setInvTextSize(int size);
	void setInvSlot(Vector2f position);
	void setHovered(bool flag);
	void setGrayedOut(bool flag);
	void setTextColor();//sets the item name's color according to its rarity
	Vector2f getPosition();
	void setPosition(Vector2f position);
};
