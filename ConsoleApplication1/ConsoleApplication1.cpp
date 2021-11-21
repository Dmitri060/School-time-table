#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Teacher
{

	std::string m_name;
	std::vector<std::string> &m_schoolObject;

public:
	Teacher(std::string name, std::vector<std::string> &schoolObject) : m_name(name), m_schoolObject(schoolObject)
	{

	}
	~Teacher()
	{}
};

std::string cinSchoolObject(std::string text = "Введите предмет(stop): ")
{
	while (true)
	{
		std::cout << text;
		std::string a;
		std::getline(std::cin, a);

		if (std::cin.fail()) 
		{
			std::cin.clear(); 
			std::cin.ignore(32767, '\n');
		}
		else
			return a;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
#pragma region initSchoolObject

    std::vector<std::string> schoolObject;
	while (true)
	{
		std::string object(cinSchoolObject());
		if (object == "stop")
			break;
		schoolObject.push_back(object);
	}

	std::sort(schoolObject.begin(), schoolObject.end());

#pragma endregion

#pragma region initTeacher

	std::vector<Teacher> teacher;
	while (true)
	{
		std::string name(cinSchoolObject("Введите имя учителя: "));
		std::vector<std::string*> object;
		while (true)
		{

		}
	}

#pragma endregion

}
