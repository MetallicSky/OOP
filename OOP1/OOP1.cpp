#include "Matr.h"
#include "Shapes.h"
#include "Phonebook.h"

#include "windows.h"
#include <iostream>
#include <conio.h>
#include <vector>

using namespace std;

int main()
{
	// LAB1 LAB1 LAB1 LAB1 LAB1 LAB1 LAB1 LAB1 LAB1 LAB1 LAB1 LAB1

	/*Matrix<int> test1(3, 2);
	cout << "\ntest1: without value constructor:" << endl;
	cout << test1.toString();

	test1.randomise(0, 10);
	cout << "\ntest1: after randomise(0, 10):" << endl;
	cout << test1.toString();

	Matrix<int> test2(2, 3, 4);
	cout << "\ntest2: with value = 4 constructor:" << endl;
	cout << test2.toString();

	if (test1 == test2)
		cout << "\nequal matrices" << endl;
	if (test1 != test2)
		cout << "\nnon-equal matrices" << endl;

	Matrix<int> test3(test1);
	cout << "\ntest3: with copy (test1) constructor:" << endl;
	cout << test3.toString();

	test3 = test1 * test2;
	cout << "\ntest3: test3 = test1 * test2:" << endl;
	cout << test3.toString();

	test1 = test1 + test1;
	cout << "\ntest1: test1 = test1 + test1:" << endl;
	cout << test1.toString();

	test2 = test2 - test2;
	cout << "\ntest2: test2 = test2 - test2:" << endl;
	cout << test2.toString();

	test1 = test1 * 2;
	cout << "\ntest1: test1 = test1 * 2:" << endl;
	cout << test1.toString();

	test1 = test1 / 2;
	cout << "\ntest1: test1 = test1 / 2:" << endl;
	cout << test1.toString();

	Matrix<int> test4(4, 4);
	test4.randomise(-10, 10);
	cout << "\ntest4: new 4X4 matrix after randomise(-10, 10):" << endl;
	cout << test4.toString();
	cout << "\ntest4 det = " << test4.determinant() << endl;
	cout << endl;*/

	// LAB2 LAB2 LAB2 LAB2 LAB2 LAB2 LAB2 LAB2 LAB2 LAB2 LAB2 LAB2

	/*vector<Shape*> shapes;
	int minR = 0;
	int maxR = 10;
	for (int i = 0; i < 3; i++)
	{
		COORD center;
		center.X = rand() % (maxR - minR + 1) + minR;
		center.Y = rand() % (maxR - minR + 1) + minR;
		COORD radius = center;
		while (radius.X == center.X && radius.Y == center.Y)
		{
			radius.X = rand() % (maxR - minR + 1) + minR;
			radius.Y = rand() % (maxR - minR + 1) + minR;
		}

		shapes.push_back(new Circle(center, radius));
	}
	for (int i = 0; i < 3; i++)
	{
		COORD p1;
		p1.X = rand() % (maxR - minR + 1) + minR;
		p1.Y = rand() % (maxR - minR + 1) + minR;
		COORD p2 = p1;
		while (p2.X == p1.X && p2.Y == p1.Y)
		{
			p2.X = rand() % (maxR - minR + 1) + minR;
			p2.Y = p1.Y + abs(p2.X - p1.X);
		}

		shapes.push_back(new Square(p1, p2));
	}
	for (int i = 0; i < 3; i++)
	{
		COORD bottomLeft;
		bottomLeft.X = rand() % (maxR - minR + 1) + minR;
		bottomLeft.Y = rand() % (maxR - minR + 1) + minR;
		COORD topRight = bottomLeft;
		while (topRight.X == bottomLeft.X && topRight.Y == bottomLeft.Y)
		{
			topRight.X = rand() % (maxR - minR + 1) + minR;
			topRight.Y = rand() % (maxR - minR + 1) + minR;
		}

		shapes.push_back(new Rect(bottomLeft, topRight));
	}
	for (int i = 0; i < 3; i++)
	{
		COORD p1;
		p1.X = rand() % (maxR - minR + 1) + minR;
		p1.Y = rand() % (maxR - minR + 1) + minR;
		COORD p2 = p1;
		while (p1.X == p2.X && p1.Y == p2.Y)
		{
			p2.X = rand() % (maxR - minR + 1) + minR;
			p2.Y = rand() % (maxR - minR + 1) + minR;
		}
		COORD p3 = p1;
		while (p1.X == p3.X && p1.Y == p3.Y || (p2.X == p3.X && p2.Y == p3.Y))
		{
			p3.X = rand() % (maxR - minR + 1) + minR;
			p3.Y = rand() % (maxR - minR + 1) + minR;
		}

		shapes.push_back(new Triangle(p1, p2, p3));
	}
	int minP = 0;
	int maxP = 0;
	int minA = 0;
	int maxA = 0;
	float sumA = 0;
	for (int i = 0; i < shapes.size(); i++)
	{
		cout << typeid(*shapes[i]).name() << " " << i << ":\n";
		cout << shapes[i]->toString();
		cout << "P = " << shapes[i]->findPerim() << endl;
		if (shapes[i]->findPerim() > shapes[maxP]->findPerim())
			maxP = i;
		else if (shapes[i]->findPerim() < shapes[minP]->findPerim())
			minP = i;
		cout << "S = " << shapes[i]->findArea() << endl;
		if (shapes[i]->findArea() > shapes[maxA]->findArea())
			maxA = i;
		else if (shapes[i]->findArea() < shapes[minA]->findArea())
			minA = i;
		sumA += shapes[i]->findArea();
	}

	cout << "\n\nAreas sum = " << sumA << endl;

	cout << "\nsmallest P figure:" << endl;
	cout << typeid(*shapes[minP]).name() << " " << minP << ":\n";
	cout << shapes[minP]->toString();
	cout << "P = " << shapes[minP]->findPerim() << endl;
	cout << "S = " << shapes[minP]->findArea() << endl;

	cout << "\nbiggest P figure:" << endl;
	cout << typeid(*shapes[maxP]).name() << " " << maxP << ":\n";
	cout << shapes[maxP]->toString();
	cout << "P = " << shapes[maxP]->findPerim() << endl;
	cout << "S = " << shapes[maxP]->findArea() << endl;

	cout << "\nsmallest A figure:" << endl;
	cout << typeid(*shapes[minA]).name() << " " << minA << ":\n";
	cout << shapes[minA]->toString();
	cout << "P = " << shapes[minA]->findPerim() << endl;
	cout << "S = " << shapes[minA]->findArea() << endl;

	cout << "\nbiggest A figure:" << endl;
	cout << typeid(*shapes[maxA]).name() << " " << maxA << ":\n";
	cout << shapes[maxA]->toString();
	cout << "P = " << shapes[maxA]->findPerim() << endl;
	cout << "S = " << shapes[maxA]->findArea() << endl;*/

	// LAB3 LAB3 LAB3 LAB3 LAB3 LAB3 LAB3 LAB3 LAB3 LAB3 LAB3 LAB3

	Phonebook book;
}