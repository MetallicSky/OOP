#pragma once

#include "windows.h"
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

const double PI = 3.141592653589793238463;

using namespace std;

struct customCOORD
{
	float X;
    float Y;
};

float getLength(customCOORD A, customCOORD B)
{
	return sqrt(pow((A.X - B.X), 2) + pow((A.Y - B.Y), 2));
}

class Shape
{
protected:
	vector<customCOORD> dots;
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
            int floatToInt = dots[i].X;
            str += to_string(floatToInt);
			str += "; ";
            floatToInt = dots[i].Y;
            str += to_string(floatToInt);
            str += ") ";
		}
		return str;
	}
};

class Circle : public Shape
{
	float radius;
public:
	Circle(customCOORD center, customCOORD rad)
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
	Square(customCOORD bottomLeft, customCOORD topRight)
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
	Rect(customCOORD bottomLeft, customCOORD topRight)
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
	Triangle(customCOORD p1, customCOORD p2, customCOORD p3)
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

class ShapeCollector
{
	vector<Shape*> shapes;

	Shape* minAreaShape;
	Shape* maxAreaShape;
	Shape* minPerimeterShape;
	Shape* maxPerimeterShape;
	float totalArea;
    float totalPerimeter;
public:
	ShapeCollector()
	{
		minAreaShape = nullptr;
		maxAreaShape = nullptr;
		minPerimeterShape = nullptr;
		maxPerimeterShape = nullptr;
		totalArea = 0;
		totalPerimeter = 0;
	}

	void add(Shape* shape)
	{
		shapes.push_back(shape);
		totalArea += shape->findArea();
		totalPerimeter += shape->findPerim();

		if (shapes.size() == 1)
		{
			minAreaShape = shape;
			maxAreaShape = shape;
			minPerimeterShape = shape;
			maxPerimeterShape = shape;
			return;
		}

		if (minAreaShape->findArea() > shape->findArea())
			minAreaShape = shape;
		else if (maxAreaShape->findArea() < shape->findArea())
			maxAreaShape = shape;

		if (minPerimeterShape->findArea() > shape->findPerim())
			minPerimeterShape = shape;
		else if (maxPerimeterShape->findArea() < shape->findPerim())
			maxPerimeterShape = shape;
	}

	void addAll(vector<Shape*> adding)
	{
		for (int i = 0; i < adding.size(); i++)
			add(adding[i]);
	}

	Shape* getMaxAreaShape()
	{
		return maxAreaShape;
	}

	Shape* getMinAreaShape()
	{
		return minAreaShape;
	}

	Shape* getMaxPerimeterShape()
	{
		return maxPerimeterShape;
	}

	Shape* getMinPerimeterShape()
	{
		return minPerimeterShape;
	}

	float getTotalArea()
	{
		return totalArea;
	}

	float getTotalPerimeter()
	{
		return totalPerimeter;
	}

	int size()
	{
		return shapes.size();
	}

	Shape* operator [] (int i)
	{
		return shapes[i];
	}
};
