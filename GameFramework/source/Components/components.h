#pragma once

#include <math.h>
#include <cmath>
#include <iostream>

const float QUARTER_PI = (float)0.78539816339;
const float HALF_PI = (float)1.570796326795;
const float PI = (float)3.14159265359;
const float TWO_PI = (float)6.28318530718;

//define datatypes

struct vec2
{
	double x = 0;
	double y = 0;

	vec2(double x = 0, double y = 0) :
		x(x), y(y)
	{}

	friend std::ostream& operator<<(std::ostream& os, const vec2& a)
	{
		return os << "X: " << a.x << " Y: " << a.y;
	}

	vec2 operator-(void) const
	{
		return vec2(-x, -y);
	}

	vec2 operator-(const vec2& a) const
	{
		return vec2(x - a.x, y - a.y);
	}

	vec2 operator-(double a) const
	{
		return vec2(x - a, y - a);
	}

	vec2 operator+(void) const
	{
		return vec2(+x, +y);
	}

	vec2 operator+(const vec2& a) const
	{
		return vec2(x + a.x, y + a.y);
	}

	vec2 operator+(double a) const
	{
		return vec2(x + a, y + a);
	}

	vec2 operator*(const vec2& a) const
	{
		return vec2(x * a.x, y * a.y);
	}

	vec2 operator*(double a) const
	{
		return vec2(x * a, y * a);
	}

	vec2 operator/(const vec2& a) const
	{
		return vec2(x / a.x, y / a.y);
	}

	vec2 operator/(double a) const
	{
		return vec2(x / a, y / a);
	}

	void operator-=(const vec2& a)
	{
		x -= a.x;
		y -= a.y;
	}

	void operator+=(const vec2& a)
	{
		x += a.x;
		y += a.y;
	}

	void operator*=(const double a)
	{
		x *= a;
		y *= a;
	}

	void operator*=(const vec2& a)
	{
		x *= a.x;
		y *= a.y;
	}

	void operator/=(const double a)
	{
		x /= a;
		y /= a;
	}

	void operator/=(const vec2& a)
	{
		x /= a.x;
		y /= a.y;
	}

	void set(double x_, double y_)
	{
		x = x_;
		y = y_;
	}

	double lenSqr(void) const
	{
		return x * x + y * y;
	}

	double len(void) const
	{
		return std::sqrt(x * x + y * y);
	}

	vec2 normalize(void)
	{
		double l = len();

		if (l == 0) return vec2(0,0);

		double invLen = 1.0 / l;

		x *= invLen;
		y *= invLen;

		return *this;
	}

	void limit(double limit)
	{
		if (limit > len()) {
			normalize();
			x *= limit;
			y *= limit;
		}
	}

};

struct vec3
{
	double x = 0;
	double y = 0;
	double z = 0;

	vec3(double x = 0, double y = 0, double z = 0) :
		x(x), y(y), z(z)
	{}

	friend std::ostream& operator<<(std::ostream& os, const vec3& a)
	{
		return os << "X: " << a.x << " Y: " << a.y << " Z: " << a.z;
	}

	vec3 operator-(void) const
	{
		return vec3(-x, -y, -z);
	}

	vec3 operator-(const vec3& a) const
	{
		return vec3(x - a.x, y - a.y, z - a.z);
	}

	vec3 operator-(double a) const
	{
		return vec3(x - a, y - a, z - a);
	}

	vec3 operator+(void) const
	{
		return vec3(+x, +y, + z);
	}

	vec3 operator+(const vec3& a) const
	{
		return vec3(x + a.x, y + a.y, z + a.z);
	}

	vec3 operator+(double a) const
	{
		return vec3(x + a, y + a, z + a);
	}

	vec3 operator*(const vec3& a) const
	{
		return vec3(x * a.x, y * a.y, z * a.z);
	}

	vec3 operator*(double a) const
	{
		return vec3(x * a, y * a, z * a);
	}

	vec3 operator/(const vec3& a) const
	{
		return vec3(x / a.x, y / a.y, z / a.z);
	}

	vec3 operator/(double a) const
	{
		return vec3(x / a, y / a, z / a);
	}

	void operator-=(const vec3& a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
	}

	void operator+=(const vec3& a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
	}

	void operator*=(const double a)
	{
		x *= a;
		y *= a;
		z *= a;
	}

	void operator*=(const vec3& a)
	{
		x *= a.x;
		y *= a.y;
		z *= a.z;
	}

	void operator/=(const double a)
	{
		x /= a;
		y /= a;
		z /= a;
	}

	void operator/=(const vec3& a)
	{
		x /= a.x;
		y /= a.y;
		z /= a.z;
	}

	void set(double x_, double y_, double z_)
	{
		x = x_;
		y = y_;
		z = z_;
	}

	double lenSqr()
	{
		return x * x + y * y + z * z;
	}

	double len()
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	vec3 normalize()
	{
		double l = len();

		if (l == 0) return vec3(0,0,0);

		double invLen = 1.0 / l;

		x *= invLen;
		y *= invLen;
		z *= invLen;

		return *this;
	}

	void limit(double limit)
	{
		if (limit > len())
		{
			normalize();
			x *= limit;
			y *= limit;
			z *= limit;
		}
	}
};

struct vec4
{
	double w = 0;
	double x = 0;
	double y = 0;
	double z = 0;

