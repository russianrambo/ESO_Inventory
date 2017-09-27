
#include "slot.h"

Slot::Slot()
{
	name.setString("");
	type = HEAD;
	rating.setString("");
	value.setString("");
	rarity = NORMAL;
	hovered = false;

	setBaseSprite("ESO_resources/item_icon.png");//default icon
	spr_slot.setTexture(texture_slot);
}

Slot::Slot(string name, string filename, ItemType type, string rating, string value, ItemRarity rarity)
{
	this->name.setString(name);
	this->filename = filename;
	this->type = type;
	this->rating.setString(rating);
	this->value.setString(value);
	this->rarity = rarity;
	hovered = false;

	setBaseSprite(filename);
	spr_slot.setTexture(texture_slot);
}

Sprite Slot::getBaseSprite()
{
	return spr_slot;
}

void Slot::setBaseSprite(string filename)
{
	loadTexture(texture_slot, filename);
}

//Virtual functions
Vector2f Slot::getPosition()
{
	return spr_slot.getPosition();
}
void Slot::setPosition(Vector2f position)
{
	spr_slot.setPosition(position);
}


string Slot::getFilename()
{
	return filename;
}
void Slot::setFilename(string filename)
{
	this->filename = filename;
}
//END

Text Slot::getName()
{
	return name;
}
void Slot::setName(string name)
{
	this->name.setString(name);
}

ItemType Slot::getType()
{
	return type;
}
void Slot::setType(ItemType type)
{
	this->type = type;
}

Text Slot::getRating()
{
	return rating;
}
void Slot::setRating(string rating)
{
	this->rating.setString(rating);
}

Text Slot::getValue()
{
	return value;
}
void Slot::setValue(string value)
{
	this->value.setString(value);
}

ItemRarity Slot::getRarity()
{
	return rarity;
}
void Slot::setRarity(ItemRarity rarity)
{
	this->rarity = rarity;
}

bool Slot::getHovered()
{
	return hovered;
}
void Slot::setHovered(bool flag)
{
	hovered = flag;
}