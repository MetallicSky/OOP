#pragma once

#include "windows.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Phonebook
{
	class Contact
	{
		class Number
		{
			string num;
			short type;
			enum numType
			{
				MOBILE,
				WORK,
				HOME
			};
		public:

			Number(string num)
			{
				this->num = num;
				this->type = MOBILE;
			}

			Number(string num, short type)
			{
				this->num = num;
				this->type = type;
			}

			string getNum()
			{
				return num;
			}

			string getType()
			{
				switch (this->type)
				{
				case MOBILE:
					return "MOBILE";
				case WORK:
					return "WORK";
				case HOME:
					return "HOME";
				}
			}

			void setNum(string number)
			{
				this->num = number;
				this->type = MOBILE;
			}

			void setNum(string number, short type)
			{
				this->num = number;
				if (type < 3 && type > -1)
					this->type = type;
				else
					this->num = MOBILE;
			}

			void setType(short type)
			{
				if (type < 3 && type > -1)
					this->type = type;
				return;
			}
		};

		string name;
		vector<Number> numbers;

		bool validNum(string number)
		{
			bool plus = false;
			if (number.front() == '+')
			{
				plus = true;
				number.erase(0, 1);
			}
			bool invalidChar = number.find_first_not_of("*#0123456789") != string::npos;
			if (invalidChar)
				return false;
			return true;
		}

	public:

		~Contact()
		{
			numbers.clear();
		}

		Contact(string name)
		{
			this->name = name;
		}

		Contact(string name, string num)
		{
			this->name = name;
			if (validNum(num) == false)
				throw exception("invalid number");
			this->numbers.push_back(num);
		}

		Contact(string name, string num, short type)
		{
			this->name = name;
			validNum(num);
			if (validNum(num) == false)
				throw exception("invalid number");
			this->numbers.push_back(num);
			this->numbers[0].setType(type);
		}

		/// <summary>
		/// Возвращает string с названием контакта
		/// </summary>
		/// <returns></returns>
		string getName()
		{
			return name;
		}

		/// <summary>
		/// Изменяет название контакта
		/// </summary>
		/// <param name="name">Новое название</param>
		void setName(string name)
		{
			this->name = name;
		}

		/// <summary>
		/// Добавляет контакту новый номер типа type (0 - MOBILE 1 - WORK 2 - HOME)
		/// </summary>
		/// <param name="number">Новый номер</param>
		/// <param name="type">Тип</param>
		void addNumber(string number, short type)
		{
			for (int i = 0; i < numbers.size(); i++)
			{
				string str = numbers[i].getNum();
				if (str == number)
					return;
			}
			if (validNum(number) == false)
				throw exception("invalid number");
			Number temp(number, type);

			numbers.push_back(temp);
		}

		/// <summary>
		/// Добавляет контакту новый номер типа MOBILE
		/// </summary>
		/// <param name="number">Новый номер</param>
		void addNumber(string number)
		{
			addNumber(number, 0);
		}

		/// <summary>
		/// Удаляет у контакта заданный номер, если он у него есть
		/// </summary>
		/// <param name="search">удаляемый номер</param>
		/// <returns></returns>
		bool removeNumber(string search)
		{
			for (int i = 0; i < numbers.size(); i++)
				if (numbers[i].getNum() == search)
				{
					numbers.erase(numbers.begin() + i);
					return true;
				}
			return false;
		}

		/// <summary>
		/// Возвращает string со всеми номерами контакта и их типами
		/// </summary>
		/// <returns></returns>
		string getNumbers()
		{
			string output;
			for (int i = 0; i < numbers.size(); i++)
			{
				output += numbers[i].getNum();
				output += " - ";
				output += numbers[i].getType();
				output += "\n";
			}

			return output;
		}
	};

	/// <summary>
	/// Список контактов в телефонной книге
	/// </summary>
	vector<Contact> contacts;

	/// <summary>
	/// Проверяет, является ли number корректным номером
	/// </summary>
	/// <param name="number">Проверяемый string</param>
	/// <returns></returns>
	bool validNum(string number)
	{
		bool plus = false;
		if (number.front() == '+')
		{
			plus = true;
			number.erase(0, 1);
		}
		bool invalidChar = number.find_first_not_of("*#0123456789") != string::npos;
		if (invalidChar)
			return false;
		return true;
	}

public:

	/// <summary>
	/// Добавляет новый контакт без номеров
	/// </summary>
	/// <param name="name">Название контакта</param>
	void add(string name)
	{
		Contact temp(name);
		contacts.push_back(temp);
	}

	/// <summary>
	/// Добавляет новый контакт с номером и типом type (0 - MOBILE 1 - WORK 2 - HOME)
	/// </summary>
	/// <param name="name">Название контакта</param>
	/// <param name="number">Номер</param>
	/// <param name="type">Тип номера</param>
	void add(string name, string number, short type)
	{
		Contact temp(name, number, type);
		contacts.push_back(temp);
	}

	/// <summary>
	/// Добавляет новый контакт с номером типа MOBILE
	/// </summary>
	/// <param name="name">Название контакта</param>
	/// <param name="number">Номер</param>
	void add(string name, string number)
	{
		add(name, number, 0);
	}

	/// <summary>
	/// Удаляет контакт с заданным индексом
	/// </summary>
	void remove(int index)
	{
		contacts.erase(contacts.begin() + index);
	}

	/// <summary>
	/// Возвращает string с результатами поиска в телефонной книге. Если запрос является возможным номером, то поиск осуществляется среди всех номеров, иначе среди названий контактов
	/// </summary>
	/// <param name="searchPart">Поисковый запрос</param>
	/// <returns></returns>
	string find(string searchPart)
	{
		string result;
		if (validNum(searchPart))
		{
			for (int i = 0; i < contacts.size(); i++)
				if (contacts[i].getNumbers().find(searchPart) != string::npos)
				{
					result += "\t";
					result += contacts[i].getName();
					result += ":\n";
					result += contacts[i].getNumbers();
					result += "\n";
				}
		}
		else
		{
			for (int i = 0; i < contacts.size(); i++)
				if (contacts[i].getName().find(searchPart) != string::npos)
				{
					result += "\t";
					result += contacts[i].getName();
					result += ":\n";
					result += contacts[i].getNumbers();
					result += "\n";
				}
		}

		return result;
	}

	Contact* operator [] (int i)
	{
		return &contacts[i];
	}
};