	vec4(double w, double x, double y, double z) :
		w(w), x(x), y(y), z(z)
	{}

	friend std::ostream& operator<<(std::ostream& os, const vec4& a)
	{
		return os << "W: "<< a.w << " X: " << a.x << " Y: " << a.y << " Z: " << a.z;
	}

	vec4 operator-(void) const
	{
		return vec4(-w, -x, -y, -z);
	}

	vec4 operator-(const vec4& a) const
	{
		return vec4(w - a.w, x - a.x, y - a.y, z - a.z);
	}

	vec4 operator-(double a) const
	{
		return vec4(w - a, x - a, y - a, z - a);
	}

	vec4 operator+(void) const
	{
		return vec4(+w, +x, +y, +z);
	}

	vec4 operator+(const vec4& a) const
	{
		return vec4(w + a.w, x + a.x, y + a.y, z + a.z);
	}

	vec4 operator+(double a) const
	{
		return vec4(w + a, x + a, y + a, z + a);
	}

	vec4 operator*(const vec4& a) const
	{
		return vec4(w * a.w, x * a.x, y * a.y, z * a.z);
	}

	vec4 operator*(double a) const
	{
		return vec4(w * a, x * a, y * a, z * a);
	}

	vec4 operator/(const vec4& a) const
	{
		return vec4(w / a.w, x / a.x, y / a.y, z / a.z);
	}

	vec4 operator/(double a) const
	{
		return vec4(w / a, x / a, y / a, z / a);
	}

	void operator-=(const vec4& a)
	{
		w -= a.w;
		x -= a.x;
		y -= a.y;
		z -= a.z;
	}

	void operator+=(const vec4& a)
	{
		w += a.w;
		x += a.x;
		y += a.y;
		z += a.z;
	}

	void operator*=(const double a)
	{
		w *= a;
		x *= a;
		y *= a;
		z *= a;
	}

	void operator*=(const vec4& a)
	{
		w *= a.w;
		x *= a.x;
		y *= a.y;
		z *= a.z;
	}

	void operator/=(const double a)
	{
		w /= a;
		x /= a;
		y /= a;
		z /= a;
	}

	void operator/=(const vec4& a)
	{
		w /= a.w;
		x /= a.x;
		y /= a.y;
		z /= a.z;
	}

	void set(double w_, double x_, double y_, double z_)
	{
		w = w_;
		x = x_;
		y = y_;
		z = z_;
	}

	double lenSqr()
	{
		return w * w + x * x + y * y + z * z;
	}

	double len()
	{
		return std::sqrt(w * w + x * x + y * y + z * z);
	}

	vec4 normalize()
	{
		double l = len();

		if (l == 0) return vec4(0,0,0,0);

		double invLen = 1.0 / l;

		w *= invLen;
		x *= invLen;
		y *= invLen;
		z *= invLen;

		return *this;
	}

	void limit(double limit)
	{
		if (limit > len())
		{
			normalize();
			w *= limit;
			x *= limit;
			y *= limit;
			z *= limit;
		}
	}
};

typedef struct _vertex
{
	vec2 p1;
	vec2 p2;
} vertex;

inline float calcInvSqRoot(float n) 
{

	const float threehalfs = 1.5F;
	float y = n;

	long i = *(long*)&y;

	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;

	y = y * (threehalfs - ((n * 0.5F) * y * y));
	y = y * (threehalfs - ((n * 0.5F) * y * y));

	return y;
}

inline int hash(int state)
{
	state ^= 2747636419u;
	state *= 2654435769u;
	state ^= state >> 16;
	state *= 2654435769u;
	state ^= state >> 16;
	state *= 2654435769u;
	return state;
}

inline double randomDouble(double min, double max)
{
	return (min)+((double)rand() / RAND_MAX) * (max - min);  // can change random2D().lenSqr() with rand() / RAND_MAX
}

inline vec2 random2D()
{
	return vec2(randomDouble(-1,1),randomDouble(-1,1)).normalize();//vec2(hash(rand()), hash(rand())).normalize();
}

inline vec2 signRandom2D()
{
	vec2 r = random2D();
	r.x = r.x < 0 ? r.x * -1 : r.x;
	r.y = r.y < 0 ? r.y * -1 : r.y;
	r.normalize();
	return r;
}

inline vec3 random3D()
{
	return vec3(hash(rand()), hash(rand()), hash(rand())).normalize();
}

inline vec4 random4D()
{
	return vec4(hash(rand()), hash(rand()), hash(rand()), hash(rand())).normalize();
}

inline float map(float val, float oldMin, float oldMax, float newMin, float newMax)
{
	return newMin + (newMax - newMin) * ((val - oldMin) / (oldMax - oldMin));
}

inline double constrain(double val, double min, double max)
{
	return val < min ? min : val > max ? max : val;
}

inline vec2 constrainvec2(vec2 vec, vec2 min, vec2 max) 
{
	vec.x = constrain(vec.x, min.x, max.x);
	vec.y = constrain(vec.y, min.y, max.y);
	return vec;
}

inline vec2 constrainvec2(vec2 vec, vertex limit) 
{
	return constrainvec2(vec, limit.p1, limit.p2);
}

inline double dotProduct(vec2 a, vec2 b)
{
	return a.x* b.x + a.y * b.y;
}

