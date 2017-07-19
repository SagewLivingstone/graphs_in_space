#include <stdio.h>
#include <stdlib.h>

#include <SFML/Graphics.hpp>

int main()
{
	// Create Window, set no option for resizing
	sf::RenderWindow window(sf::VideoMode(800, 600), "Graphs in Space", sf::Style::Titlebar + sf::Style::Close);
	window.setVerticalSyncEnabled(true); // Use vsync because input delay doesn't really matter too much here
	window.setKeyRepeatEnabled(false); // Don't handle multiple held key presses

	// Make a test circle
	sf::CircleShape testcircle(100.f);
	testcircle.setFillColor(sf::Color::Green);

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			testcircle.setRadius(testcircle.getRadius() + 1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			testcircle.setRadius(testcircle.getRadius() - 1);
		}
		
		// Clear window before drawing
		window.clear();
		
		// Draw window
		window.draw(testcircle);

		// Render
		window.display();
	}

	return 0;
}