#pragma once

#include "CollisionDetection.h"
#include "BodyCreator.h"
#include "SFML/Graphics.hpp"

inline bool updatePhysicsBody(PhysicsBody* body, float deltaTime) 
{
	switch (body->type)
	{
	case BodyType::Circle:
		body->velocity += body->acceleration * deltaTime;
		body->circle.pos += body->velocity * deltaTime;
		body->acceleration.set(0, 0);
		return true;

	case BodyType::AABB:
		body->velocity += body->acceleration * deltaTime;
		body->aabb.min += body->velocity * deltaTime;
		body->aabb.max += body->velocity * deltaTime;
		body->acceleration.set(0, 0);
		return true;

	case BodyType::Polygon:
		body->velocity += body->acceleration * deltaTime;
		body->polygon.pos += body->velocity * deltaTime;
		for (unsigned int i = 0; i < body->polygon.points.size(); i++) 
		{
			body->polygon.points[i] += body->velocity * deltaTime;
		}
		body->acceleration.set(0, 0);
		return true;
	}
	return false;
}

inline void constrainPhysicsObject(PhysicsBody* body, vec2 min, vec2 max) 
{
	switch (body->type) 
	{
	case BodyType::AABB:
		body->aabb.min.x = constrain(body->aabb.min.x, min.x, max.x - body->aabb.max.x - body->aabb.min.x);
		body->aabb.min.y = constrain(body->aabb.min.y, min.y, max.y - body->aabb.max.y - body->aabb.min.y);
		body->aabb.max.x = constrain(body->aabb.max.x, min.x + body->aabb.max.x - body->aabb.min.x, max.x);
		body->aabb.max.y = constrain(body->aabb.max.y, min.y + body->aabb.max.y - body->aabb.min.y, max.y);
		break;

	case BodyType::Circle:
		body->circle.pos = constrainvec2(body->circle.pos, min + body->circle.radius, max - body->circle.radius);
		break;

	case BodyType::Polygon:

	case BodyType::Null:
		break;
	}
}

inline void renderPhysicsObject(sf::RenderWindow& target,PhysicsBody* body, sf::Color fillColor)
{

	switch (body->type)
	{
	case BodyType::AABB:
	{sf::RectangleShape rect;
	rect.setPosition(body->aabb.min.x, body->aabb.min.y);
	rect.setSize(sf::Vector2f(body->aabb.max.x - body->aabb.min.x, body->aabb.max.y - body->aabb.min.y));
	rect.setFillColor(fillColor);
	target.draw(rect);
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
}