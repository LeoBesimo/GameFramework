#pragma once
#include <SFML/Graphics.hpp>

#include "Components.h"
//#include "Physics.h"
//#include "CollisionDetection.h"
//#include "BodyCreator.h"
//#include "CollisionResolution.h"
#include "Engine.h"

#include "RenderPhysics.h"

#include <iostream>

sf::RenderWindow* window;

lge::vec2 screenScaling;
lge::vec2 windowSize;

sf::CircleShape shape(100.f);
sf::CircleShape circle(100.f);

sf::Clock deltaClock;
float deltaTime;
float fps;

lge::vec2 mousePos;

bool mousePressed = false;
bool keyPressed = false;

lge::Engine engine;
std::vector<lge::uuid> objects;
lge::uuid walls[4];

//std::vector<lge::PhysicsBody*> bodies;
//std::vector<lge::PhysicsBody*> walls;

//lge::PhysicsBody* player = new lge::PhysicsBody();

bool create(int screenWidth, int screenHeight) {
	srand(time(NULL));

	sf::Vector2i screenSize = sf::Vector2i(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	screenScaling = lge::vec2(screenSize.x / screenWidth, screenSize.y / screenHeight);

	window = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), "Yeet");
	window->setFramerateLimit(60);

	shape.setFillColor(sf::Color::Green);
	circle.setFillColor(sf::Color::Cyan);

	windowSize = lge::vec2(screenWidth, screenHeight);


	lge::Material wall = lge::Material(0, 1, 1500, 1000);
	walls[0] = engine.AddObjectAABB(lge::vec2(0, 0), { (double)screenWidth,10 }, { 0,0 }, wall);
	walls[1] = engine.AddObjectAABB(lge::vec2(0, screenHeight - 10), { (double)screenWidth,10 }, { 0,0 }, wall);
	walls[2] = engine.AddObjectAABB(lge::vec2(0, 0), lge::vec2(10, screenHeight), { 0,0 }, wall);
	walls[3] = engine.AddObjectAABB(lge::vec2(screenWidth - 10, 0), { 10, (double)screenHeight }, { 0,0 }, wall);

	for (auto i : walls)
	{
		engine.GetPhysicsBody(i)->color = lge::vec4(255, 0, 255, 255);
	}

	for (unsigned int i = 0; i < 4; i++) 
	{
		engine.GetPhysicsBody(walls[i])->movable = false;
	}

	for (int i = 0; i < 20; i++)
	{
		lge::vec2 pos = lge::signRandom2D() * lge::randomDouble(0, screenWidth);
		lge::vec2 vel = lge::random2D() * 80;
		lge::vec2 dim = lge::vec2(lge::randomDouble(25, 40), lge::randomDouble(25, 40));
		lge::uuid id = engine.AddObjectAABB(pos, dim, vel, lge::PERFECT);
		engine.GetPhysicsBody(id)->color = lge::vec4(255, 0, 255, 255);
		objects.push_back(id);
	}

	for (int i = 0; i < 30; i++)
	{
		lge::vec2 pos = lge::signRandom2D() * lge::randomDouble(0, screenWidth); //lge::vec2(200, 100); //
		lge::vec2 vel = lge::random2D() * 80; //lge::vec2(-60, 0);//
		//lge::vec2 dim = lge::vec2(lge::randomDouble(25, 40), lge::randomDouble(25, 40));
		double r = lge::randomDouble(5, 10);
		lge::uuid id = engine.AddObjectCircle(pos, r, vel, lge::PERFECT);
		engine.GetPhysicsBody(id)->color = lge::vec4(255, 255, 0, 255);
		objects.push_back(id);
	}

	/*lge::CreateAABB(player, lge::vec2(200, 100), lge::vec2(40, 80), lge::vec2(), lge::WOOD);
	player->material.dynamicFriction = 100.2;
	player->material.staticFriction = 100.4;
	player->color = lge::vec4(255, 255, 0, 255);

	for (unsigned int i = 0; i < 10; i++) {
		bodies.push_back(new lge::PhysicsBody());

		lge::vec2 pos = lge::signRandom2D() * lge::randomDouble(0, screenWidth);

		lge::vec2 vel = lge::random2D() * 80;
		float mass = 50 + rand() % 50;

		if (true) {


			lge::vec2 dim = lge::vec2(lge::randomDouble(25, 40), lge::randomDouble(25, 40));

			//std::cout << i << " " << pos << " " << dim << " " << vel << " " << mass << "\n";

			//CreateCircle(bodies[i], pos, r, vel, mass, 1);
			lge::CreateAABB(bodies[i], pos, dim, vel, lge::SUPERBALL);
		}
		else
		{
			float r = lge::randomDouble(20, 40);
			lge::CreateCircle(bodies[i], pos, r, vel, lge::SUPERBALL);
		}
		bodies[i]->color = lge::random4D() * 255; //vec4(255, 0, 255, 0);//random4D() * 255;
		bodies[i]->color.w = 255;
	}


	//bodies.push_back(new PhysicsBody());
	//bodies.push_back(new PhysicsBody());

	//CreateAABB(bodies[0], vec2(200, 200), { 40,20 }, { 60,0 }, 100, 1);
	//CreateCircle(bodies[1], vec2(460, 440), 15, { 0,-60 }, 80, 1);

	for (unsigned int i = 0; i < 4; i++) {
		walls.push_back(new lge::PhysicsBody());
		walls[i]->color = lge::vec4(255, 0, 0, 255);
		walls[i]->movable = false;
	}

	lge::Material wall = lge::Material(0, 1, 1500, 1000);

	lge::CreateAABB(walls[0], lge::vec2(0, 0), { (double)screenWidth,10 }, { 0,0 }, wall);;
	lge::CreateAABB(walls[1], lge::vec2(0, screenHeight - 10), { (double)screenWidth,10 }, { 0,0 }, wall);
	lge::CreateAABB(walls[2], lge::vec2(0, 0), lge::vec2(10, screenHeight), { 0,0 }, wall);
	lge::CreateAABB(walls[3], lge::vec2(screenWidth - 10, 0), { 10, (double)screenHeight }, { 0,0 }, wall);

	for (int i = 0; i < walls.size(); i++)
	{
		//walls[i]->material.dynamicFriction = 0.6;
		//walls[i]->material.staticFriction = 0.9;
	}

	//bodies.push_back(new PhysicsBody());
	//CreateAABB(bodies[1], vec2(0,0), vec2(40,40), vec2(0,0), 50, 1);

	for (unsigned int i = 0; i < 20; i++)
	{
		std::cout << lge::generateUUIDv4() << "\n";
		//std::cout << randomDouble(-1, 1) << "\n";
	}*/
	return true;
}

