#include "..\..\Core Engine\src\Core\Engine.h"
#include "PhysicsEngine.h"

namespace lge
{
	PhysicsEngine::PhysicsEngine()
	{
	}

	PhysicsEngine::~PhysicsEngine()
	{
		for (auto key : objects)
		{
			delete key.second;
			key.second = nullptr;
		}

		objects.clear();
	}

	vec2 PhysicsEngine::GetGravity()
	{
		return GRAVITY;
	}

	void PhysicsEngine::SetGravity(const vec2 grav)
	{
		this->GRAVITY = grav;
	}

	void PhysicsEngine::SetNumberTimeSteps(const int TimeSteps)
	{
		this->TimeSteps = TimeSteps;
	}

	int PhysicsEngine::GetNumberTimeSteps()
	{
		return this->TimeSteps;
	}

	uuid PhysicsEngine::AddObjectAABB(vec2 position, vec2 dimension, vec2 initialVelocity, Material material)
	{
		uuid uuid = generateUUIDv4();
		keys.push_back(uuid);
		PhysicsBody* body = new PhysicsBody();
		CreateAABB(body, position, dimension, initialVelocity, material);
		body->id = uuid;
		bodies.push_back(body);
		objects[uuid] = body;
		return uuid;
	}

	uuid PhysicsEngine::AddObjectCircle(vec2 position, double radius, vec2 initialVelocity, Material material)
	{
		uuid uuid = generateUUIDv4();
		keys.push_back(uuid);
		PhysicsBody* body = new PhysicsBody();
		CreateCircle(body, position, radius, initialVelocity, material);
		body->id = uuid;
		bodies.push_back(body);
		objects[uuid] = body;
		return uuid;
	}

	uuid PhysicsEngine::AddObjectPolygon(vec2 position, double radius, unsigned int numberPoints, vec2 initialVelocity, Material material)
	{
		uuid uuid = generateUUIDv4();
		keys.push_back(uuid);
		PhysicsBody* body = new PhysicsBody();
		CreatePolygon(body, position, radius, numberPoints, initialVelocity, material);
		body->id = uuid;
		bodies.push_back(body);
		objects[uuid] = body;
		return uuid;
	}

	uuid PhysicsEngine::AddPhysicsBody(PhysicsBody* body)
	{
		uuid uuid = generateUUIDv4();
		keys.push_back(uuid);
		body->id = uuid;
		bodies.push_back(body);
		objects[uuid] = body;
		return uuid;
	}

	void PhysicsEngine::DeletePhysicsBody(uuid key)
	{
		std::unordered_map<uuid, PhysicsBody*>::iterator itr = objects.find(key);
		if (itr == objects.end()) return;
		delete itr->second;
		objects.erase(itr);
	}

	PhysicsBody* PhysicsEngine::GetPhysicsBody(uuid key)
	{/*
		auto itr = objects.find(key);
		if (itr == objects.end())
			return nullptr;
		return itr->second;*/
		for (PhysicsBody* body : bodies)
		{
			if (body->id == key) return body;
		}
		return nullptr;
	}
	std::vector<PhysicsBody*> PhysicsEngine::GetPhysicBodies()
	{/*
		std::vector<PhysicsBody*> bodies;
		for (const auto& pair : objects)
			bodies.push_back(pair.second);*/
		return bodies;
	}
	void PhysicsEngine::update(float deltaTime)
	{
		for (int k = 0; k < TimeSteps; k++)
		{
			for (unsigned int i = 0; i < bodies.size(); i++)
			{
				PhysicsBody* body = bodies[i];

				updatePhysicsBody(body,deltaTime,TimeSteps);

				for (unsigned int j = 0; j < bodies.size(); j++)
				{
					PhysicsBody* body2 = bodies[j];
					if (i == j || (body->massData.invMass + body->massData.invMass == 0)) continue;
					Manifold m = Collide(body, body2);
					if (m.collision)
					{
						ResolveCollision(m, body, body2);
						ResolveCollisionStatic(m, body, body2);
						ApplyFriction(m, body, body2);
					}
				}
			}
			/*for (const auto& key : keys)
			{
				PhysicsBody* object1 = objects[key];
				updatePhysicsBody(object1, deltaTime, TimeSteps);

				for (const auto& key2 : keys)
				{
					if (key == key2) continue;

					PhysicsBody* object2 = objects[key2];
					Manifold m = Collide(object1, object2);
					if (m.collision && (object1->massData.invMass + object2->massData.invMass != 0))
					{
						ResolveCollision(m, GetPhysicsBody(key), GetPhysicsBody(key2));
					}
				}
			}
			/*for (const auto& pair : objects)
			{
				PhysicsBody* object1 = pair.second;
				updatePhysicsBody(object1, deltaTime, TimeSteps);
				
				//std::cout << getPosition(body) << " " << body->velocity << "\n";
				//constrainPhysicsBody(body, vec2(0, 0), vec2(1000, 800));

				//std::cout << deltaTime << "\n";
				//std::cout << pair.first << " " << getPosition(body) << "\n";
				//std::cout << body->color << "\n";

				for (const auto& pair2 : objects)
				{
					if (pair.first == pair2.first || (!pair.second->movable && !pair2.second->movable))
					{
						//std::cout << pair.first << " same " << pair2.first << "\n";
						continue;
					}
					PhysicsBody* body2 = pair2.second;
					Manifold m = Collide(object1, body2);
					if (m.collision) //&& (body->massData.invMass + body2->massData.invMass != 0))
					{
						std::cout << m.normal << " " << m.penetration << "\n";
						//std::cout << "test\n";
						//ResolveCollisionStatic(m, body, body2);
						ResolveCollision(m, object1, body2);
						//ApplyFriction(m, body, body2);
					}
				}
			}*/
		}
	}
}