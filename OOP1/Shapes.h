#pragma once

#include "windows.h"
#include <math.h>
#include <iostream>
#include <string>
#include <vector>

const double PI = 3.141592653589793238463;

using namespace std;

float getLength(COORD A, COORD B)
{
	return sqrt(pow((A.X - B.X), 2) + pow((A.Y - B.Y), 2));
}

class Shape
{
protected:

	vector<COORD> dots;
public:

	virtual float findArea()
	{
		return 0;
	}

	/// <summary>
	/// ¬ычисл€ет периметр фигуры
	/// </summary>
	/// <returns></returns>
	virtual float findPerim()
	{
		return 0;
	}

	/// <summary>
	/// ¬ыводит координаты образующих фигуру точек в виде (X; Y)\n
	/// </summary>
	/// <returns></returns>
	string toString()
	{
		string str;
		for (int i = 0; i < dots.size(); i++)
		{
			str += "(";
			str += to_string(dots[i].X);
			str += "; ";
			str += to_string(dots[i].Y);
			str += ")\n";
		}
		return str;
	}
};

class Circle : public Shape
{
	float radius;
public:
	Circle(COORD center, COORD rad)
	{
		dots = { center, rad };
		radius = getLength(dots[0], dots[1]);
	}

	float findArea() override
	{
		return PI * pow(radius, 2);
	}

	float findPerim() override
	{
		return 2 * PI * radius;
	}
};

class Square : public Shape
{
	float a;

public:
	Square(COORD bottomLeft, COORD topRight)
	{
		dots = { bottomLeft, topRight };
		a = abs(dots[1].X - dots[0].X);
	}

	float findArea() override
	{
		return pow(a, 2);
	}

	float findPerim() override
	{
		return 4 * a;
	}
};

class Rect : public Shape
{
	float a;
	float b;
public:
	Rect(COORD bottomLeft, COORD topRight)
	{
		dots = { bottomLeft, topRight };
		a = abs(dots[1].X - dots[0].X);
		b = abs(dots[1].Y - dots[0].Y);
	}

	float findArea() override
	{
		return a * b;
	}

	float findPerim() override
	{
		return 2 * (a + b);
	}
};

class Triangle : public Shape
{
	float a;
	float b;
	float c;

public:
	Triangle(COORD p1, COORD p2, COORD p3)
	{
		dots = { p1, p2, p3 };
		a = getLength(dots[0], dots[1]);
		b = getLength(dots[1], dots[2]);
		c = getLength(dots[2], dots[0]);
	}

	float findArea() override
	{
		float p = findPerim() / 2;
		return sqrt(p * (p - a) * (p - b) * (p - c));
	}

	float findPerim() override
	{
		return a + b + c;
	}
};