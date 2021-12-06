#pragma once

#include "components.h"
#include "Materials.h"
#include <vector>
#include <memory>

enum BodyType {AABB, Circle, Polygon, Null};

typedef struct _MassData
{
	double mass;
	double invMass;

	double inertia;
	double invInertia;
} MassData;

typedef struct _AABB
{
	vec2 min = vec2(0,0);
	vec2 max = vec2(0,0);
} AABBStruct;

typedef struct _Circle
{
	vec2 pos = vec2(0,0);
	float radius = 0;
} CircleStruct;

typedef struct _Polygon
{
	vec2 pos = vec2(0,0);
	std::vector<vec2> points;

} PolygonStruct;

typedef struct _PhysicsBody
{
	BodyType type = BodyType::Null;
	AABBStruct aabb;
	CircleStruct circle;
	PolygonStruct polygon;
	
	bool movable = true;
	bool collidedWithImmovable = false;

	vec2 force;
	vec2 velocity;

	MassData massData;
	Material material;

	vec4 color = {255,255,255,255};

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

