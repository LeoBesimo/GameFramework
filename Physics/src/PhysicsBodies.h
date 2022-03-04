#pragma once

#include "Components.h"
#include "Utilities.h"
#include "Materials.h"
#include <vector>

namespace lge
{
	enum BodyType { AABB, Circle, Polygon, Null };

	typedef struct _MassData
	{
		double mass;
		double invMass;

		double inertia;
		double invInertia;

	} MassData;

	typedef struct _AABB
	{
		vec2 min = vec2(0, 0);
		vec2 max = vec2(0, 0);

	} AABBStruct;

	typedef struct _Circle
	{
		vec2 pos = vec2(0, 0);
		double radius = 0;

	} CircleStruct;

	typedef struct _Polygon
	{
		vec2 pos = vec2(0, 0);
		std::vector<vec2> originalPoints;
		std::vector<lge::vec2> transformedPoints;

	} PolygonStruct;

	typedef struct _PhysicsBody
	{
		BodyType type = BodyType::Null;
		AABBStruct aabb;
		CircleStruct circle;
		PolygonStruct polygon;

		uuid id;

		bool staticCollision = false;
		bool applyFriction = false;

		bool movable = true;
		bool collidedWithImmovable = false;


		vec2 force;
		vec2 velocity;
		vec2 acceleration;

		double orientation;
		double angularVelocity;
		double torque;

		MassData massData;
		Material material;

		vec4 color = { 255,255,255,255 };

	} PhysicsBody;

	typedef struct _Manifold
	{
		bool collision;
		PhysicsBody a;
		PhysicsBody b;
		vec2 normal;
		float dist;
		float penetration;

	} Manifold;
}