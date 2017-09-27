
#include "toggle.h"

Toggle::Toggle()
{
	isActive = false;
	isHovered = false;
	loadTexture(texture_toggle, "ESO_resources/toggle_inactive.png");
	spr_toggle.setTexture(texture_toggle);
	spr_toggle.setPosition(138, 510);
	toggle_number.setString("1");//Can only be either '1' or '2'
	toggle_number.setCharacterSize(11);
	toggle_number.setPosition(spr_toggle.getPosition().x + 17, spr_toggle.getPosition().y + 18);
}

Toggle::Toggle(string filename, Vector2f position, Font &font, int size)
{
	/*	
		For the sake of simplicity, it will stay active even when there are no weapons slotted, 
		which is different from how it works in the actual game.
	*/
	isActive = true;//will be set to true for now to demonstrate toggle's functionality
	isHovered = false;
	loadTexture(texture_toggle, filename);
	spr_toggle.setTexture(texture_toggle);
	spr_toggle.setPosition(position);
	toggle_number = Text("1", font, 11);//Can only be either '1' or '2'
	toggle_number.setPosition(spr_toggle.getPosition().x + 18, spr_toggle.getPosition().y + 18);
}

void Toggle::adjustState()
{
	if (isActive)//For now only this part will be executed
	{
		if (isHovered)
		{
			loadTexture(texture_toggle, "ESO_resources/toggle_hover.png");
		}
		else
		{
			loadTexture(texture_toggle, "ESO_resources/toggle_active.png");
		}
	}
	else
	{
		loadTexture(texture_toggle, "ESO_resources/toggle_inactive.png");
	}
}

void Toggle::switchNumber()
{
	if (toggle_number.getString() == "1")
	{
		toggle_number.setString("2");
	}
	else
	{
		toggle_number.setString("1");
	}
}

Sprite Toggle::getSprite()
{
	return spr_toggle;
}

Text Toggle::getText()
{
	return toggle_number;
}

bool Toggle::getActive()
{
	return isActive;
}
bool Toggle::getHovered()
{
	return isHovered;
}
void Toggle::setActive(bool flag)
{
	isActive = flag;
}
void Toggle::setHovered(bool flag)
{
	isHovered = flag;
}
