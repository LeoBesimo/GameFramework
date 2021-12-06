#pragma once

#define _CRTDBG_MAP_ALLOC

#include<iostream>

#include <crtdbg.h>

#ifdef _DEBUG

#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)

#define new DEBUG_NEW

#endif


#include <cmath>
#include <vector>
#include <iostream>

namespace lge
{	
//constants
const float QUARTER_PI = (float) 0.78539816339;
const float HALF_PI = (float) 1.570796326795;
const float PI = (float) 3.14159265359;
const float TWO_PI = (float) 6.28318530718;

//define datatypes
	struct vec2D 
	{ 
		double x = 0;
		double y = 0;

		vec2D(double x = 0, double y = 0) :
			x(x), y(y)
		{}

		void set(double x_, double y_)
		{
			x = x_;
			y = y_;
		}

		vec2D operator-(void) const
		{
			return vec2D(-x, -y);
		}

		vec2D operator-(const vec2D& a) const
		{
			return vec2D(x - a.x, y - a.y);
		}

		vec2D operator-(double a) const
		{
			return vec2D(x - a, y - a);
		}
		
		vec2D operator+(void) const
		{
			return vec2D(+x, +y);
		}

		vec2D operator+(const vec2D& a) const
		{
			return vec2D(x + a.x, y + a.y);
		}

		vec2D operator+(double a) const
		{
			return vec2D(x + a, y + a);
		}

		vec2D operator*(const vec2D& a) const
		{
			return vec2D(x * a.x, y * a.y);
		}

		vec2D operator*(double a) const
		{
			return vec2D(x * a, y * a);
		}

		vec2D operator/(const vec2D& a) const
		{
			return vec2D(x / a.x, y / a.y);
		}

		vec2D operator/(double a) const
		{
			return vec2D(x / a, y / a);
		}

		void operator-=(const vec2D& a)
		{
			x -= a.x;
			y -= a.y;
		}

		void operator+=(const vec2D& a)
		{
			x += a.x;
			y += a.y;
		}

		void operator*=(const vec2D& a)
		{
			x *= a.x;
			y *= a.y;
		}

		void operator/=(const vec2D& a)
		{
			x /= a.x;
			y /= a.y;
		}

		double LenSqr(void) const
		{
			return x * x + y * y;
		}

		double Len(void) const
		{
			return std::sqrt(x * x + y * y);
		}

		void Normalize(void)
		{
			double len = Len();
		
			if (len == 0) return;

			double invLen = 1.0 / len;

			x *= invLen;
			y *= invLen;
		}

	};
	
	typedef struct _vertex
	{ 
		float x1 = 0;
		float y1 = 0;
		float x2 = 0;
		float y2 = 0; 
	} vertex;

	//checks if object is instance of some class
	template<typename Base, typename T>
	inline bool instanceof(const T*)
	{
		return std::is_base_of<Base, T>::value;
	}

	//checks if point is inside AABB
	inline bool contains(float x1, float y1 , float x2 , float y2, float x3, float y3)
	{
		if (x3 < x1 || x3 > x2 || y3 < y1 || y3 > y2)
			return false;
		else
			return true;
	}

	inline bool contains(vec2D pos1, vec2D pos2, vec2D pos3)
	{
		if (pos3.x < pos1.x || pos3.x > pos2.x || pos3.y < pos1.y || pos3.y > pos2.y)
			return false;
		else
			return true;
	}

	//Calculates angle between 2 points
	inline float calcAngle(float x1, float y1, float x2, float y2)
	{
		float xdiff = x2 - x1;
		float ydiff = y2 - y1;
		float ang = atan2(ydiff, xdiff);
		return ang;
	}

	inline float calcAngle(vec2D v1, vec2D v2)
	{
		float xdiff = v2.x - v1.x;
		float ydiff = v2.y - v1.y;
		float ang = atan2(ydiff, xdiff);
		return ang;
	}

	inline float calcAngle(vertex v)
	{
		float xdiff = v.x2 - v.x1;
		float ydiff = v.y2 - v.y1;
		float ang = atan2(ydiff, xdiff);
		return ang;
	}

	// map value from old range to new range
	inline float map(float val, float oldMin, float oldMax, float newMin, float newMax)
	{
		float result = newMin + (newMax - newMin) * ((val - oldMin) / (oldMax - oldMin));
		return result;
	}


	//Degrees to radians
	inline float radians(float val)
	{
		return val * PI / 180;
	}

