#pragma once
#include <SFML/Graphics.hpp>
#include "../Physics/CollisionDetection.h"

#include "../Physics/Physics.h"

#include <iostream>

sf::RenderWindow *window;

vec2 screenScaling;
vec2 windowSize;

sf::CircleShape shape(100.f);
sf::CircleShape circle(100.f);

sf::Clock deltaClock;
float deltaTime;
float fps;

vec2 mousePos;

bool mousePressed = false;

std::vector<PhysicsBody*> bodies;

bool create(int screenWidth, int screenHeight) {
	srand(time(NULL));

	sf::Vector2i screenSize = sf::Vector2i(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	screenScaling = vec2(screenSize.x / screenWidth, screenSize.y / screenHeight);

	window = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), "Yeet");
	window->setFramerateLimit(120);

	shape.setFillColor(sf::Color::Green);
	circle.setFillColor(sf::Color::Cyan);

	windowSize = vec2(screenWidth, screenHeight);

	for (unsigned int i = 0; i < 1; i++) {
		bodies.push_back(new PhysicsBody());
		vec2 pos = signRandom2D() * randomDouble(0,screenWidth);
		vec2 dim = signRandom2D() * randomDouble(30, 60);
		vec2 vel = random2D() * 80;
		float mass = 50 + rand() % 50;

		std::cout << i << " " << pos << " " << dim << " " << vel << " " << mass << "\n";

		//CreateCircle(bodies[i], pos, r, vel, mass, 1);
		CreateAABB(bodies[i], pos, dim, vel, mass, 1);
		bodies[i]->color = random4D() * 255; //vec4(255, 0, 255, 0);//random4D() * 255;
		bodies[i]->color.w = 255;
	}

	for (unsigned int i = 0; i < 20; i++) 
	{
		//std::cout << randomDouble(-1, 1) << "\n";
	}


	return true;

}

