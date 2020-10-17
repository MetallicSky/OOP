#include "Matr.h"
#include <iostream>

using namespace std;

int main()
{
	Matrix<int> test1(3, 2);
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
	cout << endl;
}