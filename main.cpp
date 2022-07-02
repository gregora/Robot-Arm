#include "include/arm.h"
#include <stdio.h>

using namespace std;

int main(){

	vector<float> sizes = {1, 1, 1};
	Arm a(sizes);

	int WIDTH = 800;
	int HEIGHT = 600;


	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Arm");
	sf::View view(sf::Vector2f(0, 0), sf::Vector2f(WIDTH / 2, HEIGHT / 2));
	view.zoom(0.03);
	window.setView(view);

	while (window.isOpen())
	{
	// check all the window's events that were triggered since the last iteration of the loop
	sf::Event event;
	while (window.pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
			window.close();
	}

	// clear the window with black color
	window.clear(sf::Color::Black);

	a.physics(1.0f / 60.0f, true);
	// draw everything here...
	// window.draw(...);
	window.draw(a);

	// end the current frame
	window.display();
}

}
