#pragma once
#include<SFML/Graphics.hpp>
#include <vector>
#include "SCelija.h"
#include "Pathf.h"
#include "Astar.h"
class Grid
{
private:
	sf::RenderWindow* window;
	std::vector<std::vector<SCelija>> celije;
	sf::Vector2u screensize;
	sf::Vector2i kraj;
	sf::Vector2i start;
	int celijaIRazmak = 32;
	unsigned short int modusOperandi=0;
	void updejtajF(int x,int y);
	void saljiUAstar();
	void clear_screen();
	Pathf pathf;
	Astar astar;
	sf::Font font;
	priority_queue<pair<sf::Vector2i, int>> pq;
	bool bstart, bend;
	sf::Text greskaText;
	
public:
	Grid(sf::RenderWindow* window);
	void mousePressed(sf::Vector2i position);
	void inputs();
	void draw();

};

