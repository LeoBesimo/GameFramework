#pragma once

#include "CollisionDetection.h"
#include "BodyCreator.h"
#include "SFML/Graphics.hpp"

inline vec2 getPosition(PhysicsBody* body)
{
	switch (body->type)
	{
	case BodyType::Circle:
		return body->circle.pos;
	case BodyType::AABB:
		return body->aabb.min;
	case BodyType::Polygon:
		/*body->velocity += body->acceleration * deltaTime;
		body->polygon.pos += body->velocity * deltaTime;
		for (unsigned int i = 0; i < body->polygon.points.size(); i++)
		{
			body->polygon.points[i] += body->velocity * deltaTime;
		}
		body->acceleration.set(0, 0);*/
		return body->polygon.pos;
	}

	return vec2(0, 0);
}

inline void setPosition(PhysicsBody* body, vec2 pos)
{
	switch (body->type)
	{
	case BodyType::Circle:
		body->circle.pos = pos;
		break;
	case BodyType::AABB:
	{
		vec2 size = body->aabb.max - body->aabb.min;
		body->aabb.min = pos;
		body->aabb.max = pos + size;
		break;
	}
	case BodyType::Polygon:
		/*body->velocity += body->acceleration * deltaTime;
		body->polygon.pos += body->velocity * deltaTime;
		for (unsigned int i = 0; i < body->polygon.points.size(); i++)
		{
			body->polygon.points[i] += body->velocity * deltaTime;
		}
		body->acceleration.set(0, 0);*/
		break;
	}
}

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
	{
		vec2 dim = body->aabb.max - body->aabb.min;
		body->aabb.min = constrainVec2(body->aabb.min, min, max - dim);
		body->aabb.max = constrainVec2(body->aabb.max, min + dim, max);
		break;
	}
	case BodyType::Circle:
		body->circle.pos = constrainVec2(body->circle.pos, min + body->circle.radius, max - body->circle.radius);
		break;

	case BodyType::Polygon:

	case BodyType::Null:
		break;
	}
}

inline void bounceInArea(PhysicsBody* body, vec2 min, vec2 max)
{
	switch (body->type)
	{
	case BodyType::AABB:
	{
		vec2 dim = body->aabb.max - body->aabb.min;
		if (body->aabb.min.x > max.x - dim.x || body->aabb.max.x < min.x + dim.x) body->velocity.x *= -1;
		if (body->aabb.min.y > max.y - dim.y || body->aabb.max.y < min.y + dim.y) body->velocity.y *= -1;
		break;
	}
	case BodyType::Circle:
		if (body->circle.pos.x > max.x - body->circle.radius || body->circle.pos.x < min.x + body->circle.radius) body->velocity.x *= -1;
		if (body->circle.pos.y > max.y - body->circle.radius || body->circle.pos.y < min.y + body->circle.radius) body->velocity.y *= -1;
		break;
	case BodyType::Polygon:
		break;
	}
}

inline void renderPhysicsObject(sf::RenderWindow& target,PhysicsBody* body, sf::Color fillColor)
{

	switch (body->type)
	{
	case BodyType::AABB:
	{
		sf::RectangleShape rect;
		rect.setPosition(body->aabb.min.x, body->aabb.min.y);
		vec2 dim = body->aabb.max - body->aabb.min;
		//std::cout << dim << "\n";
		rect.setSize(sf::Vector2f(dim.x,dim.y));
		rect.setFillColor(fillColor);
		target.draw(rect);

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
}