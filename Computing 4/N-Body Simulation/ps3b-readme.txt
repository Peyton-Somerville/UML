/**********************************************************************
 *  N-Body Simulation ps3b-readme.txt template
 **********************************************************************/

Name: Peyton Somerville
Hours to complete assignment: 7

/**********************************************************************
 *  Briefly discuss the assignment itself and what you accomplished.
 **********************************************************************/
This program simulates motion of bodies over a given time interval. Given
a body's starting position, velocity, and mass, this program calculates the
forces acting on it (acceleration -> new velocity -> new position) to find its
next position, using the leapfrog finite difference apporximation shemce, which
uses Newton's law of universal gravitation, the principle of superposition, 
and Newton's second law of motion. 

  /**********************************************************************
 *  Discuss one or more key algorithms, data structures, or 
 *  OO designs that were central to the assignment.
 **********************************************************************/
The vector of unique_ptrs of CelestialBody objects was central to this 
assignment, because it made navigating through every body object very easy,
with just using vector_name.at(i) in a for loop with i as the iterator.
And since a vector can alway grow in size, it can handle any amount of bodies.




/**********************************************************************
 *  Briefly explain the workings of the features you implemented.
 *  Describe if and how do you used the smart pointers 
 *  Include code excerpts.
 **********************************************************************/
To find the total force acting on a body, you need the sum of the forces
acting on it. This double for loop goes through each combination of two 
bodies (excluding when j == k, so its not checking Earth- Earth or Sun- Sun)
adding to a running total of the forces, which are then used to find the
body's acceleration, the velocity, and then its new position.
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


I use a smart point in the Universe constructor to setup the vector:
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


/**********************************************************************
 *  List whatever help (if any) you received from the instructor,
 *  classmates, or anyone else.
 **********************************************************************/
I worked alone.

/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
I did not encounter any serious problems.

/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
-Added time elapsed display
-Added music
-Made a universe in milkyway.txt that includes all planets in our own Milky Way Galaxy from Mercury to Pluto.