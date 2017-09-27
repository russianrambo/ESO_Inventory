
#include "inventory_tab.h"

InventoryTab::InventoryTab()
{
	itemCount = 0;
	state = ALL;
}

InventoryTab::InventoryTab(TabState state)
{
	for (unsigned int i = 0; i < icons.size(); i++)
	{
		loadTexture(textures[i], "ESO_resources/item_icon.png");
		icons[i].setTexture(textures[i]);
		icons[i].setPosition(Vector2f(1289 + (float)(30 * i), 198));
	}
	itemCount = 0;
	this->state = state;
	adjustSprite();
	spr_rating.setTexture(texture_rating);
	spr_rating.setPosition(Vector2f(1429, 253));
	adjustState();//load default textures
}

void InventoryTab::setItemCount(int newCount)
{
	itemCount = newCount;
}
int InventoryTab::getItemCount()
{
	return itemCount;
}

void InventoryTab::setHovered(int index)//Later will be TabState instead of int
{
	switch (index)
	{
	case 0:
		loadTexture(textures[index], "ESO_resources/all_icon_hover.png");//all tab icon(NO HOVER EFFECT FOR NOW)
		break;
	case 1:
		loadTexture(textures[index], "ESO_resources/weapon_icon_hover.png");//weapon tab icon
		break;
	case 2:
		loadTexture(textures[index], "ESO_resources/body_icon_hover.png");//apparel tab icon
		break;
	default:
		loadTexture(textures[index], "ESO_resources/item_icon.png");//blank
		break;
	}
}

Vector2f InventoryTab::getLastSlotPosition()
{
	return Vector2f(1125, 273 + (float)(43 * itemCount));
}

void InventoryTab::addNewSlot(string name, string filename, ItemType type, string rating, string value, ItemRarity rarity, Font &font)
{
	slots.push_back(new InventorySlot(name, filename, type, rating, value, rarity, font, getLastSlotPosition()));
	setItemCount(slots.size());
}

void InventoryTab::removeSlot(InventorySlot * item)
{
	int pos = find(slots.begin(), slots.end(), item) - slots.begin();
	slots.erase(slots.begin() + pos);
	setItemCount(slots.size());
}

void InventoryTab::adjustState()
{
	switch (state)
	{
	case 0://all tab icon
		loadTexture(textures[state], "ESO_resources/all_icon_active.png");
		loadTexture(textures[state + 1], "ESO_resources/weapon_icon_inactive.png");
		loadTexture(textures[state + 2], "ESO_resources/body_icon_inactive.png");
		break;
	case 1://weapon tab icon
		loadTexture(textures[state - 1], "ESO_resources/all_icon_inactive.png");
		loadTexture(textures[state], "ESO_resources/weapon_icon_active.png");
		loadTexture(textures[state + 1], "ESO_resources/body_icon_inactive.png");
		break;
	case 2://apparel tab icon
		loadTexture(textures[state - 2], "ESO_resources/all_icon_inactive.png");
		loadTexture(textures[state - 1], "ESO_resources/weapon_icon_inactive.png");
		loadTexture(textures[state], "ESO_resources/body_icon_active.png");
		break;
	default:
		loadTexture(textures[state], "ESO_resources/item_icon.png");//blank
		break;
	}
}

TabState InventoryTab::getState()
{
	return state;
}
void InventoryTab::setState(TabState newState)
{
	state = newState;
	adjustState();//Adjust the state of the icons on state change
	adjustSprite();
}

void InventoryTab::adjustSprite()
{
	if (state == WEAPON)
	{
		loadTexture(texture_rating, "ESO_resources/tab_damage.png");
	}
	else
	{
		loadTexture(texture_rating, "ESO_resources/tab_armor.png");
	}
}

Sprite InventoryTab::getRatingSprite()
{
	return spr_rating;
}
