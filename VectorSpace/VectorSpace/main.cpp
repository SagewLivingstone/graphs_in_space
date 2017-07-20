#include <stdio.h>
#include <stdlib.h>

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "Space.h"
#include "Helpers.h"

int main()
{
	PrintFullPath(".");

	Space* world = new Space();
	WindowData* windowdata = new WindowData();

	// Create Window, set no option for resizing
	sf::RenderWindow window(sf::VideoMode(windowdata->Width, windowdata->Height), windowdata->Title, sf::Style::Titlebar + sf::Style::Close);
	window.setVerticalSyncEnabled(true); // Use vsync because input delay doesn't really matter too much here
	window.setKeyRepeatEnabled(false); // Don't handle multiple held key presses

	// Give the world a window to draw to
	world->SetWindow(&window);

	// Make a test circle
	sf::CircleShape testcircle(100.f, 50);
	testcircle.setFillColor(sf::Color::Green);
	testcircle.setOutlineThickness(12);

	// Load a test image
	sf::Texture testimage;
	if (!testimage.loadFromFile("images\\testimage.jpg"))
		fprintf(stderr, "Could not load the test image");
	testimage.setSmooth(true);
	
	sf::Sprite s_testimage;
	s_testimage.setTexture(testimage);
	s_testimage.setColor(sf::Color(255, 0, 0));
	s_testimage.move(sf::Vector2f(50, 60));
	s_testimage.setOrigin(sf::Vector2f(50, 50));
	s_testimage.rotate(20);

	// Load fonts
	sf::Font hyperspace;
	if (!hyperspace.loadFromFile("fonts\\hyperspace.otf"))
		fprintf(stderr, "Could not load hyperspace font");

	// Mainloop while window is open
	while (window.isOpen())
	{
		// Get all events since last iteration
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Quit program : close window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Real-time keyboard input
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		//{
		//	testcircle.setRadius(testcircle.getRadius() + 1);
		//}

		world->HandleInput();

		// Clear window before drawing
		window.clear();
		
		// Draw window
		//window.draw(testcircle);
		//window.draw(s_testimage);
		world->Render();

		// Render
		window.display();
	}

	// Clean up before exit
	{
		delete world;
		delete windowdata;
	}

	return 0;
}