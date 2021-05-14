#ifndef PTREE_HPP
#define PTREE_HPP
#include <iostream>
#include <SFML/Graphics.hpp>

class PTree : public sf::Drawable
{
public:
	PTree(float baseSquareSize, int depth, bool type);

private:
	float L;
	int N;
	bool specialTree;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

void pTree(sf::RenderTarget& target, const int N,
	const sf::RectangleShape& base); //45 45 90 triangle

void pTree2(sf::RenderTarget& target, const int N,
	const sf::RectangleShape& base); //30 60 90 triangle

#endif
