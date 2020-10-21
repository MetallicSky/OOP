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

		string getName()
		{
			return name;
		}

		void setName(string name)
		{
			this->name = name;
		}

		void addNumber(string number, short type)
		{
			for (int i = 0; i < numbers.size(); i++)
				if (numbers[i].getNum() == number)
					return;
			if (validNum(number) == false)
				throw exception("invalid number");
			Number temp(number, type);

			numbers.push_back(temp);
		}

		void addNumber(string number)
		{
			addNumber(number, 0);
		}

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

		string getNumbers()
		{
			string output;
			for (int i = 0; i < numbers.size(); i++)
			{
				output += numbers[i].getNum();
				output += "\t";
				output += numbers[i].getType();
				output += "\n";
			}
		}
	};

	vector<Contact> contacts;

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

	void add(string name)
	{
		Contact temp(name);
		contacts.push_back(temp);
	}

	void add(string name, string number, short type)
	{
		Contact temp(name, number, type);
		contacts.push_back(temp);
	}

	void add(string name, string number)
	{
		add(name, number, 0);
	}

	void remove(int index)
	{
		contacts.erase(contacts.begin() + index);
	}

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
	}

	Contact operator [] (int i)
	{
		return contacts[i];
	}
};