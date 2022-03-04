#pragma once
#include <SFML/Graphics.hpp>

#include "Components.h"
#include "lgeMath.h"
//#include "Physics.h"
//#include "CollisionDetection.h"
//#include "BodyCreator.h"
//#include "CollisionResolution.h"
#include "PhysicsEngine.h"

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

//lge::PhysicsEngine engine;
//std::vector<lge::uuid> objects;
//lge::uuid walls[4];

bool create(int screenWidth, int screenHeight) {
	srand(time(NULL));

	sf::Vector2i screenSize = sf::Vector2i(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	screenScaling = lge::vec2(screenSize.x / screenWidth, screenSize.y / screenHeight);

	window = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), "Yeet");
	window->setFramerateLimit(60);

	shape.setFillColor(sf::Color::Green);
	circle.setFillColor(sf::Color::Cyan);

	windowSize = lge::vec2(screenWidth, screenHeight);

	/*
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
		lge::vec2 pos = lge::signRandom2D() * lge::randomDouble(0, screenWidth);
		lge::vec2 vel = lge::random2D() * 80;
		double r = lge::randomDouble(5, 10);
		lge::uuid id = engine.AddObjectCircle(pos, r, vel, lge::PERFECT);
		engine.GetPhysicsBody(id)->color = lge::vec4(255, 255, 0, 255);
		objects.push_back(id);
	}
	*/

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
			mousePressed = false;
		}

		//TODO: Extend physics rendering system

		double totalVel = 0;

		window->clear(sf::Color::White);

		lines.clear();

		double angle = lge::map(mousePos.x,0,windowSize.x,0, lge::TWO_PI);

		lge::mat2 screen(1000, 0, 0, 800);

		lge::mat2 scaler(150, 0, 0, 150);

		lge::mat2 rotation(cos(angle), -sin(angle), sin(angle), cos(angle));
		//rotation = lge::invMat2(rotation);
		//rotation = lge::invMat2(rotation);
		lge::vec2 pos(-0.25, -0.25);
		lge::vec2 pos1(0.25, -0.25);
		lge::vec2 pos2(0.25, 0.25);
		lge::vec2 pos3(-0.25, 0.25);

		//lge::mat2 transform = screen * lge::invMat2(screen * 0.5) *rotation * (screen * 0.5);
		
		lge::mat2 transform = scaler * rotation;

		lge::vec2 displacement = windowSize/2;

		//std::cout << transform << "\n";

		lge::vec2 scaledPos = transform * pos + displacement;
		lge::vec2 scaledPos1 = transform * pos1 + displacement;
		lge::vec2 scaledPos2 = transform * pos2 + displacement;
		lge::vec2 scaledPos3 = transform * pos3 + displacement;

		sf::Vertex line[8];
		for (int i = 0; i < 8; i++) line[i].color = sf::Color::Red;
		line[0].color = sf::Color::Blue;
		line[0].position = sf::Vector2f(scaledPos.x, scaledPos.y);
		line[1].position = sf::Vector2f(scaledPos1.x, scaledPos1.y);
		line[2].position = sf::Vector2f(scaledPos1.x, scaledPos1.y);
		line[3].position = sf::Vector2f(scaledPos2.x, scaledPos2.y);
		line[4].position = sf::Vector2f(scaledPos2.x, scaledPos2.y);
		line[5].position = sf::Vector2f(scaledPos3.x, scaledPos3.y);
		line[6].position = sf::Vector2f(scaledPos3.x, scaledPos3.y);
		line[7].position = sf::Vector2f(scaledPos.x, scaledPos.y);

		window->draw(line,8 ,sf::Lines);


		/*if(!keyPressed) engine.update(deltaTime);

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
		*/
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
