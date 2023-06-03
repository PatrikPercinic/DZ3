#include "Grid.h"
#include <iostream>
#include <list>
#include <unordered_set>
#include "Astar.h"
using namespace std;
//Ovaj kod je katastrofa!


bool cmp(int x, int y) {
	return x > y;
}

void Grid::updejtajF(int x, int y)
{
	queue<pair<sf::Vector2i, int>> q;
	vector<sf::Vector2i> v;
	pair<sf::Vector2i, int> min;
	sf::Vector2i curr(x, y);
	pathf.susjedneCelije(celije, curr);

}

void Grid::saljiUAstar()
{

	int grid[50][25];
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			if (celije[i][j].vrsta == 1)
			{
				grid[i][j] = 0;
			}
			else
			{
				grid[i][j] = 1;
			}


		}
	}
	Pair src = make_pair(start.x, start.y);
	Pair dest = make_pair(kraj.x, kraj.y);
	stack<Pair> put;
	put = astar.aStarSearch(grid, src, dest);
	put.pop();
	while (put.size() > 1) {
		pair<int, int> p = put.top();
		put.pop();
		celije[p.first][p.second].vrsta = 4;
		//printf("-> (%d,%d) ", p.first, p.second);
	}
}

void Grid::clear_screen()
{
	bstart = false;
	bend = false;
	for (int i = 0; i < celije.size(); i++)
	{
		for (int j = 0; j < celije[i].size(); j++)
		{
			celije[i][j].vrsta = 0;
			celije[i][j].f = 999;
		}
	}

}

Grid::Grid(sf::RenderWindow* window)
{
	bend = false;
	bstart = false;
	this->window = window;
	screensize = window->getSize();

	celije.resize(screensize.x / celijaIRazmak);
	for (int i = 0; i < screensize.x / celijaIRazmak; i++)
	{
		celije[i].resize((screensize.y - 150) / celijaIRazmak);
		for (int j = 0; j < (screensize.y - 150) / celijaIRazmak; j++) {
			celije[i][j].vrsta = 0;
			celije[i][j].f = 999;
		}
	}
	if (!font.loadFromFile("ARIALN.TTF"))
	{
		throw _exception();
	}

	////crveno-zid
	//celije[5][5].vrsta = 1;
	////plavo-start
	//celije[6][5].vrsta = 2;
	////zeleno-kraj
	//celije[7][5].vrsta = 3;

}

void Grid::mousePressed(sf::Vector2i position)
{

	if ((position.x >= 0 and position.x <= screensize.x) and (position.y >= 0 and position.y <= screensize.y - 150))
	{
		int x = round(position.x / celijaIRazmak);
		int y = round(position.y / celijaIRazmak);

		if ((y >= screensize.y - 150) / celijaIRazmak)
		{
			y--;
		}
		if (x >= screensize.x / celijaIRazmak)
		{
			x--;
		}

		if (modusOperandi == 0)
		{
			celije[x][y].vrsta = 1;

		}
		else if (modusOperandi == 1)
		{
			celije[x][y].vrsta = 2;
			if ((start.x != 0 or start.y != 0) and (start.x != x or start.y != y))
			{
				celije[start.x][start.y].vrsta = 0;
			}
			pathf.set_start(x, y);
			start.x = x;
			start.y = y;
		}
		else if (modusOperandi == 2)
		{
			celije[x][y].vrsta = 3;
			if ((kraj.x != 0 or kraj.y != 0) and (kraj.x != x or kraj.y != y))
			{
				celije[kraj.x][kraj.y].vrsta = 0;

			}
			pathf.set_kraj(x, y);
			kraj.x = x;
			kraj.y = y;

		}
		else if (modusOperandi == 3)
		{
			//celije[x][y].vrsta = 5;

			if (bstart and bend)
			{
				updejtajF(x, y);
				greskaText.setString("");
			}
			else
			{
				sf::Text greskaText;
				greskaText.setFont(font);
				greskaText.setCharacterSize(30);
				greskaText.setFillColor(sf::Color::Red);
				greskaText.setPosition(1000, 900);
				if (bstart)
				{
					greskaText.setString("Greska: Pocetak nije postavljen");

				}
				else
				{
					greskaText.setString("Greska: Kraj nije postavljen!");

				}
			}


		}

	}

}
void Grid::inputs()
{

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mousePressed(sf::Mouse::getPosition(*window));
	}
	//Tipkovnica
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		modusOperandi = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		modusOperandi = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		modusOperandi = 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		modusOperandi = 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		clear_screen();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (bstart and bend)
		{
			saljiUAstar();
			greskaText.setString("");
		}
		else
		{
			greskaText.setFont(font);
			greskaText.setCharacterSize(30);
			greskaText.setFillColor(sf::Color::Red);
			greskaText.setPosition(1000, 900);
			if (bstart)
			{
				greskaText.setString("Greska: Pocetak nije postavljen");

			}
			else
			{
				greskaText.setString("Greska: Kraj nije postavljen!");

			}

		}
	}
}

