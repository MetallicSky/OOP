#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

struct customCOORD
{
	float X;
	float Y;
};

const double PI = 3.141592653589793238463;

using namespace nlohmann;
using namespace std;

float getLength(customCOORD A, customCOORD B)
{
	return sqrt(pow((A.X - B.X), 2) + pow((A.Y - B.Y), 2));
}

namespace shapes
{
	enum shapeType
	{
		CircleT = 0,
		SquareT = 1,
		RectT = 2,
		TriangleT = 3
	};

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
		/// Вычисляет периметр фигуры
		/// </summary>
		/// <returns></returns>
		virtual float findPerim()
		{
			return 0;
		}

		/// <summary>
		/// Выводит координаты образующих фигуру точек в виде (X; Y)\n
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

		/// <summary>
		/// Выводит вектор c координатами
		/// </summary>
		/// <returns></returns>
		virtual vector<float> getCoords() = 0;

		/// <summary>
		/// нужно для конвертации
		/// </summary>
		/// <returns></returns>
		// virtual string convertToJson() = 0;

		/// <summary>
		/// Возвращает тип фигуры
		/// </summary>
		/// <returns></returns>
		virtual shapeType getType() = 0;
	};

	class Circle : public Shape
	{
		float radius;
	public:
		Circle() = default;
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

		virtual vector<float> getCoords() override
		{
			return vector<float>
			{
				dots[0].X,
					dots[0].Y,
					dots[1].X,
					dots[1].Y
			};
		}
		shapeType virtual getType() override
		{
			return shapeType::CircleT;
		}
		/*string virtual convertToJson()
		{
			return "Circledots[0].X:" + to_string(dots[0].X) + ",Circledots[0].Y:" + to_string(dots[0].Y) + ",Circledots[1].X:" + to_string(dots[1].X) + ",Circledots[1].Y:" + to_string(dots[1].Y) + ",";
		}*/
	};

	class Square : public Shape
	{
		float a;

	public:
		Square() = default;
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

		vector<float> getCoords() override
		{
			return vector<float>
			{
				dots[0].X,
					dots[0].Y,
					dots[1].X,
					dots[1].Y
			};
		}
		shapeType getType() override
		{
			return shapeType::SquareT;
		}
		/*string convertToJson()
		{
			return "Squaredots[0].X:" + to_string(dots[0].X) + ",Squaredots[0].Y:" + to_string(dots[0].Y) + ",Squaredots[1].X:" + to_string(dots[1].X) + ",Squaredots[1].Y:" + to_string(dots[1].Y) + ",";
		}*/
	};

	class Rect : public Shape
	{
		float a;
		float b;
	public:
		Rect() = default;
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

		vector<float> getCoords() override
		{
			return vector<float>
			{
				dots[0].X,
					dots[0].Y,
					dots[1].X,
					dots[1].Y
			};
		}
		shapeType getType() override
		{
			return shapeType::RectT;
		}
		/*string convertToJson()
		{
			return "Rectdots[0].X:" + to_string(dots[0].X) + ",Rectdots[0].Y:" + to_string(dots[0].Y) + ",Rectdots[1].X:" + to_string(dots[1].X) + ",Rectdots[1].Y:" + to_string(dots[1].Y) + ",";
		}*/
	};

	class Triangle : public Shape
	{
		float a;
		float b;
		float c;

	public:
		Triangle() = default;
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

		vector<float> getCoords() override
		{
			return vector<float>
			{
				dots[0].X,
					dots[0].Y,
					dots[1].X,
					dots[1].Y,
					dots[2].X,
					dots[2].Y
			};
		}
		shapeType getType() override
		{
			return shapeType::RectT;
		}
		/*string convertToJson()
		{
			return "Triangledots[0].X:" + to_string(dots[0].X) + ",Triangledots[0].Y:" + to_string(dots[0].Y) + ",Triangledots[1].X:" + to_string(dots[1].X) + ",Triangledots[1].Y:" + to_string(dots[1].Y) + ",";
		}*/
	};

	class ShapeCollector
	{
		vector<Shape*> shapes;

		float totalArea;
		float totalPerimeter;

	public:
		ShapeCollector()
		{
			totalArea = 0;
			totalPerimeter = 0;
		}

		void add(Shape* shape)
		{
			shapes.push_back(shape);
			totalArea += shape->findArea();
			totalPerimeter += shape->findPerim();
		}

		void addAll(vector<Shape*> adding)
		{
			for (int i = 0; i < adding.size(); i++)
				add(adding[i]);
		}

		Shape* getMaxAreaShape()
		{
			Shape* maxAreaShape;
			if (shapes.size() > 0)
				maxAreaShape = shapes[0];
			else
				return nullptr;

			for (int i = 0; i < shapes.size(); i++)
				if (shapes[i]->findArea() > maxAreaShape->findArea())
					maxAreaShape = shapes[i];

			return maxAreaShape;
		}

		Shape* getMinAreaShape()
		{
			Shape* minAreaShape;
			if (shapes.size() > 0)
				minAreaShape = shapes[0];
			else
				return nullptr;

			for (int i = 0; i < shapes.size(); i++)
				if (shapes[i]->findArea() < minAreaShape->findArea())
					minAreaShape = shapes[i];

			return minAreaShape;
		}

		Shape* getMaxPerimeterShape()
		{
			Shape* maxPerimeterShape;
			if (shapes.size() > 0)
				maxPerimeterShape = shapes[0];
			else
				return nullptr;

			for (int i = 0; i < shapes.size(); i++)
				if (shapes[i]->findArea() > maxPerimeterShape->findPerim())
					maxPerimeterShape = shapes[i];

			return maxPerimeterShape;
		}

		Shape* getMinPerimeterShape()
		{
			Shape* minPerimeterShape;
			if (shapes.size() > 0)
				minPerimeterShape = shapes[0];
			else
				return nullptr;

			for (int i = 0; i < shapes.size(); i++)
				if (shapes[i]->findArea() < minPerimeterShape->findPerim())
					minPerimeterShape = shapes[i];

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

	void parse(vector<Shape*> shapes)
	{
		ofstream ostream;
		ostream.open("out.json");
		if (!ostream.is_open())
		{
			ofstream ostream("out.json");
			ostream.open("out.json");
		}

		json jsonStream;
		jsonStream["vector"] = {};
		for (auto i = shapes.cbegin(); i != shapes.cend(); i++)
			jsonStream["vector"].push_back({ (*i)->getType(), (*i)->getCoords() });
		ostream << jsonStream;
	}

	vector<Shape*> unparse()
	{
		vector<Shape*> shapes;
		ifstream istream;
		istream.open("out.json");

		json jsonStream;
		istream >> jsonStream;
		for (auto element : jsonStream["vector"])
		{
			shapeType figure = *element.begin();
			switch (figure)
			{
			case shapeType::CircleT:
			{
				vector<float> parameters = (element.end() - 1)->get<vector<float>>();

				customCOORD c1;
				c1.X = parameters[0];
				c1.Y = parameters[1];

				customCOORD c2;
				c2.X = parameters[2];
				c2.Y = parameters[3];

				shapes.push_back(new Circle(c1, c2));
				break;
			}
			case shapeType::SquareT:
			{
				vector<float> parameters = (element.end() - 1)->get<vector<float>>();

				customCOORD c1;
				c1.X = parameters[0];
				c1.Y = parameters[1];

				customCOORD c2;
				c2.X = parameters[2];
				c2.Y = parameters[3];

				shapes.push_back(new Square(c1, c2));
				break;
			}
			case shapeType::RectT:
			{
				vector<float> parameters = (element.end() - 1)->get<vector<float>>();

				customCOORD c1;
				c1.X = parameters[0];
				c1.Y = parameters[1];

				customCOORD c2;
				c2.X = parameters[2];
				c2.Y = parameters[3];

				shapes.push_back(new Rect(c1, c2));
				break;
			}
			case shapeType::TriangleT:
			{
				vector<float> parameters = (element.end() - 1)->get<vector<float>>();

				customCOORD c1;
				c1.X = parameters[0];
				c1.Y = parameters[1];

				customCOORD c2;
				c2.X = parameters[2];
				c2.Y = parameters[3];

				customCOORD c3;
				c3.X = parameters[2];
				c3.Y = parameters[3];

				shapes.push_back(new Triangle(c1, c2, c3));
				break;
			}
			}
		}

		return shapes;
	}
}