std::vector<sf::VertexArray> lines;

int timeSteps = 2;

void run()
{
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
			if (event.type == sf::Event::KeyPressed)
				keyPressed = true;
			if (event.type == sf::Event::KeyReleased)
				keyPressed = false;
		}

		if (mousePressed)
		{
			/*
			unsigned int size = bodies.size();
			for (int i = size - 1; i < size - 1 + 5; i++) {
				//delete bodies[i];
				//bodies[i] = new PhysicsBody();
				bodies.push_back(new lge::PhysicsBody());
				lge::vec2 pos = lge::signRandom2D() * lge::randomDouble(0, windowSize.x);
				float r = 5 + rand() % 5;
				lge::vec2 vel = lge::random2D() * 80;
				float mass = 50 + rand() % 50;

				//std::cout << i << " " << pos << " " << r << " " << vel << " " << mass << "\n";

				CreateCircle(bodies[i], pos, r, vel, lge::PERFECT);
				bodies[i]->color = lge::random4D() * 255;//vec4(255, 0, 255, 0);
			}/**/
			mousePressed = false;/**/
		}

		//TODO: Extend physics rendering system

		double totalVel = 0;

		window->clear(sf::Color::White);

		lines.clear();

		//for (unsigned int i = 0; i < bodies.size(); i++)
		//{
			//std::cout << bodies[i]->velocity << " " << bodies[i]->acceleration << "\n";
		//}

		//player->movable = true;

		//lge::vec2 force = lge::forceForDesiredVelocity(*player, lge::vec2(5, 0), deltaTime, 1);
		//std::cout << force << "\n";
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			lge::applyForce(player, lge::forceForDesiredVelocity(*player, lge::vec2(-5, 0), deltaTime, 1));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			lge::applyForce(player, lge::forceForDesiredVelocity(*player, lge::vec2(5, 0), deltaTime, 1));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			lge::applyForce(player, lge::forceForDesiredVelocity(*player, lge::vec2(0, -50), deltaTime, 1));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			lge::applyForce(player, lge::forceForDesiredVelocity(*player, lge::vec2(0, 5), deltaTime, 1));
			*/
		//std::cout << player->force << " " << player->velocity << "\n";
		//lge::applyGravity(player, deltaTime, 1);
		//lge::updatePhysicsBody(player, deltaTime, 1);
		//std::cout << player->force << " " << player->velocity << "\n";
		//std::cout << "Player: " << player->velocity << " " << deltaTime << "\n";
		/*
		for (unsigned int i = 0; i < walls.size(); i++)
		{
			lge::Manifold wp = lge::Collide(player, walls[i]);
			if (wp.collision)
			{
				//std::cout << "collide\n";
				//lge::ApplyFriction(wp, player, walls[i]);
				lge::ResolveCollisionStatic(wp, player, walls[i]);
				lge::ApplyFriction(wp, player, walls[i]);

			}
		}

		for (unsigned int k = 0; k < timeSteps; k++) {
			for (unsigned int i = 0; i < bodies.size(); i++) {
				lge::updatePhysicsBody(bodies[i], deltaTime, timeSteps);
				//std::cout << bodies[i]->velocity << " " << deltaTime << "\n";
				//applyGravity(bodies[i], deltaTime, timeSteps);
				//lge::updatePhysicsBody(bodies[i], deltaTime, timeSteps);
				//bounceInArea(bodies[i], { 0,0 }, windowSize);
				//constrainPhysicsObject(bodies[i], { 0,0 }, windowSize);
				totalVel += bodies[i]->velocity.len();

				/*lge::Manifold pm = lge::Collide(player, bodies[i]);
				if (pm.collision)
				{
					//lge::ResolveCollisionStatic(pm, player, bodies[i]);
				}*/

				/*for (unsigned int j = 0; j < walls.size(); j++)
				{
					lge::Manifold m = lge::Collide(bodies[i], walls[j]);
					if (m.collision)
					{
						//staticCollisionResolution(m, bodies[i], walls[j]);
						lge::ResolveCollision(m, bodies[i], walls[j]);
						lge::ApplyFriction(m, bodies[i], bodies[j]);
						//walls[j]->velocity = vec2(0, 0);
						/*line[1].position = sf::Vector2f(bodyPos.x - m.normal.x * 5, bodyPos.y - m.normal.y * 5);
						line[1].color = sf::Color::Magenta;
						lines.push_back(line);
						//window->draw(line);
					}
				}

				for (unsigned int j = 0; j < bodies.size(); j++) {
					if (i != j)
					{
						lge::Manifold m = lge::Collide(bodies[i], bodies[j]);

						if (m.collision)
						{
							lge::ResolveCollision(m, bodies[i], bodies[j]);
							//lge::ApplyFriction(m, bodies[i], bodies[j]);
							//staticCollisionResolution(m, bodies[i], bodies[j]);
						

							lge::vec4 c = lge::random4D() * 255;
							c.w = 255;
							bodies[j]->color = c;// vec4(255, 255, 0, 0);
						}
					}
				}
				lge::constrainPhysicsBody(bodies[i], lge::vec2(), windowSize);
			}
		}



		for (unsigned int i = 0; i < bodies.size(); i++) {
			renderPhysicsObject(*window, bodies[i]);
		}

		for (unsigned int i = 0; i < walls.size(); i++)
		{
			renderPhysicsObject(*window, walls[i]);
		}

		renderPhysicsObject(*window, player);*/

		if(!keyPressed) engine.update(deltaTime);

		/*if (!keyPressed)
		{
		for (auto j : objects)
		{
			lge::PhysicsBody* object = engine.GetPhysicsBody(j);
			lge::updatePhysicsBody(object, deltaTime, 1);
			//std::cout << lge::getPosition(object);

			for (auto i : walls)
			{
				lge::PhysicsBody* wall = engine.GetPhysicsBody(i);
				lge::Manifold m = lge::Collide(object, wall);
				if (m.collision)
				{
					std::cout << m.normal << " " << m.penetration << "\n";
					lge::ResolveCollision(m, object, wall);
				}
			}
		}
		}*/
		for (auto i : walls)
		{
			lge::PhysicsBody* body = engine.GetPhysicsBody(i);

			renderPhysicsObject(*window, body);
		}

		for (auto i : objects)
		{
			lge::PhysicsBody* body = engine.GetPhysicsBody(i);

			renderPhysicsObject(*window, body);
		}
		/*
		sf::Image img;
		//img.create(200, 100, sf::Color::White);

		sf::Uint8* p = new sf::Uint8[200 * 100 * 4];// = new sf::Uint8[200 * 100 * 4];

		for (int x = 0; x < 200; x++)
		{
			for (int y = 0; y < 100; y++)
			{
				p[4 * (x * 100 + y)] = rand() % 255; // R?
				p[4 * (x * 100 + y) + 1] = rand() % 255; // G?
				p[4 * (x * 100 + y) + 2] = rand() % 255; // B?
				p[4 * (x * 100 + y) + 3] = rand() % 255; // A?

			}
		}

		img.create(200, 100, p);

		sf::Texture text;
		text.loadFromImage(img);
		sf::Sprite s;//
		s.setTexture(text);
		s.setPosition(200, 100);
		//window->draw(s);

		delete[] p;/**/

		window->display();

		deltaTime = deltaClock.restart().asSeconds();
		fps = 1 / deltaTime;
		//std::cout << fps << " " << deltaTime<< "\n";
	}
}

bool destroy() {
	window = NULL;
	delete window;
	return true;
}