	//radians to degrees
	inline float degrees(float val)
	{
		return val * 180.0f / PI;
	}


	//calculate distance between 2 points
	inline float dist(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		float d = sqrt((x * x) + (y * y));
		return d;

	}

	inline float dist(vec2D pos1, vec2D pos2)
	{
		float x = pos2.x - pos1.x;
		float y = pos2.y - pos1.y;

		float d = sqrt(x * x + y * y);
		return d;
	}


	//constrain a value between a minimum and a maximum
	inline float constrain(float val, float min, float max)
	{
		if (val < min) 
		{
			val = min;
		}
		else if (val > max)
		{
			val = max;
		}
		
		return val;
	}

	// PhysicsObject

	class PhysicsObject
	{
	private:

		vec2D pos;
		vec2D dim;

		float ang;
		float sides;
		float rad;

		std::string type;

		std::vector<vec2D> points;

		void calcPoints()
		{
			this->points.clear();
			if (this->type == "quad")
			{
				float radius = sqrt((dim.x * dim.x) + (dim.y * dim.y)) / 2;

				float px = pos.x + radius * cos(acos((this->dim.x / 2) / radius) + PI + this->ang);
				float py = pos.y + radius * sin(acos((this->dim.x / 2) / radius) + PI + this->ang);

				float tempX = px + dim.x * cos(this->ang);
				float tempY = py + dim.x * sin(this->ang);

				vec2D point1 = { px,py };
				vec2D point2 = { tempX, tempY };
				vec2D point3 = { tempX + dim.y * cos(this->ang + PI / 2), tempY + dim.y * sin(this->ang + PI / 2) };
				vec2D point4 = { px + dim.y * cos(this->ang + PI / 2), py + dim.y * sin(this->ang + PI / 2) };

				this->points.push_back(point1);
				this->points.push_back(point2);
				this->points.push_back(point3);
				this->points.push_back(point4);
			}
			else
			{
				float theta = TWO_PI / this->sides;
				for (unsigned int i = 0; i < this->sides; i++)
				{
					float x = this->pos.x + this->rad * cos(theta * i + this->ang);
					float y = this->pos.y + this->rad * sin(theta * i + this->ang);
					vec2D point = { x, y };
					this->points.push_back(point);
				}

			}

		}

		void updatePoints(float x, float y)
		{
			for (unsigned int i = 0; i < this->points.size(); i++)
			{
				this->points[i].x += x;
				this->points[i].y += y;
			}

		}

	public:

		PhysicsObject() {
			this->sides = 0;
			this->rad = 0;
			this->ang = 0;
		}

		PhysicsObject(float x, float y, float sides, float rad, float ang, std::string type)
		{
			this->pos = { x,y };
			this->ang = ang;
			if (type == "quad" || type == "QUAD" || type == "Quad")
			{
				this->type = type;
				this->dim = { sides,rad };
			}
			else
			{
				this->type = type;
				this->sides = sides;
				this->rad = rad;
			}
			this->calcPoints();
		}

		~PhysicsObject() {}

		vec2D getPos()
		{
			return this->pos;
		}

		std::vector<vec2D> getPoints()
		{
			return this->points;
		}

		std::string getType()
		{
			return this->type;
		}

		float getRad()
		{
			return this->rad;
		}

		float getSides()
		{
			return this->sides;
		}

		vec2D getDim()
		{
			return this->dim;
		}

		void move(float x, float y)
		{
			this->pos.x += x;
			this->pos.y += y;
			this->updatePoints(x, y);
		}

		void setPos(float x, float y)
		{
			float xdiff = x - this->pos.x;
			float ydiff = y - this->pos.y;
			pos = { x,y };
			//this->updatePoints(xdiff, ydiff);
			this->calcPoints();
		}

		void setDim(float w, float h)
		{
			if (this->type == "quad")
			{
				dim = { w,h };
				this->calcPoints();
			}
		}

		void setAng(float val)
		{
			this->ang = val;
			this->calcPoints();
		}

	};

	//Physics Engine


	class PhysicsEngine
	{
	public:
		PhysicsEngine() {}
		~PhysicsEngine() {}