void run()
{

	//PhysicsBody* body = new PhysicsBody();
	//bool done = CreateCircle(body, vec2(300, 300), 60, vec2(60, 0), 100, 1);
	//PhysicsBody* mouseCircle = new PhysicsBody();
	//CreateCircle(mouseCircle, vec2(500, 500), 60, vec2(40,35), 100, 1);

	//std::cout << done << "\n";
	//std::cout << "X:" << body->circle.pos.x << " Y:" << body->circle.pos.y << "\n";

	

	while (window->isOpen()) {

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();

			if (event.type == sf::Event::MouseMoved)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
				mousePos.set(mousePosition.x, mousePosition.y);
			}
			
			if (event.type == sf::Event::MouseButtonPressed)
				mousePressed = true;
			if (event.type == sf::Event::MouseButtonReleased)
				mousePressed = false;
			
		}

		//window->setFramerateLimit(map(mousePos.x, 0, windowSize.x, 60, 200));

		if (mousePressed)
		{
			unsigned int size = bodies.size();
			for (int i = size-1; i < size-1 + 20; i++) {
				//delete bodies[i];
				//bodies[i] = new PhysicsBody();
				bodies.push_back(new PhysicsBody());
				vec2 pos = signRandom2D() * randomDouble(0, windowSize.x);
				float r = 20 + rand() % 20;
				vec2 vel = random2D() * 80;
				float mass = 50 + rand() % 50;

				//std::cout << i << " " << pos << " " << r << " " << vel << " " << mass << "\n";

				CreateCircle(bodies[i], pos, r, vel, mass, 1);
				bodies[i]->color = random4D() * 255;//vec4(255, 0, 255, 0);
			}
			mousePressed = false;
		}

		//updatePhysicsBody(body, deltaTime);
		//updatePhysicsBody(mouseCircle, deltaTime);

		//mouseCircle->circle.pos.x = constrain(mouseCircle->circle.pos.x, mouseCircle->circle.radius, windowSize.x - mouseCircle->circle.radius);
		//mouseCircle->circle.pos.y = constrain(mouseCircle->circle.pos.y, mouseCircle->circle.radius, windowSize.y - mouseCircle->circle.radius);
		/*
		if (body->circle.pos.x > windowSize.x - body->circle.radius || body->circle.pos.x < body->circle.radius) body->velocity.x *= -1;
		if (body->circle.pos.y > windowSize.y - body->circle.radius || body->circle.pos.y < body->circle.radius) body->velocity.y *= -1;

		if (mouseCircle->circle.pos.x > windowSize.x - mouseCircle->circle.radius || mouseCircle->circle.pos.x < mouseCircle->circle.radius) mouseCircle->velocity.x *= -1;
		if (mouseCircle->circle.pos.y > windowSize.y - mouseCircle->circle.radius || mouseCircle->circle.pos.y < mouseCircle->circle.radius) mouseCircle->velocity.y *= -1;

		constrainPhysicsObject(body, vec2(0, 0), windowSize);
		constrainPhysicsObject(mouseCircle, vec2(0, 0), windowSize);

		*/
		//mouseCircle->circle.pos = mousePos;
		//shape.setPosition(sf::Vector2f(body->circle.pos.x - body->circle.radius, body->circle.pos.y - body->circle.radius));
		//circle.setPosition(mouseCircle->circle.pos.x - body->circle.radius, mouseCircle->circle.pos.y - body->circle.radius);
		//std::cout << "Radius:" << body->circle.radius << "\n";

		//TODO: Update Other collision to work with new Manifold and return manifold
		//TODO: Implement AABB collision detection Algorythm
		//TODO: Implement Polygon collision detection and static resolution

		//TODO: Extend physics rendering system
		//TODO: Complete PhyscisBody constraining mechanism
		//TODO: Find bug in Collision Detection that causes Balls to collide with nothing

		double totalVel = 0;

		for(unsigned int i = 0; i < bodies.size(); i++){
			updatePhysicsBody(bodies[i], deltaTime);

			bounceInArea(bodies[i], { 0,0 }, windowSize);
			constrainPhysicsObject(bodies[i], { 0,0 }, windowSize);
			Manifold m;
			//bodies[i]->color = vec4(255, 0, 255, 0);
			m.a = *bodies[i];
			totalVel += bodies[i]->velocity.len();
			for(unsigned int j = 0; j < bodies.size(); j++){
				m.b = *bodies[j];
				if(i != j)
				{
					m = AABBvsAABB(m);
					//m = CirclevsCircle(m);
					if(m.collision)
					{
					ResolveCollision(m, bodies[i], bodies[j]);
					vec4 c = bodies[i]->color + bodies[j]->color;//random4D() * 255;
					c /= 2;
					//c.limit(255^4);
					c.w = 255;
					bodies[i]->color = c;//vec4(255, 255, 0, 0);
					bodies[j]->color = c;// vec4(255, 255, 0, 0);
					}
				}
			}
		}

		//std::cout << totalVel / bodies.size() << "\n";
		/*
		if (m.collision)
			circle.setFillColor(sf::Color::Blue);
		else
			circle.setFillColor(sf::Color::Cyan);*/

		//ResolveCollision(m,body,mouseCircle);

		//shape.setRadius(body->circle.radius);
		//circle.setRadius(mouseCircle->circle.radius);

		window->clear(sf::Color::White);
		
		for (unsigned int i = 0; i < bodies.size(); i++) {
			renderPhysicsObject(*window, bodies[i]);
		}
		//renderPhysicsObject(*window, mouseCircle, sf::Color::Blue);
		//renderPhysicsObject(*window, body, sf::Color::Green);
		
		//window->draw(circle);
		//window->draw(shape);
		window->display();

		deltaTime = deltaClock.restart().asSeconds();
		fps = 1 / deltaTime;
		//std::cout << fps << "\n";
	}
}

bool destroy() {
	window = NULL;
	delete window;
	return true;
}
