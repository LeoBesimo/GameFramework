#include "Physics2.h"

namespace lgeuf
{
	vec2 getPosition(PhysicsBody* body)
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

	void setPosition(PhysicsBody* body, vec2 pos)
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

	void applyGravity(PhysicsBody* a, double deltaTime, int timeSteps)
	{
		a->velocity.y += GRAVITY * deltaTime / timeSteps;
	}

	bool updatePhysicsBody(PhysicsBody* body, float deltaTime, int timeSteps)
	{
		body->collidedWithImmovable = false;

		double tf = 1.0 / timeSteps;

		//std::cout << tf << "\n";

		switch (body->type)
		{
		case BodyType::Circle:
		{
			vec2 acceleration = body->force * body->massData.invMass;
			body->velocity += acceleration * deltaTime;
			vec2 tempVel = body->velocity * deltaTime;
			body->circle.pos += tempVel * tf;
			body->force.set(0, 0);
			return true;
		}

		case BodyType::AABB:
		{
			vec2 acceleration = body->force * body->massData.invMass;
			body->velocity += acceleration * deltaTime;
			vec2 tempVel = body->velocity * deltaTime;
			body->aabb.min += tempVel * tf;
			body->aabb.max += tempVel * tf;
			body->force.set(0, 0);
			return true;
		}
		case BodyType::Polygon:
		{
			vec2 acceleration = body->force * body->massData.invMass;
			body->velocity += acceleration * deltaTime;
			vec2 tempVel = body->velocity * deltaTime;
			body->polygon.pos += tempVel * tf;
			for (unsigned int i = 0; i < body->polygon.points.size(); i++)
			{
				body->polygon.points[i] += tempVel * tf;
			}
			body->force.set(0, 0);
			return true;
		}
		}
		return false;
	}

	bool updatePhysicsBody(PhysicsBody* body, float deltaTime)
	{
		switch (body->type)
		{
		case BodyType::Circle:
		{
			vec2 acceleration = body->force * body->massData.invMass;
			body->velocity += acceleration * deltaTime * body->movable;
			body->circle.pos += body->velocity * deltaTime * body->movable;
			body->force.set(0, 0);
			return true;
		}
		case BodyType::AABB:
		{
			vec2 acceleration = body->force * body->massData.invMass;
			body->velocity += acceleration * deltaTime * body->movable;
			body->aabb.min += body->velocity * deltaTime * body->movable;
			body->aabb.max += body->velocity * deltaTime * body->movable;
			body->force.set(0, 0);
			return true;
		}
		case BodyType::Polygon:
		{
			vec2 acceleration = body->force * body->massData.invMass;
			body->velocity += acceleration * deltaTime * body->movable;
			body->polygon.pos += body->velocity * deltaTime * body->movable;
			for (unsigned int i = 0; i < body->polygon.points.size(); i++)
			{
				body->polygon.points[i] += body->velocity * deltaTime * body->movable;
			}
			body->force.set(0, 0);
			return true;
		}
		}
		return false;
	}

	void lge::constrainPhysicsObject(PhysicsBody* body, vec2 min, vec2 max)
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

	void lge::bounceInArea2(PhysicsBody* body, vec2 min, vec2 max)
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
}