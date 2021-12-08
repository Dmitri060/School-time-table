#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <Windows.h>

class NameClass
{
	int m_number;
	char m_parallel;
public:
	NameClass(int numder, char parallel) : m_number(numder), m_parallel(parallel) {}

	int getNumber() const
	{
		return m_number;
	}

	int getParallel() const
	{
		return m_parallel;
	}
};

class Teacher
{

	std::string m_name;
	int m_maxLessonDay;
	std::vector<const std::string*> m_schoolObject;

	std::vector<std::vector<NameClass>> m_nameClass;

public:
	Teacher(std::string& name, int maxLessonDay, std::vector<const std::string*> &schoolObject) 
		: m_name(name), m_maxLessonDay(maxLessonDay), m_schoolObject(schoolObject)
	{

	}

	const std::string& getName() const
	{
		return m_name;
	}

	/*
	* возвращает массив
	*/
	const std::vector<const std::string*>& getObject() const
	{
		return m_schoolObject;
	}

	Teacher& operator=(const Teacher& r)
	{
		m_name = r.m_name;
		m_schoolObject = r.m_schoolObject;
		return *this;
	}

	void newLesson(int day, const NameClass& nameClass)
	{
		m_nameClass[day].push_back(nameClass);
	}

	friend std::ostream& operator<< (std::ostream& out, const Teacher& teacher);
};

std::ostream& operator<<(std::ostream& out, const Teacher& teacher)
{
	out << "учитель: " << teacher.m_name << '\n';
	out << "предмет(ы):\n";
	for (auto a : teacher.m_schoolObject)
		out << *a << '\n';
	return out;
}

class Lesson
{
	const Teacher& m_teacher;
	const std::string& m_schoolObject;

public:
	Lesson(const Teacher* teacher, const std::string* schoolObject)
		: m_teacher(*teacher), m_schoolObject(*schoolObject) {}

	const Teacher& getTeacher() const
	{
		return m_teacher;
	}

	const std::string& getShcoolObject() const
	{
		return m_schoolObject;
	}
};

class TimeLesson
{
	Lesson m_lesson;
	int m_time;

public:
	TimeLesson(const Lesson& lesson, int time) : m_lesson(lesson), m_time(time)
	{}

	const Lesson& getLesson() const
	{
		return m_lesson;
	}

	int getTime() const
	{
		return m_time;
	}
};

class SchoolClass
{
	int m_number;
	char m_parallel;
	int m_dayLesson;
	std::vector<TimeLesson> m_timeLesson;

	std::vector<std::vector<Lesson>> m_time_table;

public:
	SchoolClass(int number, char parallel,int dayLesson, std::vector<TimeLesson>& timeLesson)
		: m_number(number), m_parallel(parallel), m_dayLesson(dayLesson), m_timeLesson(timeLesson)
	{
		m_timeLesson.resize(m_dayLesson);
	}

	std::vector<TimeLesson>& getTimeLesson()
	{
		return m_timeLesson;
	}

	void newLesson(int day, const Lesson& lesson)
	{
		m_time_table[day].push_back(lesson);
	}

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

int cinInt(std::string text = "Сколько дней учится класс: ")
{
	while (true)
	{
		std::cout << text;
		int a;
		std::cin >> a;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		else
			std::cin.ignore(32767, '\n');
			return a;
	}
}

/*
* null ссылка обозначает завершение поиска в массиве
*/
std::string* search(std::vector<std::string>& r, std::string text = "Введите предмет(stop): ")
{
	while (true)
	{
		std::string a(cinSchoolObject(text));
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
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::vector<std::string> schoolObject;
#pragma region initSchoolObject

	while (true)
	{
		std::string object(cinSchoolObject());
		if (object == "stop")	break;
		schoolObject.push_back(object);
	}

	system("cls");
	std::sort(schoolObject.begin(), schoolObject.end());

#pragma endregion

	std::vector<Teacher> teacher;
#pragma region initTeacher

	std::cout << "Предметы: \n";
	for (auto& a : schoolObject)
		std::cout << a << '\n';

	while (true)
	{
		std::string name(cinSchoolObject("Введите имя учителя: "));
		std::vector<const std::string*> object;
		while (true)
		{
			std::string* a(search(schoolObject));
			if (a == nullptr)
				break;
			object.push_back(a);
		}
		int maxLessonDay(cinInt("Сколько уроков в день у учителя: "));
		teacher.push_back(Teacher(name, maxLessonDay, object));
		if (cinSchoolObject("Вводить ещё учителя(yes, no): ") == "no")	break;
	}

	system("cls");
	struct {
		bool operator()(Teacher& a, Teacher& b) const { return a.getName() < b.getName(); }
	} customLess;
	std::sort(teacher.begin(), teacher.end(), customLess);

#pragma endregion
	
	std::vector<SchoolClass> schoolClass;
#pragma region initSchoolClass

	while (true)
	{
		int number(cinInt("Введите номер класа: "));
		char parallel(cinSchoolObject("Введите паралель: ")[0]);
		int dayLesson(cinInt());
		std::vector<TimeLesson> timeLesson;
		while (true)
		{
			std::string& object(*search(schoolObject));
			std::cout << "Учителя преподающие предмет: \n\n";
			for (auto& a : teacher)
			{
				for (auto& r : a.getObject())
				{
					if (*r == object)
						std::cout << a;
				}
			}
			Teacher* teas = nullptr;
			while (teas == nullptr)
			{
				std::string tea(cinSchoolObject("кто преподаёт предмет: "));
				for (auto& a : teacher)
				{
					if (a.getName() == tea)
					{
						teas = &a;
						break;
					}
				}
				if (teas != nullptr)	break;
				std::cout << "Учитель не найден, попробуйте снова.\n";
			}
			int time(cinInt("Сколько часов в неделю идёт урок: "));

			timeLesson.push_back(TimeLesson(Lesson(teas, &object), time));
			if (cinSchoolObject("Есть ещё урок(yes, no): ") == "no")	break;
		}
		schoolClass.push_back(SchoolClass(number, parallel, dayLesson, timeLesson));
		if (cinSchoolObject("Есть ещё класс(yes, no): ") == "no")	break;
	}

#pragma endregion

#pragma region MyRegion

	{
		for (auto& a : schoolClass)
		{

		}
		for (size_t i = 0; i < length; i++)
		{
			for (auto& a : schoolClass)
			{
				if ()
				{
					a.newLesson(0, a.getTimeLesson()[0].getLesson());
				}
			}
		}
	}

#pragma endregion

}
