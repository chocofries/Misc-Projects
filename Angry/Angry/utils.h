#pragma once
#include <algorithm>

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
#define SCREEN_SCALE 2.08

#define MATH_PI 3.14159265359f

enum CollideType
{
	COL_BALLS = 0x0001,
	COL_BOXES = 0x0002,
	COL_GROUND = 0x0003,
	COL_EFFECT = 0x0004
};

class Utils
{
public:

	//Clamps the value between a minimum and a maximum range
	template <typename T>
	static T Clamp(const T& var, const T& min, const T& max)
	{
		return std::max(min, std::min(var, max));
	}

	//Wraps the value between a minimum and a maximum range
	template <typename T>
	static T Wrap(const T& var, const T& min, const T& max)
	{
		T result = 0;
		if (var > max)
		{
			result = min;
		}
		else if (var < min)
		{
			result = max;
		}
		else
		{
			return (var);
		}
		return result;
	}

	//Finds the X component of a vector
	template <typename T>
	static T LengthDirX(const T& length, const T& direction)
	{
		return (length*cos(DegToRad(direction)));
	}

	//Finds the Y component of a vector
	template <typename T>
	static T LengthDirY(const T& length, const T& direction)
	{
		return (length*sin(DegToRad(direction)));
	}

	//Convert Degrees to Radians
	template <typename T>
	static T DegToRad(const T& degrees)
	{
		return ((degrees * MATH_PI) / 180.0f);
	}

	//Convert Radians to Degrees
	template <typename T>
	static T RadToDeg(const T& radians)
	{
		return ((radians * 180) / MATH_PI);
	}
};