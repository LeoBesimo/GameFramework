#include "Physics.h"

namespace lge
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

	void setPosition(PhysicsBody* body, vec2 position)
	{
		switch (body->type)
		{
		case BodyType::Circle:
			body->circle.pos = position;
			break;
		case BodyType::AABB:
		{
			vec2 size = body->aabb.max - body->aabb.min;
			body->aabb.min = position;
			body->aabb.max = position + size;
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

	vec2 forceForDesiredVelocity(const PhysicsBody &body, vec2 desiredVelocity, double deltaTime, double timeSteps)
	{
		return desiredVelocity / deltaTime / body.massData.invMass * timeSteps;
	}

	void applyForce(PhysicsBody* body, vec2 force)
	{
		//std::cout << "Applying force: " << force * deltaTime / timeSteps * body->movable << "\n";
		body->force += force * body->movable;
		//std::cout << "Body force: " << body->force << "\n";
	}

	void applyGravity(PhysicsBody* body, double deltaTime, double timeSteps)
	{
		body->velocity.y += lge::GRAVITY * deltaTime * timeSteps;
		//body->velocity.y += GRAVITY * deltaTime / timeSteps;
	}

	bool updatePhysicsBody(PhysicsBody* body, double deltaTime, double timeSteps)
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
			body->circle.pos += tempVel * tf * body->movable;
			body->force.set(0, 0);
			body->velocity *= body->movable;
			return true;
		}

		case BodyType::AABB:
		{
			vec2 acceleration = body->force * body->massData.invMass;
			body->velocity += acceleration * deltaTime;
			vec2 tempVel = body->velocity * deltaTime;
			body->aabb.min += tempVel * tf * body->movable;
			body->aabb.max += tempVel * tf * body->movable;
			body->force.set(0, 0);
			body->velocity *= body->movable;
			return true;
		}
		case BodyType::Polygon:
		{
			vec2 acceleration = body->force * body->massData.invMass;
			body->velocity += acceleration * deltaTime;
			vec2 tempVel = body->velocity * deltaTime;
			body->polygon.pos += tempVel * tf * body->movable;
			for (unsigned int i = 0; i < body->polygon.originalPoints.size(); i++)
			{
				body->polygon.originalPoints[i] += tempVel * tf * body->movable;
			}
			body->force.set(0, 0);
			body->velocity *= body->movable;
			return true;
		}
		}
		return false;
	}

	void constrainPhysicsBody(PhysicsBody* body, vec2 min, vec2 max)
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

	void bounceInArea(PhysicsBody* body, vec2 min, vec2 max)
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