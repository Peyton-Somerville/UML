/*
  Copyright 2020 Peyton Somerville
*/

#include <SFML/System.hpp>
#include "ED.hpp"

int main(int argc, char* argv[]) {
	sf::Clock clock;
	sf::Time t;

	string input1, input2;
	std::cin >> input1 >> input2;

	ED test(input1, input2);

	std::cout <<"Edit distance = " << test.OptDistance() << "\n";
	//test.printMatrix();
	std::cout << test.Alignment();

	t = clock.getElapsedTime();
	std::cout << "Execution time is " << t.asSeconds() << " seconds.\n";

	system("pause");
	return 0;
}
