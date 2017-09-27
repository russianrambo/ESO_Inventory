
#include "inventory_slot.h"

InventorySlot::InventorySlot(string name, string filename, ItemType type, string rating, string value, ItemRarity rarity, Font &font, Vector2f position)
	: Slot(name, filename, type, rating, value, rarity)
{
	loadTexture(texture_bar, "ESO_resources/inv_slot.png");
	spr_bar.setTexture(texture_bar);
	setInvFont(font);
	setInvTextSize(15);
	setTextColor();//set item name's color according to its rarity
	setInvSlot(position);
}

void InventorySlot::setInvFont(Font &font)//Pass font by reference
{
	name.setFont(font);
	rating.setFont(font);
	value.setFont(font);
}

void InventorySlot::setInvTextSize(int size)
{
	name.setCharacterSize(size);
	rating.setCharacterSize(size);
	value.setCharacterSize(size);
}

void InventorySlot::setInvSlot(Vector2f position)
{
	spr_bar.setPosition(position);
	spr_slot.setPosition(position.x + 38, position.y + 4);
	name.setPosition(position.x + 95, position.y + 12);
	rating.setPosition(position.x + 370 - rating.getLocalBounds().width, position.y + 12);
	value.setPosition(position.x + 430 - value.getLocalBounds().width, position.y + 12);
}

Sprite InventorySlot::getSprite()
{
	return spr_bar;
}

void InventorySlot::setHovered(bool flag)
{
	if (flag)
	{
		loadTexture(texture_bar, "ESO_resources/hover_inv_slot.png");
	}
	else loadTexture(texture_bar, "ESO_resources/inv_slot.png");
}

void InventorySlot::setGrayedOut(bool flag)
{
	Color c1 = Color(128, 128, 128);//darken the sprite
	Color c2 = Color(255, 255, 255);//white/normal sprite color

	if (flag)
	{
		name.setFillColor(Color(name.getFillColor().r / 2, name.getFillColor().g / 2, name.getFillColor().b / 2));
		rating.setFillColor(c1);
		value.setFillColor(c1);
		spr_slot.setColor(c1);
		spr_bar.setColor(c1);
	}
	else
	{
		setTextColor();//item name's color
		rating.setFillColor(c2);
		value.setFillColor(c2);
		spr_slot.setColor(c2);
		spr_bar.setColor(c2);
	}
}

void InventorySlot::setTextColor()
{
	switch (this->rarity)
	{
	case 0:
		name.setFillColor(Color(200, 200, 200));//Gray-ish
		break;
	case 1:
		name.setFillColor(Color(0, 200, 0));//Green(not lime)
		break;
	case 2:
		name.setFillColor(Color(30, 144, 255));//Blue/dodgerblue
		break;
	case 3:
		name.setFillColor(Color(148, 0, 211));//Purple/darkviolet
		break;
	case 4:
		name.setFillColor(Color(200, 200, 0));//Yellow/darkyellow
		break;
	default:
		name.setFillColor(Color(255, 255, 255));//White
		break;
	}
}

Vector2f InventorySlot::getPosition()
{
	return spr_bar.getPosition();
}
void InventorySlot::setPosition(Vector2f position)
{
	spr_bar.setPosition(position);
}

