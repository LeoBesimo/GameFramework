#include "Engine.h"

namespace lge
{
	Engine::Engine()
	{
	}

	Engine::~Engine()
	{
		for (auto key : objects)
		{
			delete key.second;
			key.second = nullptr;
		}

		objects.clear();
	}

	vec2 Engine::GetGravity()
	{
		return GRAVITY;
	}

	void Engine::SetGravity(const vec2 grav)
	{
		this->GRAVITY = grav;
	}

	void Engine::SetNumberTimeSteps(const int TimeSteps)
	{
		this->TimeSteps = TimeSteps;
	}

	int Engine::GetNumberTimeSteps()
	{
		return this->TimeSteps;
	}

	uuid Engine::AddObjectAABB(vec2 position, vec2 dimension, vec2 initialVelocity, Material material)
	{
		uuid uuid = generateUUIDv4();
		PhysicsBody* body = new PhysicsBody();
		CreateAABB(body, position, dimension, initialVelocity, material);
		objects[uuid] = body;
		return uuid;
	}

	uuid Engine::AddObjectCircle(vec2 position, double radius, vec2 initialVelocity, Material material)
	{
		uuid uuid = generateUUIDv4();
		PhysicsBody* body = new PhysicsBody();
		CreateCircle(body, position, radius, initialVelocity, material);
		objects[uuid] = body;
		return uuid;
	}

	uuid Engine::AddObjectPolygon(vec2 position, double radius, unsigned int numberPoints, vec2 initialVelocity, Material material)
	{
		uuid uuid = generateUUIDv4();
		PhysicsBody* body = new PhysicsBody();
		CreatePolygon(body, position, radius, numberPoints, initialVelocity, material);
		objects[uuid] = body;
		return uuid;
	}

	uuid Engine::AddPhysicsBody(PhysicsBody* body)
	{
		uuid uuid = generateUUIDv4();
		objects[uuid] = body;
		return uuid;
	}

	void Engine::DeletePhysicsBody(uuid key)
	{
		std::unordered_map<uuid, PhysicsBody*>::iterator itr = objects.find(key);
		if (itr == objects.end()) return;
		delete itr->second;
		objects.erase(itr);
	}

	PhysicsBody* Engine::GetPhysicsBody(uuid key)
	{
		auto itr = objects.find(key);
		if (itr == objects.end())
			return nullptr;
		return itr->second;
	}
	std::vector<PhysicsBody*> Engine::GetPhysicBodies()
	{
		std::vector<PhysicsBody*> bodies;
		for (const auto& pair : objects)
			bodies.push_back(pair.second);
		return bodies;
	}
	void Engine::update(float deltaTime)
	{
		for (int i = 0; i < TimeSteps; i++)
		{
			for (const auto& pair : objects)
			{
				PhysicsBody* body = pair.second;
				updatePhysicsBody(body, deltaTime, TimeSteps);
				
				//std::cout << getPosition(body) << " " << body->velocity << "\n";
				//constrainPhysicsBody(body, vec2(0, 0), vec2(1000, 800));

				//std::cout << deltaTime << "\n";
				//std::cout << pair.first << " " << getPosition(body) << "\n";
				//std::cout << body->color << "\n";

				for (const auto& pair2 : objects)
				{
					if (pair.first == pair2.first)
					{
						//std::cout << pair.first << " same " << pair2.first << "\n";
						continue;
					}
					PhysicsBody* body2 = pair2.second;

					Manifold m = Collide(body, body2);
					if (m.collision)
					{
						//std::cout << "test\n";
						ResolveCollision(m, body, body2);
						ResolveCollisionStatic(m, body, body2);
						ApplyFriction(m, body, body2);
					}
				}
			}
		}
	}
}