#include "Matr.h"
#include <iostream>

using namespace std;

int main()
{
	Matrix<int> test1(3, 2);
	cout << "\ntest1: without value constructor:" << endl;
	test1.print();

	test1.randomise(0, 10);
	cout << "\ntest1: after randomise(0, 10):" << endl;
	test1.print();

	Matrix<int> test2(2, 3, 4);
	cout << "\ntest2: with value = 4 constructor:" << endl;
	test2.print();

	if (test1 == test2)
		cout << "\nequal matrices" << endl;
	if (test1 != test2)
		cout << "\nnon-equal matrices" << endl;

	Matrix<int> test3(test1);
	cout << "\ntest3: with copy (test1) constructor:" << endl;
	test3.print();

	test3 = test1 * test2;
	cout << "\ntest3: test3 = test1 * test2:" << endl;
	test3.print();

	test1 = test1 + test1;
	cout << "\ntest1: test1 = test1 + test1:" << endl;
	test1.print();

	test2 = test2 - test2;
	cout << "\ntest2: test2 = test2 - test2:" << endl;
	test2.print();

	test1 = test1 * 2;
	cout << "\ntest1: test1 = test1 * 2:" << endl;
	test1.print();

	test1 = test1 / 2;
	cout << "\ntest1: test1 = test1 / 2:" << endl;
	test1.print();

	Matrix<int> test4(4, 4);
	test4.randomise(-10, 10);
	cout << "\ntest4: new 4X4 matrix after randomise(-10, 10):" << endl;
	test4.print();
	cout << "\ntest4 det = " << test4.determinant() << endl;
	cout << endl;
}