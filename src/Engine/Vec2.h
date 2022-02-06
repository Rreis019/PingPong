
#pragma once
#include <math.h>

#define PI 3.14159265
#define ToRadians(angle) angle * PI / 180
#define ToDegrees(angle) angle * 180 / PI

class Vec2
{
public:
	float x, y;
	Vec2()
	{
		x = y = -1;
	}

	Vec2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vec2 operator+(Vec2 arg)
	{
		Vec2 result;
		result.x = x + arg.x;
		result.y = y + arg.y;
		return result;
	}

	Vec2& operator+= (Vec2 arg)
	{
		x += arg.x;
		y += arg.y;
		return *this;
	}

	Vec2 operator-(Vec2 arg)
	{
		Vec2 result;;
		result.x = x - arg.x;
		result.y = y - arg.y;
		return result;
	}

	Vec2& operator-=(Vec2 arg)
	{
		x -= arg.x;
		y -= arg.y;
		return *this;
	}

	Vec2 operator*(int arg)
	{
		Vec2 result;
		result.x = x * arg;
		result.y = y * arg;
		return result;
	}

	Vec2 operator*(float arg)
	{
		Vec2 result;
		result.x = x * arg;
		result.y = y * arg;
		return result;
	}

	Vec2 operator/(float arg)
	{
		Vec2 result;
		result.x = x * arg;
		result.y = y * arg;
		return result;
	}


	Vec2& operator*=(int arg)
	{
		x *= arg;
		y *= arg;
		return *this;
	}

	//return angle of x,y 
    static double getAngle(double x, double y)
    {
        double ret = atan2(y, x);
        ret = ToDegrees(ret);
        return ret;
    }

    //return x,y between 0 and 1 with determined angle
    static Vec2 forward(double angle)
    {
        angle = ToRadians(angle);
		Vec2 ret = Vec2(cos(angle) , sin(angle));
        return ret;
    }

	//https://www.youtube.com/watch?v=_vQxRRqbUHY
	static Vec2 rotate(Vec2 &origin, Vec2& pos,float angle)
	{
		angle = ToRadians(angle);
		Vec2 rotated;
		Vec2 delta = pos - origin;

		rotated.x = delta.x * cos(angle) - delta.y * sin(angle);
		rotated.y = delta.x * sin(angle) + delta.y * cos(angle); 
		rotated += origin;
		return rotated;
	}

	//return  vector with lenght(hypotenuse) to 1
	//normaly called unit vector
	void normalize()
	{
		float lenght = this->lenght();
		x /= lenght;
		y /= lenght;
	}

	//cross product
	float cross(Vec2 arg)
	{
		return x * arg.y - y * arg.x;
	}

	//dot product
	float dot(Vec2 arg)
	{
		return x * arg.x + y * arg.y;
	}

	//Calculate hypotenuse of a triangle
	float lenght()
	{
		return sqrtf(x * x + y * y);
	}

	static float distance(Vec2 a, Vec2 b)//Distancia fica no DeltaZ
	{
		Vec2 Delta = a - b;
		return  Delta.lenght();
	}
};