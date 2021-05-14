//Peyton Somerville
//PS1b

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "FibLFSR.hpp"

using namespace std;

void transform(sf::Image& pic, FibLFSR* l);

int main(int argc, char* argv[])
{
	string inputFileName(argv[1]);
	string outputFileName(argv[2]);
	string seed(argv[3]);

	FibLFSR test(seed);

	sf::Image inputPicture1;
	if (!inputPicture1.loadFromFile(inputFileName))
		return EXIT_FAILURE;

	transform(inputPicture1, &test);

	inputPicture1.saveToFile(outputFileName); //copy from input file to output

	sf::Image inputPicture2;
	if (!inputPicture2.loadFromFile(inputFileName)) //load unchanged input file
		return EXIT_FAILURE;
	sf::Image outputPicture;
	if (!outputPicture.loadFromFile(outputFileName))
		return EXIT_FAILURE;

	sf::Vector2u size = inputPicture2.getSize();

	sf::RenderWindow window1(sf::VideoMode(size.x, size.y), "InputImage");
	sf::RenderWindow window2(sf::VideoMode(size.x, size.y), "OutputImage");

	sf::Texture inputTexture, outputTexture;
	inputTexture.loadFromImage(inputPicture2);
	outputTexture.loadFromImage(outputPicture);

	sf::Sprite inputSprite, outputSprite;
	inputSprite.setTexture(inputTexture);
	outputSprite.setTexture(outputTexture);

	while (window1.isOpen() && window2.isOpen())
	{
		sf::Event event;
		while (window1.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window1.close();
		}
		while (window2.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window2.close();
		}
		window1.clear();
		window1.draw(inputSprite);
		window1.display();
		window2.clear();
		window2.draw(outputSprite);
		window2.display();
	}

	return 0;
}

void transform(sf::Image& pic, FibLFSR* l)
{
	unsigned int i, j;
	sf::Vector2u size = pic.getSize();
	sf::Color col;
	for (i = 0; i < size.x; i++)
	{
		for (j = 0; j < size.y; j++)
		{
			col = pic.getPixel(i, j);

			col.r = col.r ^ l->generate(8);
			col.g = col.g ^ l->generate(8);
			col.b = col.b ^ l->generate(8);

			pic.setPixel(i, j, col);
		}
	}
}
