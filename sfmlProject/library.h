#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

namespace mySpace
{
	inline void loadTexture(Texture &t, string filename)
	{
		if (!t.loadFromFile(filename))
		{
			cout << filename << " not found" << endl;
			exit(EXIT_FAILURE);
		}
	}
}
