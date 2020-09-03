#include "../Simple_and_fast/include/SFML/*"
#include "SimpleAudioManager.h"

int main() {
	sf::Window window(sf::VideoMode(320, 240), "AudioPlayback");
	sf::Clock clock;

	//Place init logic here
	SimpleAudioManager audio;
	audio.Load("someFile.wav");

	//start game loop
	while (window.isOpen()) {
		//run approx 60 times per second
		float elapsed = clock.getElapsedTime().asSeconds();
		if (elapsed < 1.0f / 60.0f) continue;
		clock.restart();
		sf::Event event;
		while (window.pollEvent(event)) {
			//handle window events
			if (event.type == sf::Event::Closed)
				window.close();

			//handle user input
			if (event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::Space)
				audio.Play("someFile.wav");
		}
		//update and draw logic
		audio.Update(elapsed);
	}
	//shutdown logic
	return 0;
}