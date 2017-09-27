#pragma once

#include "slot.h"
#include "inventory_slot.h"
#include "inventory_tab.h"

class EquipmentSlot : public Slot
{
private:
	Sprite spr_hover;
	bool isOccupied;
	/* Path to a texture belonging to the equipped item. */
	string item_filename;
	/* Type of the equipped item. */
	ItemType item_type;
public:
	/* type - similarly to an item's type. Each equipment slot has a fixed position and image attached to it. */
	EquipmentSlot(ItemType type, string filename, Vector2f position, Texture &texture_hover);
	/* Resets current icon back to the default one. */
	void setToDefault();
	/* Checks whether the selected equipment fits the current slot. */
	bool canEquip(int item_type);
	/* Attempts to equip an item. This method should only be called after canEquip(...). */
	void equip(InventorySlot &inv_slot, int index, EquipmentSlot equipment_slots[], InventoryTab &inv_tab, Font &font);
	/* Attempts to unequip an item. */
	void unEquip(int index, EquipmentSlot equipment_slots[], InventoryTab &inv_tab, Font &font);
	/* Setter for the hover effect sprite. */
	void setHoverTexture(Texture &texture_hover);
	/* Getter for the sprite to draw. */
	Sprite getHoverSprite();
	/* Occupied boolean flag getter and setter */
	bool getOccupied();
	void setOccupied(bool flag);
	/* Getter and Setter for item_filename. */
	string getFilename();
	void setFilename(string filename);
	/* Getter and Setter for item_type. */
	ItemType getItemType();
	void setItemType(ItemType type);
};
