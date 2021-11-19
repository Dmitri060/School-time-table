#include <iostream>
#include <vector>
#include <string>

int main()
{
    std::vector<std::string> schoolObject;
	{
		std::string a;
		while (1)
		{
			std::cout << "Введите предмет: ";
			std::getline(std::cin, a);
			if (a != "stop")
				schoolObject.push_back(a);
		}
	}
}
