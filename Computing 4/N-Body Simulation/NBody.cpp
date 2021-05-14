#include "NBody.hpp"
#include <math.h>

using std::cout;
using std::endl;
using std::cin;
using std::move;

/**********************Celestial Body Class********************************/
CelestialBody::CelestialBody()
{
	return;
}

CelestialBody::CelestialBody(double r, double s)
{
	radius = r / 2;
	scale = s;
}

CelestialBody::CelestialBody(double r, double x, double y, double xV, double yV, double m, double s, string file)
{
	scale = s;
	r /= scale;
	xPos = x / scale;
	yPos = y / scale;
	xVel = xV;
	yVel = yV;
	mass = m;

	if (!texture.loadFromFile(file))
	{
		cout << "Error loading " << file << endl;
		exit(1);
	}
	sprite.setTexture(texture);

	sprite.setPosition(r + xPos, r + yPos);
}

double CelestialBody::getXPos() const
{
	return xPos;
}
double CelestialBody::getYPos() const
{
	return yPos;
}
double CelestialBody::getMass() const
{
	return mass;
}
double CelestialBody::getXVel() const
{
	return xVel;
}
double CelestialBody::getYVel() const
{
	return yVel;
}

void CelestialBody::setXPos(double newPos)
{
	xPos = newPos;
}
void CelestialBody::setYPos(double newPos)
{
	yPos = newPos;
}
void CelestialBody::setXVel(double newVel)
{
	xVel = newVel;
}
void CelestialBody::setYVel(double newVel)
{
	yVel = newVel;
}
void CelestialBody::setSpritePos(double newXPos, double newYPos)
{
	sprite.setPosition(radius + newXPos / scale, radius - newYPos / scale);
}

double CelestialBody::findXForce(CelestialBody &cb1, CelestialBody &cb2)
{
	double x = cb2.xPos - cb1.xPos;	
	double y = cb2.yPos - cb1.yPos;
	double r = sqrt((x * x) + (y * y));

	const double G = 0.0000000000667;

	double F = (G * cb1.mass * cb2.mass) / (r * r);
	double Fx = F * (x / r);

	return Fx;
}
double CelestialBody::findYForce(CelestialBody &cb1, CelestialBody &cb2)
{
	double x = cb2.xPos - cb1.xPos;
	double y = cb2.yPos - cb1.yPos;
	double r = sqrt((x * x) + (y * y));

	const double G = 0.0000000000667;

	double F = (G * cb1.mass * cb2.mass) / (r * r);
	double Fy = F * (y / r);

	return Fy;
}
void CelestialBody::setForces(double xForce, double yForce)
{
	xFor = xForce;
	yFor = yForce;
}
double CelestialBody::getXFor() const
{
	return xFor;
}
double CelestialBody::getYFor() const
{
	return yFor;
}

istream &operator >> (istream &input, CelestialBody& cb)
{
	input >> cb.xPos >> cb.yPos;
	input >> cb.xVel >> cb.yVel;
	input >> cb.mass;
	input >> cb.fileName;

	if (!cb.texture.loadFromFile(cb.fileName))
	{
		cout << "Error loading " << cb.fileName << endl;
		exit(1);
	}
	cb.sprite.setTexture(cb.texture);

	cb.sprite.setPosition(cb.radius + cb.xPos / cb.scale, cb.radius - cb.yPos / cb.scale);

	return input;
}

ostream &operator << (ostream &output, const CelestialBody& cb)
{
	output.precision(4);
	output << std::scientific;
	output << cb.xPos << "  " << cb.yPos << "  ";
	output << cb.xVel << "  " << cb.yVel << "  ";
	output << cb.mass << "  ";
	output << cb.fileName;

	return output;
}

void CelestialBody::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite);
}

/**************************Universe Class************************************/

Universe::Universe(int N, double r, double s)
{
	int i;
	for (i = 0; i < N; i++)
	{
		unique_ptr<CelestialBody> temp(new CelestialBody(r, s));
		cin >> *temp;
		bodies.push_back(move(temp));
		temp.reset();
	}
}

void Universe::step(double seconds)
{
	int i, j, k;
	double forceX, forceY;

	for (j = 0; j < bodies.size(); j++)
	{
		forceX = 0;
		forceY = 0;

		for (k = 0; k < bodies.size(); k++)
		{
			if (j != k)
			{
				forceX += (*bodies.at(j)).findXForce(*bodies.at(j), *bodies.at(k));
				forceY += (*bodies.at(j)).findYForce(*bodies.at(j), *bodies.at(k));
			}
		}

		(*bodies.at(j)).setForces(forceX, forceY);
	}

	for (i = 0; i < bodies.size(); i++)
	{
		double Ax = (*bodies.at(i)).getXFor() / (*bodies.at(i)).getMass();
		double Ay = (*bodies.at(i)).getYFor() / (*bodies.at(i)).getMass();

		double Vx = (*bodies.at(i)).getXVel() + (seconds * Ax);
		double Vy = (*bodies.at(i)).getYVel() + (seconds * Ay);
		(*bodies.at(i)).setXVel(Vx);
		(*bodies.at(i)).setYVel(Vy);
	
		double Px = (*bodies.at(i)).getXPos() + (seconds * Vx);
		double Py = (*bodies.at(i)).getYPos() + (seconds * Vy);
		(*bodies.at(i)).setXPos(Px);
		(*bodies.at(i)).setYPos(Py);

		(*bodies.at(i)).setSpritePos(Px, Py);
	}
}

ostream &operator << (ostream &output, const Universe& u)
{
	int i;
	for (i = 0; i < u.bodies.size(); i++)
	{
		output << *(u.bodies).at(i) << endl;
	}

	return output;
}

void Universe::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	int i;
	for(i = 0; i < bodies.size(); i++)
	{
		target.draw(*bodies.at(i));
	}
}