#pragma once

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Matrix
{
	size_t rws, cls;
	T** mat;

	T determinant(const Matrix& copy);
public:
	/// <summary>
	/// Создание матрицы размера rows * columns, заполненную 0
	/// </summary>
	/// <param name="rows">Количество строк</param>
	/// <param name="columns">Количество столбцов</param>
	/// <returns></returns>
	Matrix(size_t rows, size_t columns);
	/// <summary>
	///  Создание матрицы размера rows * columns, заполненную Value
	/// </summary>
	/// <param name="rows">Количество строк</param>
	/// <param name="columns">Количество столбцов</param>
	/// <param name="value">число для заполнения</param>
	/// <returns></returns>
	Matrix(size_t rows, size_t columns, T value);
	/// <summary>
	/// Создание матрицы копированием другой
	/// </summary>
	/// <param name="copy">Копируемая матрица</param>
	/// <returns></returns>
	Matrix(const Matrix& copy);

	~Matrix();

	/// <summary>
	/// Возвращает количество строк в матрице
	/// </summary>
	/// <returns></returns>
	size_t getRows()
	{
		return rws;
	}

	/// <summary>
	/// Возвращает количество столбцов в матрице
	/// </summary>
	/// <returns></returns>
	size_t getColumns()
	{
		return cls;
	}

	/// <summary>
	/// Печатает матрицу в консоли
	/// </summary>
	string toString();

	/// <summary>
	/// Заполняет массив случайными значениями от одного до второго предела
	/// </summary>
	/// <param name="point1">Первый предел</param>
	/// <param name="point2">Второй предел</param>
	void randomise(T point1, T point2);

	/// <summary>
	/// Находит определитель квадратной матрицы
	/// </summary>
	/// <returns></returns>
	T determinant();

	T* operator [] (int i)
	{
		return mat[i];
	}

	bool operator ==(const Matrix& other)
	{
		if (rws != other.rws || cls != other.cls)
			return false;
		for (int i = 0; i < rws; i++)
			for (int j = 0; j < cls; j++)
			{
				T t1, t2;
				t1 = mat[i][j];
				t2 = other.mat[i][j];
				if (t1 != t2)
					return false;
			}
		return true;
	}

	bool operator !=(const Matrix& other)
	{
		if (rws != other.rws || cls != other.cls)
			return true;
		for (int i = 0; i < rws; i++)
			for (int j = 0; j < cls; j++)
			{
				T t1, t2;
				t1 = mat[i][j];
				t2 = other.mat[i][j];
				if (t1 != t2)
					return true;
			}

		return false;
	}

	Matrix& operator=(const Matrix& other)
	{
		for (int i = 0; i < this->rws; i++)
		{
			delete[] this->mat[i];
		}
		delete[] this->mat;
		this->cls = other.cls;
		this->rws = other.rws;
		this->mat = new T * [this->rws];
		for (int i = 0; i < this->rws; i++)
		{
			this->mat[i] = new T[this->cls];
			for (int j = 0; j < this->cls; j++)
				this->mat[i][j] = other.mat[i][j];
		}

		return *this;
	}

	Matrix operator + (const Matrix& other) const
	{
		if (this->rws != other.rws || this->cls != other.cls)
			throw exception("different matrix sizes, addition not possible");
		Matrix<T> temp(other);
		for (int i = 0; i < this->rws; i++)
			for (int j = 0; j < this->cls; j++)
				temp.mat[i][j] += mat[i][j];
		return temp;
	}

	Matrix operator - (const Matrix& other) const
	{
		if (this->rws != other.rws || this->cls != other.cls)
			throw exception("different matrix sizes, substraction not possible");
		Matrix<T> temp(*this);
		for (int i = 0; i < this->rws; i++)
			for (int j = 0; j < this->cls; j++)
				temp.mat[i][j] -= other.mat[i][j];
		return temp;
	}

	Matrix operator * (const Matrix& other) const
	{
		if (this->cls != other.rws)
			throw exception("Matrix 1 must have the same amount of columns as rows in Matrix 2 for matrix multiplication");
		Matrix<T> temp(this->rws, other.cls);
		for (int i = 0; i < temp.rws; i++)
			for (int j = 0; j < temp.cls; j++)
				for (int k = 0; k < this->cls; k++)
					temp.mat[i][j] += this->mat[i][k] * other.mat[k][j];
		return temp;
	}

	Matrix operator * (T scalar) const
	{
		Matrix<T> temp(*this);
		for (int i = 0; i < temp.rws; i++)
			for (int j = 0; j < temp.cls; j++)
				temp.mat[i][j] *= scalar;
		return temp;
	}
	Matrix operator / (T scalar) const
	{
		Matrix<T> temp(*this);
		for (int i = 0; i < temp.rws; i++)
			for (int j = 0; j < temp.cls; j++)
				temp.mat[i][j] /= scalar;
		return temp;
	}
};

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t columns)
{
	if (rows < 1)
		throw exception("<1 rows amount");
	if (columns < 1)
		throw exception("<1 columns amount");
	mat = new T * [rows];
	for (int i = 0; i < rows; i++)
	{
		mat[i] = new T[columns];
		for (int j = 0; j < columns; j++)
			mat[i][j] = 0;
	}
	rws = rows;
	cls = columns;
}

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t columns, T value)
{
	if (rows < 1)
		throw exception("<1 rows amount");
	if (columns < 1)
		throw exception("<1 columns amount");
	mat = new T * [rows];
	for (int i = 0; i < rows; i++)
	{
		mat[i] = new T[columns];
		for (int j = 0; j < columns; j++)
			mat[i][j] = value;
	}
	rws = rows;
	cls = columns;
}

