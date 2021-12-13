#pragma once

#include <unordered_map>

#include "Utilities.h"
#include "Components.h"
#include "PhysicsBodies.h"
#include "BodyCreator.h"
#include "CollisionResolution.h"

namespace lge
{
	class Engine {
	
	private:
		vec2 GRAVITY;

		std::unordered_map<uuid, PhysicsBody*> objects;
		std::vector<uuid> keys;

		int TimeSteps = 2;

	public:

		Engine();
		~Engine();
		
		vec2 GetGravity();
		void SetGravity(const vec2 grav);
		
		void SetNumberTimeSteps(const int TimeSteps);
		int GetNumberTimeSteps();

		uuid AddObjectAABB(vec2 position, vec2 dimension, vec2 initialVelocity, Material material);
		uuid AddObjectCircle(vec2 position, double radius, vec2 initialVelocity, Material material);
		uuid AddObjectPolygon(vec2 position, double radius, unsigned int numberPoints, vec2 initialVelocity, Material material);
		uuid AddPhysicsBody(PhysicsBody* body);

		void DeletePhysicsBody(uuid key);
		PhysicsBody* GetPhysicsBody(uuid key);
		std::vector<PhysicsBody*> GetPhysicBodies();

		void update(float deltaTime);
	};
}