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


/*
* null ссылка обозначает завершение поиска в массиве
*/
std::string* search(std::vector<std::string>& r)
{
	std::cout << "\e[1;1H\e[2J";
	while (true)
	{
		std::string a(cinSchoolObject());
		if (a == "stop")
			break;
		for (auto& e : r)
		{
			if (a == e)
				return &e;
		}
		std::cout << "элемент не найден попробайте заново.\n";
	}
	return nullptr;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	std::vector<std::string> schoolObject;
#pragma region initSchoolObject

	while (true)
	{
		std::string object(cinSchoolObject());
		if (object == "stop")
			break;
		schoolObject.push_back(object);
	}

	std::sort(schoolObject.begin(), schoolObject.end());

#pragma endregion

	std::vector<Teacher> teacher;
#pragma region initTeacher

	while (true)
	{
		std::string name(cinSchoolObject("Введите имя учителя: "));
		std::vector<std::string*> object;
		while (true)
		{
			auto a(search(schoolObject));
			if (a == nullptr)
				break;
			object.push_back(a);
			/*
			* добавить инициализации нового компонента в массив teacher
			* добавить выход из цикла teacher
			*/
		}
	}

#pragma endregion

}
