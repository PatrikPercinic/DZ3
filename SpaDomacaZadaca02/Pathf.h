#pragma once
#include<SFML/Graphics.hpp>
#include<queue>
#include<cmath>
#include "SCelija.h"
using namespace std;




class Pathf
{
private:
	sf::RenderWindow* window;
	std::vector<std::vector<SCelija>> celije;
	sf::Vector2i start;
	sf::Vector2i current;
	sf::Vector2i kraj;

public:
	queue<pair<sf::Vector2i, int>> susjedneCelije(vector<vector<SCelija>>& celije,sf::Vector2i orig);
	//Pathf(sf::RenderWindow* window);
	Pathf();
	void set_celije(vector<vector<unsigned short int>> celije);
	void set_start(int x,int y);
	void set_kraj(int x,int y);
	void update();



};

