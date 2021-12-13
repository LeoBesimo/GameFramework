#include "BodyCreator.h"

namespace lge
{
	bool CreateCircle(PhysicsBody* body, vec2 pos, double radius, vec2 vel, Material material)
	{
		//body = new PhysicsBody();
		if (body == nullptr) return false;

		body->type = BodyType::Circle;

		//std::cout << pos.x << " " << pos.y << "\n";

		body->circle = { vec2(pos.x,pos.y) , radius };

		//std::cout << body->circle.pos.x << " " << body->circle.pos.y << "\n";

		double area = radius * radius * PI;
		double mass = area * material.density;

		body->velocity = vel;
		body->massData.mass = mass;
		body->massData.invMass = (mass == 0) ? 0 : 1 / mass;
		body->material = material;

		return true;
	}

	bool CreateAABB(PhysicsBody* body, vec2 pos, vec2 dim, vec2 vel, Material material)
	{
		//body = new PhysicsBody();
		if (body == nullptr) return false;

		body->type = BodyType::AABB;
		body->aabb = { pos, pos + dim };

		float area = dim.x * dim.y;
		float mass = area * material.density;

		body->velocity = vel;
		body->massData.mass = mass;
		body->massData.invMass = (mass == 0) ? 0 : 1 / mass;
		body->material = material;

		return true;
	}

	bool CreatePolygon(PhysicsBody* body, vec2 pos, float radius, unsigned int numberPoints, vec2 vel, Material material)
	{
		if (body == nullptr || numberPoints < 2) return false;

		body->type = BodyType::Polygon;

		float increment = TWO_PI / numberPoints;
		std::vector<vec2> points;

		for (unsigned int i = 0; i < numberPoints; i++) {
			float x = radius * cos(increment * i) + pos.x;
			float y = radius * sin(increment * i) + pos.y;
			points.push_back(vec2(x, y));
		}

		vec2 side = points[1] - points[0];
		double sideLength = dotVec2(side, side);

		double apothem = sideLength / (2.0f * tan(180 / numberPoints));
		double area = (numberPoints * sideLength * apothem) / 2;

		body->polygon = { pos, points };
		double mass = area * material.density;
		body->velocity = vel;
		body->massData.mass = mass;
		body->massData.invMass = (mass == 0) ? 0 : 1 / mass;
		body->material = material;

		return true;
	}
}