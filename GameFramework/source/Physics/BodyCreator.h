#include "PhysicsBodies.h"
#include <iostream>

inline bool CreateCircle(PhysicsBody* body, vec2 pos, float radius ,vec2 vel, float mass, float restitution)
{
	//body = new PhysicsBody();
	if (body == nullptr) return false;

	body->type = BodyType::Circle;

	//std::cout << pos.x << " " << pos.y << "\n";

	body->circle = { vec2(pos.x,pos.y) , radius };

	//std::cout << body->circle.pos.x << " " << body->circle.pos.y << "\n";

	body->velocity = vel;
	body->mass = mass;
	body->restitution = restitution;
	
	return true;
}

inline bool CreateAABB(PhysicsBody* body, vec2 pos, vec2 dim, vec2 vel ,float mass, float restitution)
{
	//body = new PhysicsBody();
	if (body == nullptr) return false;

	body->type = BodyType::AABB;
	body->aabb = { pos, pos + dim };
	
	body->velocity = vel;
	body->mass = mass;
	body->restitution = restitution;

	return true;
}

inline bool CreatePolygon(PhysicsBody* body, vec2 pos, float radius, float numberPoints, vec2 vel, float mass, float restitution)
{
	//body = new PhysicsBody();
	if (body == nullptr) return false;

	body->type = BodyType::Polygon;
	
	float increment = TWO_PI / numberPoints;
	std::vector<vec2> points;

	for (unsigned int i = 0; i < numberPoints; i++) {
		float x = radius * cos(increment * i) + pos.x;
		float y = radius * sin(increment * i) + pos.y;
		points.push_back(vec2(x, y));
	}

	body->polygon = { pos, points };

	body->velocity = vel;
	body->mass = mass;
	body->restitution = restitution;

	return true;
}