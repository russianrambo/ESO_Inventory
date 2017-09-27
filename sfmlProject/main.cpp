/**********************************************************************************
*	<The Elder Scrolls Online> - inventory system imitation.
*	Resources Used: Simple and Fast Multimedia Library (SFML),
*					in-game made screenshots(Resolution: 1600x900; 'png' format).
*	By <Andrei Voinov>
*
*	Alt + Enter -> Full Screen Mode/Windowed Mode.
*	Double-click or drag an item to equip it.
*	Double-click an equipped item to unequip it.
*   Esc to exit.
***********************************************************************************/

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include "inventory_slot.h"
#include "equipment_slot.h"
#include "toggle.h"
#include "inventory_tab.h"
#include "library.h"

using namespace std;
using namespace sf;
using namespace mySpace;

//This screen resolution is fixed because of the resolution of all the screenshots which is 1600x900
const int WIDTH = 1600;
const int HEIGHT = 900;

int main()
{
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "ESO Inventory");
	bool fullscreen = false;//Windowed mode by default.
	bool dragging = false;
	bool hovering = false;
	bool drawFeedback = false;
	Texture texture_ui, texture_hover, texture_drag, texture_highlight;
	Sprite spr_ui, spr_drag;
	Sprite spr_h1, spr_h2, spr_h3;//weapon row - 3 weapon slots with a highlight effect.
	Font font;
	Color half_transparent = Color(255, 255, 255, 128);

	//LMB Double-click timing
	float elapsed1 = 10;//time between clicks.
	int numOfClicks = 1;//sort of a cooldown on double-clicking to avoid chained double-clicking(when a 3rd click is recognised as another double-click).
	float elapsed2 = 10;//feedback presence time.
	Clock clock1, clock2;//clock1 - double-click; clock2 - feedback timer.

	int mouseX = 0;
	int mouseY = 0;

	//Y-coordinates for the highlight effect of the 2 rows of weapons
	float pos_top = 494;
	float pos_bot = 534;

	//Load the background
	loadTexture(texture_ui, "ESO_resources/main_ui.png");
	spr_ui.setTexture(texture_ui);//the position of the sprite is (0, 0) by default
	//Load the hover and highlight texture
	loadTexture(texture_hover, "ESO_resources/hover_icon.png");//default hover effect texture for all equipment slots
	loadTexture(texture_highlight, "ESO_resources/active_weapon.png");
	spr_h1.setTexture(texture_highlight);
	spr_h2.setTexture(texture_highlight);
	spr_h3.setTexture(texture_highlight);
	spr_h1.setPosition(5, 494);
	spr_h2.setPosition(50, 494);
	spr_h3.setPosition(95, 494);
	spr_h1.setColor(half_transparent);
	spr_h2.setColor(half_transparent);
	spr_h3.setColor(half_transparent);
	//Load the font
	if (!font.loadFromFile("ESO_resources/univers-67-condensed-bold.ttf"))//default font for the whole project
	{
		cout << "Font file not found" << endl;
		exit(EXIT_FAILURE);
	}
	Text feedback = Text("FEEDBACK", font, 18);//Top-right corner of the screen. White-colored text-based feedback on failed actions.
	int items_limit = 100;//Maximum number of items that can be present in the inventory at any given time
	Text number_of_items = Text("1 / " + to_string(items_limit), font, 14);
	number_of_items.setPosition(Vector2f(1252, 759));
	
	//INITIALIZE THE EQUIPMENT SLOTS (17 in total). Just like in the UI, positions of all the slots are fixed in the array.
	array<EquipmentSlot, 17> equipment_slots = { EquipmentSlot(HEAD, "ESO_resources/head_empty.png", Vector2f(54, 222), texture_hover),
		EquipmentSlot(SHOULDERS, "ESO_resources/shoulders_empty.png", Vector2f(10, 269), texture_hover), EquipmentSlot(CHEST, "ESO_resources/chest_empty.png", Vector2f(104, 269), texture_hover),
		EquipmentSlot(HANDS, "ESO_resources/hands_empty.png", Vector2f(10, 314), texture_hover), EquipmentSlot(WAIST, "ESO_resources/waist_empty.png", Vector2f(104, 314), texture_hover),
		EquipmentSlot(LEGS, "ESO_resources/legs_empty.png", Vector2f(10, 359), texture_hover), EquipmentSlot(FEET, "ESO_resources/feet_empty.png", Vector2f(104, 359), texture_hover),
		EquipmentSlot(COSTUME, "ESO_resources/costume_empty.png", Vector2f(9, 427), texture_hover), EquipmentSlot(NECK, "ESO_resources/neck_empty.png", Vector2f(50, 427), texture_hover),
		EquipmentSlot(RING, "ESO_resources/ring_empty.png", Vector2f(90, 427), texture_hover), EquipmentSlot(RING, "ESO_resources/ring_empty.png", Vector2f(130, 427), texture_hover),
		EquipmentSlot(ONE_HANDED, "ESO_resources/weapon_empty.png", Vector2f(10, 499), texture_hover), EquipmentSlot(ONE_HANDED, "ESO_resources/weapon_empty.png", Vector2f(10, 539), texture_hover),
		EquipmentSlot(OFF_HAND, "ESO_resources/off_hand_empty.png", Vector2f(55, 499), texture_hover), EquipmentSlot(OFF_HAND, "ESO_resources/off_hand_empty.png", Vector2f(55, 539), texture_hover),
		EquipmentSlot(POISON, "ESO_resources/poison_empty.png", Vector2f(100, 499), texture_hover), EquipmentSlot(POISON, "ESO_resources/poison_empty.png", Vector2f(100, 539), texture_hover)
	};
	//END OF INITIALIZATION

	//Set up the weapon toggle button
	Toggle weapon_toggle = Toggle("ESO_resources/toggle_inactive.png", Vector2f(138, 510), font, 11);

	//Set up the inventory tab
	InventoryTab inv_tab = InventoryTab(WEAPON);
	//ADD INVENTORY SLOTS TO THE INVENTORY TAB
	inv_tab.addNewSlot("Bow of Hunding's Rage", "ESO_resources/bow.png", TWO_HANDED, "1120", "70", SUPERIOR, font);
	inv_tab.addNewSlot("Galatite Dagger of Decrease Health", "ESO_resources/dagger1.png", ONE_HANDED, "1120", "43", SUPERIOR, font);
	inv_tab.addNewSlot("Galatite Dagger of Decrease Health", "ESO_resources/dagger2.png", ONE_HANDED, "1120", "43", SUPERIOR, font);
	inv_tab.addNewSlot("Areldur's Ring", "ESO_resources/ring.png", RING, "", "43", SUPERIOR, font);
	inv_tab.addNewSlot("Signet of the Warlock", "ESO_resources/ring.png", RING, "", "50", LEGENDARY, font);
	inv_tab.addNewSlot("Bloodthorn Disguise", "ESO_resources/outfit.png", COSTUME, "", "0", NORMAL, font);
	inv_tab.addNewSlot("Embrace of Shadows", "ESO_resources/armor.png", CHEST, "1604", "46", FINE, font);
	inv_tab.addNewSlot("Ruby Necklace of Flame Resist", "ESO_resources/necklace.png", NECK, "", "43", EPIC, font);
	inv_tab.addNewSlot("Belt of the Red Mountain", "ESO_resources/belt.png", WAIST, "673", "24", FINE, font);
	inv_tab.addNewSlot("Mask of Shadows", "ESO_resources/helm.png", HEAD, "1403", "38", FINE, font);
	inv_tab.addNewSlot("Footpads of Shadows", "ESO_resources/boots.png", FEET, "1403", "23", FINE, font);
	//END OF ADDING

	//Pointers and reusable variables
	EquipmentSlot * eqSlot = NULL;//A pointer to an equipment slot. Used for equipping items.
	int eq_index = 0;//Index of an equipment slot inside of the premade array. Used for equipping items.
	int eq_index2 = 0;//Second index
	InventorySlot * item = NULL;//A pointer to an inventory slot. Used for dragging/equipping items.
	loadTexture(texture_drag, "ESO_resources/item_icon.png");//blank icon image
	spr_drag.setTexture(texture_drag);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
			//Most oftenly used key-combination Alt+Enter which triggers the Fullscreen mode
			if (Keyboard::isKeyPressed(Keyboard::RAlt) && Keyboard::isKeyPressed(Keyboard::Return))
			{
				VideoMode desktop = VideoMode::getDesktopMode();//get the screen resolution
				window.create(VideoMode(desktop.width, desktop.height), "ESO Inventory", (fullscreen ? Style::Fullscreen : Style::Default));
				fullscreen = !fullscreen;
			}
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
			{
				elapsed1 = clock1.restart().asSeconds();
				//Weapon row toggle
				if (weapon_toggle.getSprite().getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y) 
					&& weapon_toggle.getActive())
				{
					//Switch the number
					weapon_toggle.switchNumber();
					if (spr_h1.getPosition().y == pos_top)
					{
						spr_h1.setPosition(5, pos_bot);
						spr_h2.setPosition(50, pos_bot);
						spr_h3.setPosition(95, pos_bot);
					}
					else
					{
						spr_h1.setPosition(5, pos_top);
						spr_h2.setPosition(50, pos_top);
						spr_h3.setPosition(95, pos_top);
					}
				}
				//Inventory tab icons
				for (unsigned int i = 0; i < inv_tab.icons.size(); i++)
				{
					if (inv_tab.icons[i].getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y))
					{
						inv_tab.setState((TabState)i);
					}
				}
				//The mouse cursor is positioned over an equipment slot.
				if (eqSlot != NULL && hovering)
				{
					if (elapsed1 <= 0.5 && numOfClicks == 1)//Windows default time between clicks for double-click is 500ms or 0.5s
					{
						numOfClicks++;
						if (inv_tab.getItemCount() == items_limit)
						{
							feedback.setString("You do not have enough space in your inventory");
							feedback.setPosition(WIDTH - feedback.getLocalBounds().width - 20, feedback.getLocalBounds().height);
							drawFeedback = true;
							clock2.restart();
						}
						else
						{
							eqSlot->unEquip(eq_index, &equipment_slots[0], inv_tab, font);
						}
					}
					else
					{
						numOfClicks = 1;
					}
				}
				//The mouse cursor is positioned over an inventory slot and nothing is being dragged atm.
				if (item != NULL && item->getSprite().getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y))
				{
					//Left mouse double-click means an attempt to equip an item
					if (elapsed1 <= 0.5 && numOfClicks == 1)//Windows default time between clicks for double-click is 500ms or 0.5s
					{
						numOfClicks++;
						vector<EquipmentSlot*> eq_ref;
						for (unsigned int i = 0; i < equipment_slots.size(); i++)
						{
							bool result = equipment_slots[i].canEquip(item->getType());
							//Special case for active weapon row when i is (11-13-15 or 12-14-16)
							if (weapon_toggle.getText().getString() == "1")
							{
								//If the result is true, keep one or two references to equipment slots
								if (result && i != 12 && i != 14 && i!= 16)
								{
									eq_ref.push_back(&equipment_slots[i]);
									if (eq_ref.size() == 1)
									{
										eq_index = i;
									}
									if (eq_ref.size() == 2)
									{
										eq_index2 = i;
									}
								}
							}
							else
							{
								if (result && i != 11 && i != 13 && i != 15)
								{
									eq_ref.push_back(&equipment_slots[i]);
									if (eq_ref.size() == 1)
									{
										eq_index = i;
									}
									if (eq_ref.size() == 2)
									{
										eq_index2 = i;
									}
								}
							}
						}
						//If the there was only 1 slot found
						if (eq_ref.size() == 1)//any item that is NOT a 1-h weapon or a ring
						{
							eq_ref[0]->equip(*item, eq_index, &equipment_slots[0], inv_tab, font);
						}
						//If the there were 2 slots found(One-handed weapon or ring)
						else if (eq_ref.size() == 2)//Only 1-handed weapons or rings fall into this category
						{
							if (!eq_ref[0]->getOccupied())//the slot is empty, equip the item
							{
								eq_ref[0]->equip(*item, eq_index, &equipment_slots[0], inv_tab, font);
							}
							//If the first slot is occuped, but the second slot is empty
							else if (!eq_ref[1]->getOccupied())
							{
								eq_ref[1]->equip(*item, eq_index2, &equipment_slots[0], inv_tab, font);
							}
							//If both slots are occupied, equip the item into the first found slot
							else
							{
								eq_ref[0]->equip(*item, eq_index, &equipment_slots[0], inv_tab, font);
							}
						}
						else
						{//this should never be executed unless there is a coding error
							cout << "ERROR: failed to find a suitable equipment slot" << endl;
							cout << "Size of the array: " << eq_ref.size() << endl;
						}
					}
					else
					{
						numOfClicks = 1;
						dragging = true;
						item->setGrayedOut(true);//gray out the selected slot
						window.setMouseCursorVisible(false);
					}
				}
			}
			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && dragging)
			{
				//If released on top of EquipmentSlot - try to equip
				if (hovering)
				{
					bool result = eqSlot->canEquip(item->getType());
					//If result is true, remove item from the inventory; otherwise, print text-based feedback
					if (result)
					{
						eqSlot->equip(*item, eq_index, &equipment_slots[0], inv_tab, font);
					}
					else
					{
						feedback.setString("Item cannot be equipped in that slot");
						feedback.setPosition(WIDTH - feedback.getLocalBounds().width - 20, feedback.getLocalBounds().height);
						drawFeedback = true;
						clock2.restart();
					}
					dragging = false;
					window.setMouseCursorVisible(true);
					item->setGrayedOut(false);//revert the selected inventory slot back to normal
				}
				else 
				{
					//If released on top of InventorySlot(later InventoryTab) - revert back to normal; else, keep it floating
					if (item != NULL && item->getSprite().getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y))
					{
						dragging = false;
						window.setMouseCursorVisible(true);
						item->setGrayedOut(false);//revert the selected inventory slot back to normal
					}
				}
			}
			if (event.type == Event::MouseMoved)
			{
				mouseX = event.mouseMove.x;
				mouseY = event.mouseMove.y;
			}
		}
		//Hover effect for the equipment slots
		hovering = false;
		for (unsigned int i = 0; i < equipment_slots.size(); i++)
		{
			bool isAlreadySet = false;//A flag to determine whether the state of one of the slots has already been changed.
			//If mouse cursor is hovered over one of the equipment slots, set all the values ONLY once.
			if (equipment_slots[i].getBaseSprite().getGlobalBounds().contains((float)mouseX, (float)mouseY) && !hovering)
			{
				equipment_slots[i].setHovered(true);
				eqSlot = &equipment_slots[i];
				eq_index = i;
				isAlreadySet = true;
				hovering = true;
			}
			//If dragging an item, highlight all of the equipment slots in which the item can fit.
			if (dragging && equipment_slots[i].canEquip(item->getType()) && !isAlreadySet)
			{
				equipment_slots[i].setHovered(true);
				isAlreadySet = true;
			}
			//If one of the previous conditions has been fulfilled, then do not set hovered state to false.
			if(!isAlreadySet)
			{
				equipment_slots[i].setHovered(false);
			}
		}

		//Set hover effect for the weapon slots and toggle
		if (weapon_toggle.getSprite().getGlobalBounds().contains((float)mouseX, (float)mouseY))
		{
			weapon_toggle.setHovered(true);
		}
		else
		{
			weapon_toggle.setHovered(false);
		}
		weapon_toggle.adjustState();
		//CLEAR
		window.clear();
		//Draw main ui
		window.draw(spr_ui);
		//Draw feedback
		elapsed2 = clock2.getElapsedTime().asSeconds();
		if (elapsed2 >= 3 && drawFeedback)
		{
			drawFeedback = false;
		}
		if (drawFeedback)
		{
			window.draw(feedback);
		}
		//Draw Equipment Slots
		for (unsigned int i = 0; i < equipment_slots.size(); i++)
		{
			window.draw(equipment_slots[i].getBaseSprite());
			if (equipment_slots[i].getHovered())
			{
				window.draw(equipment_slots[i].getHoverSprite());
			}
		}
		//Draw the highlight sprites for the 2 weapon rows
		window.draw(spr_h1);
		window.draw(spr_h2);
		window.draw(spr_h3);
		//Draw the weapon toggle
		window.draw(weapon_toggle.getSprite());
		window.draw(weapon_toggle.getText());
		//Draw Inventory Tabs' icons
		for (unsigned int i = 0; i < inv_tab.icons.size(); i++)
		{
			if (inv_tab.icons[i].getGlobalBounds().contains((float)mouseX, (float)mouseY) && inv_tab.getState() != i)
			{
				inv_tab.setHovered(i);
			}
			else
			{
				inv_tab.adjustState();
			}
			window.draw(inv_tab.icons[i]);
		}
		//Draw Inventory Slots
		TabState tab_state = inv_tab.getState();
		int itemCounter = 0;//to count how many inventory slots have been drawn so far
		for (unsigned int i = 0; i < inv_tab.slots.size(); i++)
		{
			if (	tab_state == ALL	//All tab
				|| (tab_state == WEAPON && inv_tab.slots[i]->getType() >= 10) //Weapon tab
				|| (tab_state == APPAREL && inv_tab.slots[i]->getType() < 10))//Apparel tab
			{
				//Set hover effect for the inventory slots
				if (inv_tab.slots[i]->getSprite().getGlobalBounds().contains((float)mouseX, (float)mouseY) && dragging == false)
				{
					item = inv_tab.slots[i];
					item->setHovered(true);
				}
				else
				{
					inv_tab.slots[i]->setHovered(false);
				}
				//If the slot matches the tab's category, draw it; otherwise, skip it. 
				inv_tab.slots[i]->setInvSlot(Vector2f(1125, 273 + (float)(43 * itemCounter)));
				window.draw(inv_tab.slots[i]->getSprite());
				window.draw(inv_tab.slots[i]->getBaseSprite());
				window.draw(inv_tab.slots[i]->getName());
				if (tab_state != ALL)
				{
					window.draw(inv_tab.slots[i]->getRating());
				}
				window.draw(inv_tab.slots[i]->getValue());

				itemCounter++;
			}
		}
		//Draw Inventory Tab's rating sprite if needed
		if (tab_state == WEAPON || tab_state == APPAREL)
		{
			window.draw(inv_tab.getRatingSprite());
		}
		//Draw Inventory Space Available/Max
		number_of_items.setString(to_string(inv_tab.getItemCount()) + " / " + to_string(items_limit));//updates the Text
		window.draw(number_of_items);
		//Dragging sprites
		if (dragging)
		{
			loadTexture(texture_drag, item->getFilename());
			spr_drag.setPosition((float)mouseX, (float)mouseY);
			window.draw(spr_drag);
		}
		//DISPLAY
		window.display();
	}

	return 0;
}
