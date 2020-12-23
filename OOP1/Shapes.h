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
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;
using customCOORD = struct customCOORD { float X; float Y; };
const double PI = 3.141592653589793238463;

using namespace std;

float getLength(customCOORD A, customCOORD B)
{
	return sqrt(pow((A.X - B.X), 2) + pow((A.Y - B.Y), 2));
}

class Shape
{
protected:

	void parse_points(pt::ptree* obj, std::vector<customCOORD>& arr) {
		pt::ptree all_arr;
		for (auto i = 0; i < arr.size(); ++i) {
			pt::ptree points_arr;
			for (auto j = 0; j < 2; ++j) {
				pt::ptree point_arr;
				j == 0 ? point_arr.put_value(arr[i].X) : point_arr.put_value(arr[i].Y);
				points_arr.push_back(std::make_pair("", point_arr));
			}
			all_arr.push_back(std::make_pair("", points_arr));
		}
		obj->add_child("points_arr", all_arr);
	}

	void unparse_points(pt::ptree* obj, std::vector<customCOORD>& arr) {
		auto i = 0, j = 0;
		for (pt::ptree::value_type& point : obj->get_child("points_arr")) {
			customCOORD c1;
			for (pt::ptree::value_type& dot : point.second) {
				j == 0 ? c1.X = dot.second.get_value<double>() : c1.Y = dot.second.get_value<double>();
				++j;
			}
			arr.push_back(c1);
			j = 0;
			++i;
		}
	};
	vector<customCOORD> dots;
public:
	virtual void parse(pt::ptree* obj) = 0;
	virtual void unparse(pt::ptree* obj) = 0;
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
	void unparse(pt::ptree* obj) override {
		this->radius = obj->get<double>("radius");
		unparse_points(obj, this->dots);
	}
	void parse(pt::ptree* obj) override {
		pt::ptree circle_info;
		circle_info.put("radius", radius);
		parse_points(&circle_info, dots);
		obj->add_child("circle", circle_info);
	}
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
	void parse(pt::ptree* obj) override {
		pt::ptree square_info;
		pt::ptree all_arr;
		square_info.put("edge_len", a);
		parse_points(&square_info, dots);
		obj->add_child("square", square_info);
	}
	void unparse(pt::ptree* obj) override {
		this->a = obj->get<double>("edge_len");
		unparse_points(obj, this->dots);
	}
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
	void parse(pt::ptree* obj) override {
		pt::ptree rectanlge_info;
		rectanlge_info.put("first_edge_len", a);
		rectanlge_info.put("second_edge_len", b);
		parse_points(&rectanlge_info, dots);
		obj->add_child("rectangle", rectanlge_info);
	}
	void unparse(pt::ptree* obj) override {
		this->a = obj->get<double>("first_edge_len");
		this->b = obj->get<double>("second_edge_len");
		unparse_points(obj, this->dots);
	}
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
	void parse(pt::ptree* obj)  override {
		pt::ptree triangle_info;
		triangle_info.put("FirstSecond", a);
		triangle_info.put("FirstThird", b);
		triangle_info.put("SecondThird", c);
		parse_points(&triangle_info, dots);
		obj->add_child("triangle", triangle_info);
	}
	void unparse(pt::ptree* obj) override {
		this->a = obj->get<double>("FirstSecond");
		this->b = obj->get<double>("FirstThird");
		this->c = obj->get<double>("SecondThird");
		unparse_points(obj, this->dots);
	}
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
	void parse(std::string file_name) {
		std::fstream file;
		file.open(file_name, std::ios_base::out);
		if (file.fail()) {
			throw std::invalid_argument("Can't open file");
		}
		pt::ptree json_obj;
		for (auto i : shapes) {
			i->parse(&json_obj);
		}
		pt::write_json(file, json_obj);
	}

	void unparse(std::string file_name) {
		std::fstream file;
		file.open(file_name, std::ios_base::in);
		if (file.fail()) {
			throw std::invalid_argument("Can't open file");
		}
		pt::ptree objects;
		pt::read_json(file, objects);
		if (objects.empty()) {
			throw std::invalid_argument("Incorrect JSON structure");
		}
		for (pt::ptree::const_iterator iter = objects.begin(); iter != objects.end(); ++iter) {
			if (iter->first == "circle") {
				Circle* circle(new Circle);
				pt::ptree a;
				a = iter->second;
				circle->unparse(&a);
				this->add(circle);
			}
			else if (iter->first == "triangle") {
				Triangle* triangle(new Triangle);
				pt::ptree a;
				a = iter->second;
				triangle->unparse(&a);
				this->add(triangle);
			}
			else if (iter->first == "rectangle") {
				Rect* rectangle(new Rect);
				pt::ptree a;
				a = iter->second;
				rectangle->unparse(&a);
				this->add(rectangle);
			}
			else if (iter->first == "square") {
				Square* square(new Square);
				pt::ptree a;
				a = iter->second;
				square->unparse(&a);
				this->add(square);
			}
			else {
				throw std::invalid_argument("Invalid figure");
			}
		}
	}
};