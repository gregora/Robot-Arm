#include "include/arm.h"
#include <stdio.h>
#include <iostream>
#include <random>

using namespace std;

void render(Arm a);

float randFloat(){
	std::random_device rd{};
	std::mt19937 engine{rd()};
	std::uniform_real_distribution<double> dist{0.0, 1.0};
	double ret = dist(engine);
	return ret;
}


int main(){

	vector<float> sizes = {1, 1, 1};
	Arm a(sizes, 5);

	render(a);

}

void render(Arm a){

	int WIDTH = 800;
	int HEIGHT = 600;

	bool RECORD = false;


	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Arm");
	sf::View view(sf::Vector2f(0, 0), sf::Vector2f(WIDTH / 2, HEIGHT / 2));
	view.zoom(0.03);
	window.setView(view);

	sf::Clock clock;
	float passed = 0;

	float tx = 1;
	float ty = 1;
	int frame = 0;
	while (window.isOpen())
	{
		frame ++;
		window.clear(sf::Color::Black);

		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);


		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			tx = worldPos.x;
			ty = -worldPos.y;
		}

		float angles[] = {0,0,0};
		a.getAngles(&angles[0]);

		float a1,a2,a3;

		float dx = (tx - a.getArmLocation().x);
		float dy = (ty - a.getArmLocation().y);

		float min = 100000;

		float drx,dry;

		for(int i = 0; i < 100; i++){
			float ar1 = (randFloat() - 0.5);
			float ar2 = (randFloat() - 0.5);
			float ar3 = (randFloat() - 0.5);

			drx = -ar1*sin(angles[2] + 3.14/2)
						-(ar1 + ar2)*sin(angles[2] + angles[1] + 3.14/2)
						-(ar1 + ar2 + ar3)*sin(angles[2] + angles[1] + angles[0] + 3.14/2);

			dry = ar1*cos(angles[2] + 3.14/2)
						+(ar1 + ar2)*cos(angles[2] + angles[1] + 3.14/2)
						+(ar1 + ar2 + ar3)*cos(angles[2] + angles[1] + angles[0] + 3.14/2);

			float val = abs(vector2angle(drx, dry) - vector2angle(dx, dy));

			if(val < min){
				min = val;
				a1 = ar1;
				a2 = ar2;
				a3 = ar3;
			}

		}

		//printf("D: %f %f\n", dx, dy);
		//printf("DR: %f %f\n", drx, dry);
		//printf("ERR: %f\n", sqrt(pow(drx - dx, 2) + pow(dry - dy, 2)));

		if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
			a1 = -5*(angles[0]);
			a2 = -5*(angles[1]);
			a3 = -5*(angles[2]);
		}

		a.applySpeeds({a1, a2, a3});

		sf::Time delta = clock.restart();
		float d = delta.asSeconds();
		if(RECORD){
			d = 1.0f/60;
		}
		a.physics(d, false);

		sf::RectangleShape dir;
		dir.setSize(sf::Vector2f(0.2, 0.02));
		dir.setOrigin(0, 0.01);
		dir.setPosition(a.getArmLocation().x, -a.getArmLocation().y);
		dir.setFillColor(sf::Color::Red);
		dir.setRotation(vector2angle(drx, dry) * 180/3.14);

		sf::CircleShape target(0.05);
		target.setOrigin(0.05, 0.05);
		target.setFillColor(sf::Color(255, 0, 0));

		target.setPosition(tx, -ty);

		window.draw(target);
		window.draw(a);
		//window.draw(dir);

		// end the current frame
		window.display();

		if(RECORD){
			window.capture().saveToFile("render/" + to_string(frame) + ".png");
		}

		passed+=d;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed){
				window.close();
				if(RECORD){
					system("cd render/ && ./render.sh");
				}
				return;
			}
		}

	}

}
