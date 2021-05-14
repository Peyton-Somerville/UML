#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "PTree.hpp"

using std::cout;
using std::endl;

PTree::PTree(float baseSquareSize, int depth, bool type)
{
	L = baseSquareSize;
	N = depth;
	specialTree = type;
}

void PTree::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape baseSquare;
	baseSquare.setSize(sf::Vector2f(L, L));
	baseSquare.setOrigin(baseSquare.getSize() / 2.f);
	if (specialTree == true)
	{
		baseSquare.setPosition((target.getSize().x / 2.f) - L,
			(target.getSize().y - L / 2.f) - L / 2);
	}
	else
	{
		baseSquare.setPosition(target.getSize().x / 2.f,
			target.getSize().y - L / 2.f);
	}
	baseSquare.setFillColor(sf::Color::Blue);

	if (specialTree == true)
		pTree2(target, N, baseSquare);

	else
		pTree(target, N, baseSquare);
}

void pTree(sf::RenderTarget& target, const int N,
	const sf::RectangleShape& base)
{
	const float scaleFactor = sqrt(2.f) / 2;

	if (N < 0)
		return;
	target.draw(base);

	const sf::Vector2f& size = base.getSize();
	const sf::Transform& trans = base.getTransform();

	sf::Color col = base.getFillColor();
	if (col.b > 150)
		col.b -= 50;
	else if (col.r < 150)
		col.r += 50;
	else if (col.g < 205)
		col.g += 50;

	sf::RectangleShape left = base;
	left.setSize(size * scaleFactor);
	left.setOrigin(0, left.getSize().y);
	left.setPosition(trans.transformPoint(0, 0));
	left.rotate(-45);
	left.setFillColor(col);
	pTree(target, N - 1, left);

	sf::RectangleShape right = base;
	right.setSize(size * scaleFactor);
	right.setOrigin(right.getSize());
	right.setPosition(trans.transformPoint(size.x, 0));
	right.rotate(45);
	right.setFillColor(col);
	pTree(target, N - 1, right);
}

void pTree2(sf::RenderTarget& target, const int N,
	const sf::RectangleShape& base)
{
	const float scaleFactor1 = 1.f / 2;
	const float scaleFactor2 = (1.f / 2) * sqrt(3.f);

	if (N < 0)
		return;
	target.draw(base);

	const sf::Vector2f& size = base.getSize();
	const sf::Transform& trans = base.getTransform();

	sf::Color col = base.getFillColor();
	if (col.b > 150)
		col.b -= 50;
	else if (col.r < 150)
		col.r += 50;
	else if (col.g < 205)
		col.g += 50;

	sf::RectangleShape left = base;
	left.setSize(size * scaleFactor1);
	left.setOrigin(0, left.getSize().y);
	left.setPosition(trans.transformPoint(0, 0));
	left.rotate(-60);
	left.setFillColor(col);
	pTree2(target, N - 1, left);

	sf::RectangleShape right = base;
	right.setSize(size * scaleFactor2);
	right.setOrigin(right.getSize());
	right.setPosition(trans.transformPoint(size.x, 0));
	right.rotate(30);
	right.setFillColor(col);
	pTree2(target, N - 1, right);
}