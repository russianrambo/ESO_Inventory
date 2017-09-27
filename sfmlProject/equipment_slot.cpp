
#include "equipment_slot.h"

EquipmentSlot::EquipmentSlot(ItemType type, string filename, Vector2f position, Texture &texture_hover)
{
	this->type = type;
	this->filename = filename;
	isOccupied = false;
	hovered = false;
	spr_slot.setPosition(position);
	setToDefault();
	setHoverTexture(texture_hover);
	spr_hover.setColor(Color(255, 255, 255, 128));//make it half-transparent
	spr_hover.setPosition(position);
}

void EquipmentSlot::setToDefault()
{
	item_filename = "";
	item_type = HEAD;
	name.setString("");
	rating.setString("");
	value.setString("");
	rarity = NORMAL;
	setBaseSprite(filename);//load the default texture
	isOccupied = false;
}

bool EquipmentSlot::canEquip(int item_type)
{
	bool result = false;
	//Either the types of 2 slots are equal, or 1-handed weapon can be equipped into an OFF_HAND slot.
	if (type == item_type || ((type == OFF_HAND && item_type == ONE_HANDED)))
	{
		result = true;
	}
	//2-handed weapons fit into ONE_HANDED slots and automatically occupy OFF_HAND slots.
	else if (item_type == TWO_HANDED && type == ONE_HANDED)
	{
		result = true;
	}
	//The item is not a fit for this slot.
	else
	{
		result = false;
	}
	return result;
}

void EquipmentSlot::equip(InventorySlot &inv_slot, int index, EquipmentSlot equipment_slots[], InventoryTab &inv_tab, Font &font)
{
	//If a 2-h weapon is about to be equipped, unequip any other weapons in both main-hand and off-hand slots
	if (inv_slot.getType() == TWO_HANDED)
	{
		//If the off-hand slot is occupied by a 1-handed weapon, unequip it
		if (equipment_slots[index + 2].getOccupied() && equipment_slots[index + 2].getItemType() == ONE_HANDED)
		{
			equipment_slots[index + 2].unEquip(index + 2, equipment_slots, inv_tab, font);
		}
		//If the main-hand slot is occupied by either a 1-handed or a 2-handed weapon, unequip it
		if (isOccupied)
		{
			unEquip(index, &equipment_slots[0], inv_tab, font);
		}

		equipment_slots[index + 2].setBaseSprite(inv_slot.getFilename());//Change off-hand icon as well
		equipment_slots[index + 2].setFilename(inv_slot.getFilename());
		equipment_slots[index + 2].setName(inv_slot.getName().getString());
		equipment_slots[index + 2].setRating(inv_slot.getRating().getString());
		equipment_slots[index + 2].setValue(inv_slot.getValue().getString());
		equipment_slots[index + 2].setRarity(inv_slot.getRarity());
		equipment_slots[index + 2].setOccupied(true);
		equipment_slots[index + 2].setItemType(inv_slot.getType());
	}
	else if (isOccupied)
	{
		unEquip(index, &equipment_slots[0], inv_tab, font);
	}
	
	item_filename = inv_slot.getFilename();
	setBaseSprite(item_filename);
	name.setString(inv_slot.getName().getString());
	rating.setString(inv_slot.getRating().getString());
	value.setString(inv_slot.getValue().getString());
	rarity = inv_slot.getRarity();
	item_type = inv_slot.getType();
	isOccupied = true;

	inv_tab.removeSlot(&inv_slot);
}

void EquipmentSlot::unEquip(int index, EquipmentSlot equipment_slots[], InventoryTab &inv_tab, Font &font)
{
	//If there is not enough space in the inventory, unequip attempt fails(this is not implemented yet)
	//If trying to equip a one-handed weapon when there is a two-handed weapon equipped,
	//unequip the two-handed weapon.
	inv_tab.addNewSlot(name.getString(), item_filename, item_type, rating.getString(), value.getString(), rarity, font);
	//If there is a 2-H weapon equipped, clear out 2 equipment slots
	if (item_type == TWO_HANDED)
	{
		if (type == OFF_HAND)
		{
			equipment_slots[index - 2].setToDefault();
		}
		else if(type == ONE_HANDED)
		{
			equipment_slots[index + 2].setToDefault();
		}
	}
	setToDefault();
}

void EquipmentSlot::setHoverTexture(Texture &texture_hover)
{
	spr_hover.setTexture(texture_hover);
}
Sprite EquipmentSlot::getHoverSprite()
{
	return spr_hover;
}

bool EquipmentSlot::getOccupied()
{
	return isOccupied;
}
void EquipmentSlot::setOccupied(bool flag)
{
	isOccupied = flag;
}

string EquipmentSlot::getFilename()
{
	return item_filename;
}
void EquipmentSlot::setFilename(string filename)
{
	item_filename = filename;
}

ItemType EquipmentSlot::getItemType()
{
	return item_type;
}
void EquipmentSlot::setItemType(ItemType newType)
{
	item_type = newType;
}