#include <SFML/Graphics.hpp>
#include "Grid.h"
#include <iostream>

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 950), "Hello, SFML world!");
	window.setFramerateLimit(60);
	Grid grid(&window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		grid.inputs();
		grid.draw();
		window.display();
	}

	return 0;
}