void Grid::draw()
{
	vector<sf::Text> text;
	sf::Text temptext;
	temptext.setFont(font);
	temptext.setCharacterSize(30);
	temptext.setFillColor(sf::Color::White);
	temptext.setPosition(10, 800);
	temptext.setString("Q za zidove, W za start, E za cilj, R za reset,\nM za manual mode, space za izracunat");
	text.push_back(temptext);
	sf::Text stanjeText;
	stanjeText.setFont(font);
	stanjeText.setCharacterSize(30);
	stanjeText.setFillColor(sf::Color::White);
	stanjeText.setPosition(1000, 800);
	if (modusOperandi == 0)
	{
		stanjeText.setString("Selected tool: Zid");

	}
	else if (modusOperandi == 1)
	{
		stanjeText.setString("Selected tool: Start");
	}
	else if (modusOperandi == 2)
	{
		stanjeText.setString("Selected tool: Cilj");

	}
	else if (modusOperandi == 3)
	{
		stanjeText.setString("Selected tool: Manual");

	}

	vector<sf::RectangleShape> ab;
	for (int i = 0; i < screensize.x / celijaIRazmak; i++)
	{
		for (int j = 0; j < (screensize.y - 150) / celijaIRazmak; j++)
		{
			sf::Text temptext;
			temptext.setFont(font);
			temptext.setCharacterSize(20);
			temptext.setFillColor(sf::Color::Black);
			sf::Vector2f size(30, 30);
			sf::RectangleShape celija(size);
			sf::Vector2f pos(celijaIRazmak * i, celijaIRazmak * j);
			celija.setPosition(pos);
			if (celije[i][j].vrsta == 1)
			{
				celija.setFillColor(sf::Color::Red);
			}
		else if (celije[i][j].vrsta == 0 and celije[i][j].f == 999)
			{
				celija.setFillColor(sf::Color::White);
			}
			else if (celije[i][j].vrsta == 2)
			{
				bstart = true;
				celija.setFillColor(sf::Color::Blue);
			}
			else if (celije[i][j].vrsta == 3)
			{
				bend = true;

				celija.setFillColor(sf::Color::Green);
			}
			else if (celije[i][j].vrsta == 4)
			{
				celija.setFillColor(sf::Color::Yellow);
				//temptext.setPosition(pos.x, pos.y);
				//temptext.setString(to_string(celije[i][j].f));
			}
			else if (celije[i][j].f != 999)
			{
				celija.setFillColor(sf::Color::Yellow);
				temptext.setPosition(pos.x, pos.y);
				temptext.setString(to_string(celije[i][j].f));
			}
			else
			{
				celija.setFillColor(sf::Color::White);
			}
			text.push_back(temptext);
			ab.push_back(celija);
		}
	}

	for (auto it = ab.begin(); it != ab.end(); ++it)
	{
		window->draw(*it);
	}
	for (auto it = text.begin(); it != text.end(); ++it)
	{
		window->draw(*it);
	}
	window->draw(stanjeText);
	window->draw(greskaText);

}
