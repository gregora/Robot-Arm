#include "include/arm.h"
#include <stdio.h>

using namespace std;

void render(Arm a, float time);

int main(){

	vector<float> sizes = {1, 1, 1};
	Arm a(sizes);

	render(a, 20);

}

void render(Arm a, float time){

	int WIDTH = 800;
	int HEIGHT = 600;


	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Arm");
	sf::View view(sf::Vector2f(0, 0), sf::Vector2f(WIDTH / 2, HEIGHT / 2));
	view.zoom(0.03);
	window.setView(view);

	sf::Clock clock;
	float passed = 0;
	while (window.isOpen())
	{
		window.clear(sf::Color::Black);

		sf::Time delta = clock.restart();
		a.physics(delta.asSeconds(), true);

		window.draw(a);

		// end the current frame
		window.display();


		passed+=delta.asSeconds();
		if(passed >= time){
			window.close();
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

	}

}