		bool polygonCollision(PhysicsObject p1, PhysicsObject p2)
		{
			PhysicsObject poly1 = p1;
			PhysicsObject poly2 = p2;

			for (unsigned int shape = 0; shape < 2; shape++)
			{

				if (shape == 1)
				{
					poly1 = p2;
					poly2 = p1;
				}

				for (unsigned int p = 0; p < poly1.getPoints().size(); p++)
				{
					vec2D line_p1s = poly1.getPos();
					vec2D line_p1e = poly1.getPoints()[p];

					for (unsigned int q = 0; q < poly2.getPoints().size(); q++) 
					{
						vec2D line_p2s = poly2.getPoints()[q];
						vec2D line_p2e = poly2.getPoints()[(q + 1) % poly2.getPoints().size()];

						float den = (line_p2e.x - line_p2s.x) * (line_p1s.y - line_p1e.y) - (line_p1s.x - line_p1e.x) * (line_p2e.y - line_p2s.y);

						float u = ((line_p2s.y - line_p2e.y) * (line_p1s.x - line_p2s.x) + (line_p2e.x - line_p2s.x) * (line_p1s.y - line_p2s.y)) / den;
						float t = ((line_p1s.y - line_p1e.y) * (line_p1s.x - line_p2s.x) + (line_p1e.x - line_p1s.x) * (line_p1s.y - line_p2s.y)) / den;

						if (0 <= t && t < 1 && 0 <= u && u < 1)
						{
							return true;
						}
					}
				}
			}
			return false;
		}

		PhysicsObject polygonCollision_Static(PhysicsObject p1, PhysicsObject p2)
		{
			PhysicsObject poly1 = p1;
			PhysicsObject poly2 = p2;

			for (unsigned int shape = 0; shape < 2; shape++)
			{

				if (shape == 1)
				{
					poly1 = p2;
					poly2 = p1;
				}

				for (unsigned int p = 0; p < poly1.getPoints().size(); p++)
				{
					vec2D line_p1s = poly1.getPos();
					vec2D line_p1e = poly1.getPoints()[p];

					vec2D displacement = { 0,0 };

					for (unsigned int q = 0; q < poly2.getPoints().size(); q++)
					{
						vec2D line_p2s = poly2.getPoints()[q];
						vec2D line_p2e = poly2.getPoints()[(q + 1) % poly2.getPoints().size()];

						float den = (line_p2e.x - line_p2s.x) * (line_p1s.y - line_p1e.y) - (line_p1s.x - line_p1e.x) * (line_p2e.y - line_p2s.y);

						float u = ((line_p2s.y - line_p2e.y) * (line_p1s.x - line_p2s.x) + (line_p2e.x - line_p2s.x) * (line_p1s.y - line_p2s.y)) / den;
						float t = ((line_p1s.y - line_p1e.y) * (line_p1s.x - line_p2s.x) + (line_p1e.x - line_p1s.x) * (line_p1s.y - line_p2s.y)) / den;

						if (0 <= t && t < 1 && 0 <= u && u < 1)
						{
							displacement.x += (1.0f - u) * (line_p1e.x - line_p1s.x);
							displacement.y += (1.0f - u) * (line_p1e.y - line_p1s.y);
						}
					}

					float x = p1.getPos().x + displacement.x * (shape == 0 ? -1 : 1);
					float y = p1.getPos().y + displacement.y * (shape == 0 ? -1 : 1);
					p1.move(displacement.x * (shape == 0 ? -1 : 1), displacement.y * (shape == 0 ? -1 : 1));
					//p1.setPos(x, y);
				}
			}
			return p1;
		}

		bool checkCollisionCircle(vec2D pos1, float rad1, vec2D pos2, float rad2)
		{
			return dist(pos1, pos2) < (rad1 + rad2);
		}

		vec2D lineLineIntersection(vec2D a, vec2D b, vec2D c, vec2D d)
		{
			float x1 = a.x;
			float y1 = a.y;
			float x2 = b.x;
			float y2 = b.y;

			float x3 = c.x;
			float y3 = c.y;
			float x4 = d.x;
			float y4 = d.y;

			float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

			if (den == 0)
			{
				return { NULL,NULL };
			}

			float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
			float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

			if (0 < t && t < 1 && 0 < u && u < 1)
			{
				float x = x1 + t * (x2 - x1);
				float y = y1 + t * (y2 - y1);
				return { x,y };
			}
			else
			{
				return { NULL,NULL };
			}
		}

