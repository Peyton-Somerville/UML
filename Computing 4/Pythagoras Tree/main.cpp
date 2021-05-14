/*
  Peyton Somerville
*/
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "PTree.hpp"

using std::cout;
using std::endl;
using std::stoi;
using std::stof;
using std::cin;

int main(int argc, char* argv[])
{
	float baseSquareSize = stof(argv[1]);
	int depth = stoi(argv[2]);

	if (baseSquareSize <= 0)
	{
		cout << "Please enter a base square size larger than 0.\n";
		return -1;
	}
	else if (depth < 0)
	{
		cout << "Please enter a depth of at least 0.\n";
		return -1;
	}

	int LWindowX = baseSquareSize * 6;
	int LWindowY = baseSquareSize * 4;

	bool type;
	cout << "Choose one of the following:\n";
	cout << "0: 45 45 90 Tree\n";
	cout << "1: 30 60 90 Tree\n>> ";
	cin >> type;

	sf::RenderWindow window;
	if (type == false)
		window.create(sf::VideoMode(LWindowX, LWindowY), "Pythagoras Tree");
	else
		window.create(sf::VideoMode(700, 500), "Pythagoras Tree");

	PTree object(baseSquareSize, depth, type);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(object);
		window.display();
	}

	return 0;
}