template<typename T>
Matrix<T>::Matrix(const Matrix& copy)
{
	mat = new T * [copy.rws];
	for (int i = 0; i < copy.rws; i++)
	{
		mat[i] = new T[copy.cls];
		for (int j = 0; j < copy.cls; j++)
			mat[i][j] = copy.mat[i][j];
	}
	rws = copy.rws;
	cls = copy.cls;
}

template<typename T>
Matrix<T>::~Matrix()
{
	for (int i = 0; i < rws; i++)
	{
		delete[] mat[i];
	}
	delete[] mat;
}

template<typename T>
string Matrix<T>::toString()
{
	string output;
	for (int i = 0; i < this->rws; i++)
	{
		for (int j = 0; j < this->cls; j++)
		{
			output += to_string(this->mat[i][j]);
			if (j != this->cls - 1)
				output += " ";
		}
		output += "\n";
	}
	return output;
}

template<typename T>
void Matrix<T>::randomise(T point1, T point2)
{
	T min, max;
	if (point1 < point2)
	{
		min = point1;
		max = point2;
	}
	else
	{
		min = point2;
		max = point1;
	}
	for (int i = 0; i < rws; i++)
		for (int j = 0; j < cls; j++)
			mat[i][j] = rand() % (max - min + 1) + min;
}

template<typename T>
T Matrix<T>::determinant(const Matrix& smaller)
{
	T det = 0;
	if (smaller.rws == 2)
	{
		det = smaller.mat[0][0] * smaller.mat[1][1] - smaller.mat[0][1] * smaller.mat[1][0];
		return det;
	}
	Matrix<T> temp(smaller.rws - 1, smaller.rws - 1);
	for (int i = 0; i < smaller.cls; i++)
	{
		int numbersDone = 0;
		for (int j = 1; j < smaller.rws; j++)
			for (int k = 0; k < smaller.cls; k++)
				if (k != i)
				{
					numbersDone++;
					temp.mat[(numbersDone - 1) / (smaller.rws - 1)][(numbersDone - 1) % (smaller.rws - 1)] = smaller.mat[j][k];
				}

		det += pow(-1, i + 2) * smaller.mat[0][i] * determinant(temp);
	}

	return det;
}

template<typename T>
T Matrix<T>::determinant()
{
	if (this->cls != this->rws)
		throw exception("Matrix determinant can only be found in square matrix");
	T det = 0;
	if (this->rws == 2)
	{
		det = this->mat[0][0] * this->mat[1][1] - this->mat[0][1] * this->mat[1][0];
		return det;
	}
	if (this->rws == 1)
		return this->mat[0][0];
	Matrix<T> temp(this->rws - 1, this->rws - 1);
	for (int i = 0; i < this->cls; i++)
	{
		int numbersDone = 0;
		for (int j = 1; j < this->rws; j++)
			for (int k = 0; k < this->cls; k++)
				if (k != i)
				{
					numbersDone++;
					temp.mat[(numbersDone - 1) / (this->rws - 1)][(numbersDone - 1) % (this->rws - 1)] = this->mat[j][k];
				}

		det += pow(-1, i + 2) * this->mat[0][i] * determinant(temp);
	}

	return det;
}