		vec2D lineLineIntersection(vertex a, vertex b)
		{
			float x1 = a.x1;
			float y1 = a.y1;
			float x2 = a.x2;
			float y2 = a.y2;

			float x3 = b.x1;
			float y3 = b.y1;
			float x4 = b.x2;
			float y4 = b.y2;

			float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
			std::cout << "den: " << den << "\n";
			if (den == 0)
			{
				return { NULL,NULL } ;
			}

			float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
			float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

			if (0 <= t && t < 1 && 0 <= u && u < 1)
			{
				float x = x1 + t * (x2 - x1);
				float y = y1 + t * (y2 - y1);
				//std::cout << x << " " << y << " " << t  << " " << u <<"\n";
				return { x,y };
			}
			else 
			{
				return { NULL,NULL };
			}
		}



		bool checkCollisionRect(PhysicsObject a, PhysicsObject b)
		{
			vec2D aPos = a.getPos();
			vec2D aDim = a.getDim();

			vec2D bPos = b.getPos();
			vec2D bDim = b.getDim();

			if(aPos.x + aDim.x / 2 < bPos.x - bDim.x / 2 || aPos.x - aDim.x / 2 > bPos.x + bDim.x / 2 || aPos.y + aDim.y / 2 < bPos.y - bDim.y / 2 || aPos.y - aDim.y /2 > bPos.y + bDim.y / 2)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		
	};
	/*
	class PVector
	{
	public:

		float x = 0;
		float y = 0;
		float z = 0;

		PVector() {}

		PVector(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		PVector(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		~PVector() {}

		float mag()
		{
			return sqrt(x * x + y * y);
		}

		float heading()
		{
			float ang = atan2(y, x);
			return ang;
		}

		float angleBetween(PVector p)
		{
			float xdiff = p.x - this->x;
			float ydiff = p.y - this->y;
			float ang = atan2(ydiff, xdiff);
			return ang;
		}

		PVector set(float x, float y)
		{
			this->x = x;
			this->y = y;
			this->z = 0;
			return PVector(this->x, this->y,this->z);
		}

		PVector set(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			return PVector(this->x, this->y, this->z);
		}

		PVector cross(PVector v)
		{
			return cross(v, PVector(NULL, NULL, NULL));
		}

		PVector cross(PVector v, PVector target) 
		{

			float crossX = y * v.z - v.y * z;
			float crossY = z * v.x - v.z * x;
			float crossZ = x * v.y - v.x * y;

			if (target.x == NULL && target.y == NULL && target.z == NULL)
			{
				target = PVector(crossX, crossY, crossZ);
			}
			else 
			{
				target.set(crossX, crossY, crossZ);
			}

			return target;
		}

		PVector normalize()
		{
			float m = this->mag();
			if (m != 0 && m != 1)
			{
				this->div(m);
			}
			return PVector(this->x, this->y);
		}

		PVector setMag(float len)
		{
			this->normalize();
			this->mult(len);
			return PVector(this->x, this->y);
		}

		PVector add(float val)
		{
			this->x += val;
			this->y += val;
			return PVector(this->x, this->y);
		}

		PVector add(float x, float y)
		{
			this->x += x;
			this->y += y;
			return PVector(this->x, this->y);
		}
		
		PVector add(PVector p)
		{
			this->x += p.x;
			this->y += p.y;
			return PVector(this->x, this->y);
		}

		PVector sub(float val)
		{
			this->x -= val;
			this->y -= val;
			return PVector(this->x, this->y);
		}

		PVector sub(float x, float y)
		{
			this->x -= x;
			this->y -= y;
			return PVector(this->x, this->y);
		}

		PVector sub(PVector p)
		{
			this->x -= p.x;
			this->y -= p.y;
			return PVector(this->x, this->y);
		}

		PVector mult(float val)
		{
			this->x *= val;
			this->y *= val;
			return PVector(this->x, this->y);
		}

		PVector mult(float x, float y)
		{
			this->x *= x;
			this->y *= y;
			return PVector(this->x, this->y);
		}

		PVector mult(PVector p)
		{
			this->x *= p.x;
			this->y *= p.y;
			return PVector(this->x, this->y);
		}

		PVector div(float val)
		{
			this->x /= val;
			this->y /= val;
			return PVector(this->x, this->y);
		}

		PVector div(float x, float y)
		{
			this->x /= x;
			this->y /= y;
			return PVector(this->x, this->y);
		}

		PVector div(PVector p)
		{
			this->x /= p.x;
			this->y /= p.y;
			return PVector(this->x, this->y);
		}
	};
	*/
}