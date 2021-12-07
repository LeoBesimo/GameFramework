#pragma once

#include <math.h>
#include <cmath>
#include <iostream>

namespace lge
{
	const float QUARTER_PI = (float)0.78539816339;
	const float HALF_PI = (float)1.570796326795;
	const float PI = (float)3.14159265359;
	const float TWO_PI = (float)6.28318530718;

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

			if (l == 0) return vec2(0, 0);

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
			return vec3(+x, +y, +z);
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

			if (l == 0) return vec3(0, 0, 0);

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
			return os << "W: " << a.w << " X: " << a.x << " Y: " << a.y << " Z: " << a.z;
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

			if (l == 0) return vec4(0, 0, 0, 0);

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
}