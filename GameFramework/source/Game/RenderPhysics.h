#pragma once

#include <SFML/Graphics.hpp>
#include "PhysicsBodies.h"
#include "Components.h"

inline void renderPhysicsObject(sf::RenderWindow& target, lge::PhysicsBody* body, sf::Color fillColor)
{

	switch (body->type)
	{
	case lge::BodyType::AABB:
	{
		sf::RectangleShape rect;
		rect.setPosition(body->aabb.min.x, body->aabb.min.y);
		lge::vec2 dim = body->aabb.max - body->aabb.min;
		//std::cout << body->aabb.min << " " << dim << " " <<  lge::vec4(fillColor.r,fillColor.g, fillColor.b, fillColor.a) << "\n";
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
		target.draw(edgePoint);*/
		break;
	}

	case lge::BodyType::Circle:
	{
		sf::CircleShape circle;
		circle.setPosition(body->circle.pos.x - body->circle.radius, body->circle.pos.y - body->circle.radius);
		circle.setRadius(body->circle.radius);
		circle.setFillColor(fillColor);
		target.draw(circle);
		break;
	}

	case lge::BodyType::Polygon:
	{
		sf::ConvexShape shape;
		shape.setPointCount(body->polygon.transformedPoints.size());

		for (unsigned int i = 0; i < body->polygon.transformedPoints.size(); i++) {
			shape.setPoint(i, sf::Vector2f(body->polygon.transformedPoints[i].x, body->polygon.transformedPoints[i].y));
		}

		shape.setFillColor(fillColor);
		target.draw(shape);
		break;
	}

	case lge::BodyType::Null:
		break;
	}
}

inline void renderVec2List(sf::RenderWindow& target, std::vector<lge::vec2> vec2List)
{
	sf::VertexArray lines(sf::Lines, vec2List.size() * 2);
	unsigned int j = 0;
	for (unsigned int i = 0; i < vec2List.size() * 2; i+=2)
	{
		lines[i].position = sf::Vector2f(vec2List[j % vec2List.size()].x, vec2List[j % vec2List.size()].y);
		lines[i+1] = sf::Vector2f(vec2List[(j + 1) % vec2List.size()].x, vec2List[(j + 1) % vec2List.size()].y);
		j++;
	}

	for (unsigned int i = 0; i < lines.getVertexCount(); i++) lines[i].color = sf::Color::Black;

	//std::cout << lines.getVertexCount() << "\n";

	target.draw(lines);
}

inline void renderPhysicsObject(sf::RenderWindow& target, lge::PhysicsBody* body)
{
	renderPhysicsObject(target, body, sf::Color(body->color.x, body->color.y, body->color.z, body->color.w));
}