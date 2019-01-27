#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

std::vector<std::string> contacts;

int main()
{
	int input = 0;
	std::string contact_name = "";
	std::string searchee = "";

	while (true)
	{
		std::cout << "\nChoose an operation to do:\n1. Add new contact\n2. Look-up existent contacts\n";
		std::cin>> input;

		switch (input)
		{
		case 0:
		default:
			std::cout << "Invalid option number\n";
			break;
		case 1:
			std::cout << "Enter new contact's name:\n";
			//Получаем имя нового контакта
			//getline чтобы туда вошло имя с пробелами, иначе cin прервётся на первом же пробеле
			while(!getline (std::cin, contact_name) || contact_name.empty());
			//Опускаем буквы в lowercase
			std::transform(contact_name.begin(), contact_name.end(), contact_name.begin(), ::tolower);
			//Добавляем имя в контейнер
			contacts.push_back(contact_name);
			//Чистим строку на будущее и на всякий
			contact_name.clear();
			break;
		case 2:
			std::cout << "Input contact's name to search for:\n";
			while (!getline(std::cin, searchee) || searchee.empty());
			std::transform(searchee.begin(), searchee.end(), searchee.begin(), ::tolower);
			int matches = 0;

			for (auto &names : contacts)
			{
				if (strstr(names.c_str(), searchee.c_str()))
				{
					matches++;
				}
			}

			std::cout << searchee << ": " << matches << " result(s)\n";

			break;
		}
	}

	return 0;
}