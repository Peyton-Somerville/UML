#ifndef NBODY_HPP
#define NBODY_HPP
#include <iostream>
#include <SFML/Graphics.hpp>

using std::string;
using std::vector;
using std::unique_ptr;
using std::istream;
using std::ostream;

class CelestialBody : public sf::Drawable
{
public:
	CelestialBody();		//default constructor
	CelestialBody(double r, double s);		//value constructor when called from Universe class
	CelestialBody(double r, double x, double y, double xV, double yV, double m, double s, string file);		//default value constuctor

	double getXPos() const;
	double getYPos() const;
	double getMass() const;
	double getXVel() const;
	double getYVel() const;

	void setXPos(double newPos);
	void setYPos(double newPos);
	void setXVel(double newVel);
	void setYVel(double newVel);
	void setSpritePos(double newXPos, double newYPos);

	double findXForce(CelestialBody &cb1, CelestialBody &cb2);
	double findYForce(CelestialBody &cb1, CelestialBody &cb2);
	void setForces(double xForce, double yForce);
	double getXFor() const;
	double getYFor() const;


	friend istream &operator >> (istream &input, CelestialBody& cb);
	friend ostream &operator << (ostream &output, const CelestialBody& cb);

private:
	double xPos, yPos;
	double xVel, yVel;
	double xFor, yFor;
	double xAcc, yAcc;
	double mass;

	double radius;
	double scale;

	string fileName;
	sf::Texture texture;
	sf::Sprite sprite;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class Universe : public sf::Drawable
{
public:
	Universe(int N, double r, double s);

	void step(double seconds);

	friend ostream &operator << (ostream &output, const Universe& u);

private:
	vector<unique_ptr<CelestialBody>> bodies;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif