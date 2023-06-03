#include "Pathf.h"
#include <iostream>
#include <queue>

queue<pair<sf::Vector2i, int>> Pathf::susjedneCelije(vector<vector<SCelija>>& celije,sf::Vector2i orig)
{
	//Ako bude trebalo za nes drugo
	//this->celije = celije;

	/*trebo 8 okolo provjerit
[x-1,y-1][x,y-1][x+1,y-1]
[x-1,y  ][x,y  ][x+1,y  ]
[x-1,y+1][x,y+1][x+1,y+1]
*/
	queue<pair<sf::Vector2i, int>> q;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == 1 and j == 1)
			{
			}
			else if (orig.x==0 or orig.y==0 or orig.x>=round(1600/32)-1 or orig.y>=round(800/32)-1)
			{
				cout<<"greska";
			}
			else
			{	//Ovaj kod je KA TA STRO FA!!!
				int x= orig.x + (i - 1);
				int y= orig.y + (j - 1);
				sf::Vector2i susjed(x, y);
				celije[x][y].g = 14 * min(abs(x - start.x), abs(y- start.y)) + 10 * ((max(abs(x - start.x), abs(y - start.y))) - (min(abs(x - start.x), abs(y - start.y))));
				celije[x][y].h = 14 * min(abs(x- kraj.x), abs(y- kraj.y)) + 10 * ((max(abs(x - kraj.x), abs(y - kraj.y))) - (min(abs(x - kraj.x), abs(y - kraj.y))));
				celije[x][y].f = celije[x][y].g + celije[x][y].h;
				cout << "g:" << celije[x][y].g;
				cout << " h:" << celije[x][y].h;
				cout << " f:" << celije[x][y].f << endl;
				sf::Vector2i temp(x, y);
				pair<sf::Vector2i, int> susjedF(temp,celije[x][y].f);
				q.push(susjedF);	
			}

		}
	}


	return q;
}

//Pathf::Pathf(sf::RenderWindow* window)
//{
//	this->window = window;
//}

Pathf::Pathf()
{
}

void Pathf::set_celije(vector<vector<unsigned short int>> celije)
{


}

void Pathf::set_start(int x, int y)
{
	start.x = x;
	start.y = y;
}

void Pathf::set_kraj(int x, int y)
{
	kraj.x = x;
	kraj.y = y;
}

void Pathf::update()
{

}
