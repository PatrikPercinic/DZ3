#pragma once
#include<SFML/Graphics.hpp>
struct SCelija {
	//sf::Vector2i pos;
	unsigned short int vrsta;
	//udaljenost od starta
	int g = INFINITY;
	//udaljenost od kraja
	int h = INFINITY;
	//zbroj
	int f = INFINITY;
};