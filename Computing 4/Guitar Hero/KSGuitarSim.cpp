/*
  Copyright 2020 Peyton Somerville
*/

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include <math.h>
#include <limits.h>

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <vector>

#include "RingBuffer.h"
#include "StringSound.h"

#define SAMPLES_PER_SEC 44100
#define SAMPLES_SIZE 44100 * 8  // SAMPLES_PER_SEC * duration (seconds)
#define KEYBOARD_SIZE 37


std::vector<sf::Int16> makeSamples(StringSound gs) {
	std::vector<sf::Int16> samples;

	gs.pluck();
	int i;
	for (i = 0; i < SAMPLES_SIZE; i++) {
		gs.tic();
		samples.push_back(gs.sample());
	}

	return samples;
}

int main() {
	try {	
		// weird size to fit note reference picture perfectly
		sf::RenderWindow window(sf::VideoMode(695, 211), "Guitar Simulator");
		sf::Event event;

		std::vector<sf::Int16> samples;
		std::vector<std::vector<sf::Int16>> vectSamples(KEYBOARD_SIZE);
		std::vector<sf::SoundBuffer> buffers(KEYBOARD_SIZE);
		std::vector<sf::Sound> sounds(KEYBOARD_SIZE);

		int i;
		double freq;
		for (i = 0; i < KEYBOARD_SIZE; i++) {
			freq = 440 * pow(2, (i - 24) / 12.0);
			StringSound gs = StringSound(freq);

			samples = makeSamples(gs);
			vectSamples[i] = samples;

			if (!buffers[i].loadFromSamples(&vectSamples[i][0], SAMPLES_SIZE, 1, SAMPLES_PER_SEC))
				throw std::runtime_error("sf::SoundBuffer: failed to load from samples.");

			sounds[i].setBuffer(buffers[i]);
		}

		std::string keyboard = "q2we4r5ty7u8i9op-[=zxdcfvgbnjmk,.;/' ";
		int j;

		// Note reference picture
		sf::Image noteRefImage;
		if (!noteRefImage.loadFromFile("GuitarSimKeyReference.PNG"))
			return EXIT_FAILURE;
		sf::Texture noteRefTexture;
		noteRefTexture.loadFromImage(noteRefImage);
		sf::Sprite noteRef;
		noteRef.setTexture(noteRefTexture);

		while (window.isOpen()) {
			while (window.pollEvent(event)) {
				switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::TextEntered:
					if (event.text.unicode < 128) {  // need to convert from unicode to ASCII
						char key = (char)(event.text.unicode);

						for (j = 0; j < KEYBOARD_SIZE; j++) {
							if (keyboard[j] == key) {
								std::cout << "Key Pressed: " << keyboard[j] << "\n";
								std::cout << "Attemping to play sound associated with key...\n\n";
								sounds[j].play();
								break;
							}
						}
					}
					
				default:
					break;
				}

				window.clear();
				window.draw(noteRef);
				window.display();
			}
		}
	}
	catch (std::invalid_argument& ia)
	{
		std::cerr << "Invalid Argument - " << ia.what() << "\n";
	}
	catch (std::runtime_error& re)
	{
		std::cerr << "Runtime Error - " << re.what() << "\n";
	}
	return 0;
}
