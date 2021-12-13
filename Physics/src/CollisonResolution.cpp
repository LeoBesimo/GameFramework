#include "CollisionResolution.h"

namespace lge
{
	void ResolveCollision(Manifold m, PhysicsBody* a, PhysicsBody* b)
	{
		vec2 rv = b->velocity - a->velocity;

		float velAlongNormal = dotVec2(rv, m.normal);

		if (velAlongNormal > 0) return;

		float e = fminf(a->material.restitution, b->material.restitution);

		float j = -(1 + e) * velAlongNormal;
		if(a->massData.invMass + b->massData.invMass != 0) j /= a->massData.invMass + b->massData.invMass;

		vec2 impulse = m.normal * j;

		a->velocity -= impulse * a->massData.invMass * (a->movable || !a->collidedWithImmovable);
		b->velocity += impulse * b->massData.invMass * (b->movable || !b->collidedWithImmovable);
	}

	void ResolveCollisionStatic(Manifold m, PhysicsBody* a, PhysicsBody* b)
	{
		if (a->collidedWithImmovable || !a->movable) b->collidedWithImmovable = true;
		if (b->collidedWithImmovable || !b->movable) a->collidedWithImmovable = true;

		vec2 aPos = getPosition(a);
		vec2 bPos = getPosition(b);
		aPos -= m.normal * (m.penetration / 2) * (a->movable || !a->collidedWithImmovable);
		bPos += m.normal * (m.penetration / 2) * (b->movable || !a->collidedWithImmovable);
		setPosition(a, aPos);
		setPosition(b, bPos);
	}

	void ApplyFriction(Manifold m, PhysicsBody* a, PhysicsBody* b)
	{
		vec2 rv = b->velocity - a->velocity;
		vec2 t = rv - m.normal * dotVec2(rv, m.normal);
		t.normalize();

		//t *= -1;

		float velAlongNormal = dotVec2(rv, m.normal);

		if (velAlongNormal > 0) return;
		
		float e = fminf(a->material.restitution, b->material.restitution);

		float j = -(1 + e) * velAlongNormal;
		if (a->massData.invMass + b->massData.invMass != 0) j /= a->massData.invMass + b->massData.invMass;

		float jt = -dotVec2(rv.normalize(), m.normal.normalize());
		//std::cout << -dotVec2(rv, m.normal) << "\n";
		if (a->massData.invMass + b->massData.invMass != 0) j /= a->massData.invMass + b->massData.invMass;  jt = jt / (a->massData.invMass + b->massData.invMass);

		float mu = PythagoreanSolve(a->material.staticFriction, b->material.staticFriction);
		
		vec2 frictionImpulse;
		//std::cout << jt << " " << mu << " " << j << " " << j * mu << "\n";

		if ((jt) < j * mu)
		{
			//std::cout << "static \n";
			frictionImpulse = t * jt;
		}
		else
		{
			//std::cout << "dynamic \n";
			mu = PythagoreanSolve(a->material.dynamicFriction, b->material.dynamicFriction);
			frictionImpulse = t * -j * mu;
		}

		//std::cout << t << " " << frictionImpulse << " " << mu << "\n";

		a->velocity += frictionImpulse * a->massData.invMass * (a->movable || a->collidedWithImmovable);
		b->velocity -= frictionImpulse * b->massData.invMass * (b->movable || b->collidedWithImmovable);
	
	}

	void PositionalCorrection(Manifold m, PhysicsBody* a, PhysicsBody* b)
	{
		const float percent = 1.1;
		const float slop = 0.01;
		vec2 correction = m.normal * (max(m.penetration - slop, 0.0f) / (a->massData.invMass + b->massData.invMass)) * percent;
		vec2 pos1 = getPosition(a);
		vec2 pos2 = getPosition(b);

		pos1 -= correction * a->massData.invMass * a->movable;
		pos2 += correction * b->massData.invMass * b->movable;

		setPosition(a, pos1);
		setPosition(b, pos2);
	}

	Manifold Collide(PhysicsBody* a, PhysicsBody* b)
	{
		switch (a->type)
		{
		case BodyType::AABB:
			switch (b->type)
			{
			case BodyType::AABB:
			{
				Manifold m;
				m.a = *a;
				m.b = *b;
				m = AABBVsAABB(m);
				return m;
			}
			case BodyType::Circle:
			{
				Manifold m;
				m.a = *b;
				m.b = *a;
				m = CircleVsAABB(m);
				//positionalCorrection(m, a, b);
				//ResolveCollisionStatic(m, b, a);
				return m;
			}
			case BodyType::Polygon:
				break;
			case BodyType::Null:
				break;
			}
			break;

		case BodyType::Circle:
			switch (b->type)
			{
			case BodyType::AABB:
			{
				Manifold m;
				m.a = *a;
				m.b = *b;
				m = CircleVsAABB(m);
				//positionalCorrection(m, a, b);
				//ResolveCollisionStatic(m, a, b);
				return m;
			}
			case BodyType::Circle:
			{
				Manifold m;
				m.a = *a;
				m.b = *b;
				m = CircleVsCircle(m);
				return m;
			}
			case BodyType::Polygon:
				break;
			case BodyType::Null:
				break;
			}
			break;

		case BodyType::Polygon:
			switch (b->type)
			{
			case BodyType::AABB:
				break;
			case BodyType::Circle:
				break;
			case BodyType::Polygon:
				break;
			case BodyType::Null:
				break;
			}
			break;


		case BodyType::Null:
			switch (b->type)
			{
			case BodyType::AABB:
				break;
			case BodyType::Circle:
				break;
			case BodyType::Polygon:
				break;
			case BodyType::Null:
				break;
			}
			break;
		}
		Manifold m;
		m.collision = false;
		return m;
	}
}