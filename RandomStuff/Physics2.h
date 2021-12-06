#pragma once

#include "components.h"

#include "CollisionDetection.h"

#define GRAVITY 20

namespace lge
{
	vec2 lge::getPosition(PhysicsBody* body);

	void lge::setPosition(PhysicsBody* body, vec2 pos);

	void lge::applyGravity(PhysicsBody* a, double deltaTime, int timeSteps);

	bool lge::updatePhysicsBody(PhysicsBody* body, float deltaTime, int timeSteps);

	bool lge::updatePhysicsBody(PhysicsBody* body, float deltaTime);

	void lge::constrainPhysicsObject(PhysicsBody* body, vec2 min, vec2 max);

	void lge::bounceInArea(PhysicsBody* body, vec2 min, vec2 max);
}
/*inline void renderPhysicsObject(sf::RenderWindow& target, PhysicsBody* body, sf::Color fillColor)
{

	switch (body->type)
	{
	case BodyType::AABB:
	{
		sf::RectangleShape rect;
		rect.setPosition(body->aabb.min.x, body->aabb.min.y);
		vec2 dim = body->aabb.max - body->aabb.min;
		//std::cout << dim << "\n";
		rect.setSize(sf::Vector2f(dim.x, dim.y));
		rect.setFillColor(fillColor);
		target.draw(rect);

		/*
		sf::CircleShape edgePoint;
		edgePoint.setRadius(5);
		edgePoint.setPosition(body->aabb.min.x-2.5, body->aabb.min.y-2.5);
		edgePoint.setFillColor(sf::Color::Green);
		target.draw(edgePoint);
		edgePoint.setPosition(body->aabb.max.x-2.5, body->aabb.max.y-2.5);
		target.draw(edgePoint);
		break;
	}

	case BodyType::Circle:
	{
		sf::CircleShape circle;
		circle.setPosition(body->circle.pos.x - body->circle.radius, body->circle.pos.y - body->circle.radius);
		circle.setRadius(body->circle.radius);
		circle.setFillColor(fillColor);
		target.draw(circle);
		break;
	}

	case BodyType::Polygon:
	{
		sf::ConvexShape shape;
		shape.setPointCount(body->polygon.points.size());

		for (unsigned int i = 0; i < body->polygon.points.size(); i++) {
			shape.setPoint(i, sf::Vector2f(body->polygon.points[i].x, body->polygon.points[i].y));
		}

		shape.setFillColor(fillColor);
		target.draw(shape);
		break;
	}

	case BodyType::Null:
		break;
	}
}

inline void renderPhysicsObject(sf::RenderWindow& target, PhysicsBody* body)
{
	renderPhysicsObject(target, body, sf::Color(body->color.x, body->color.y, body->color.z, body->color.w));
}*/