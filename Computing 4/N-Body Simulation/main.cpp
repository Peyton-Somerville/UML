/*
	Peyton Somerville
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include "NBody.hpp"

using std::cin;
using std::cout;
using std::stod;

int main(int argc, char* argv[])
{
	int numBodies;
	double universeRadius, scaledUniverseSize;
	int counter = 0;
	double totalTime = stod(argv[1]);
	double changeInTime = stod(argv[2]);
	double simTime = 0;

	cin >> numBodies;
	cin >> universeRadius;

	//calculating scale factor
	double tempR = universeRadius;
	while (tempR > 1000)
	{
		tempR /= 10;
		counter++;
	}
	double scaleFactor = pow(10.0, counter);

	if (tempR > 500)		//window has to be under 1000 x 1000
	{
		scaledUniverseSize = universeRadius / scaleFactor;
	}
	else
	{
		scaledUniverseSize = (universeRadius * 2) / scaleFactor;
	}

	Universe solarSystem(numBodies, scaledUniverseSize, scaleFactor);


	sf::RenderWindow window(sf::VideoMode(scaledUniverseSize, scaledUniverseSize), "N-Body Simulation");

	sf::Image backgroundPicture;
	if (!backgroundPicture.loadFromFile("space.jpg"))
	{
		cout << "Failed to open image file.\n";
		exit(1);
	}

	sf::Texture backgroundTexture;
	backgroundTexture.loadFromImage(backgroundPicture);

	sf::Sprite background;
	background.setTexture(backgroundTexture);

	sf::Font timeFont;
	timeFont.loadFromFile("arial.ttf");

	sf::Text timeText;
	timeText.setFont(timeFont);
	timeText.setCharacterSize(12);
	
	sf::Music music;
	if (!music.openFromFile("2001.wav"))
	{
		return -1;
	}
	music.play();

	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}

		window.clear();

		window.draw(background);

		timeText.setString("Time elapsed: " + std::to_string(simTime));
		window.draw(timeText);

		window.draw(solarSystem);
		//cout << solarSystem << "\n";
		solarSystem.step(changeInTime);

		window.display();

		simTime += changeInTime;

		if (simTime >= totalTime)
		{
			break;
		}
	}

	cout << "// Final Results:\n" << numBodies << "\n" << universeRadius << "\n" << solarSystem << "\n";

	return 0;
}