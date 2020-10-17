#include "Matr.h"
#include <iostream>

using namespace std;

int main()
{
	Matrix<int> test1(3, 2);
	test1.randomise(-10, 10);
	cout << "Matrix 1:" << endl;
	test1.print();
	Matrix<int> test2(3, 3);
	test2.randomise(-5, 5);
	cout << "\nMatrix 2:" << endl;
	test2.print();
	if (test1 == test2)
		cout << "\nequal" << endl;
	if (test1 != test2)
		cout << "\nnon-equal" << endl;
	Matrix<int> test3(1, 1);
	test3.randomise(0, 10);
	test3.print();
	cout << "det = " << test3.determinant();
	cout << endl;
	test3.print();
	cout << endl;
}