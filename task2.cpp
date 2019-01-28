#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

std::size_t CountEntries(std::vector<std::string> &contacts, std::string &searchStr)
{
	std::size_t matches = 0;
	std::size_t foundPos;

	for (auto &names : contacts)
	{
		foundPos = names.find(searchStr);
		if (foundPos != std::string::npos)
		{
			matches++;
		}
	}

	return matches;
}

int main()
{
	std::vector<std::string> contacts;
	int input = 0;
	std::string contact_name = "";
	std::string searchStr = "";
	std::size_t matches = 0;

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
				std::cout << "Enter new contact's name: ";

				// Получаем имя нового контакта
				// getline чтобы туда вошло имя с пробелами, иначе cin прервётся на первом же пробеле
				while(!getline (std::cin, contact_name) || contact_name.empty());
				
				// Переводим предложение в lowercase
				std::transform(contact_name.begin(), contact_name.end(), contact_name.begin(), ::tolower);

				matches = CountEntries(contacts, contact_name);

				if (matches == 0)
				{
					// Добавляем имя в контейнер
					contacts.push_back(contact_name);
				} 
				else
				{
					std::cout << "\nThis name already exists. Please try another one.\n";
				}

				// Чистим строку и к-во вхождений на будущее и на всякий
				contact_name.clear();
				matches = 0;
				break;
			
			case 2:
				std::cout << "Input contact's name to search for:\n";
				while (!getline(std::cin, searchStr) || searchStr.empty());
				std::transform(searchStr.begin(), searchStr.end(), searchStr.begin(), ::tolower);
				
				matches = CountEntries(contacts, searchStr);

				std::cout << searchStr << ": " << matches << " result(s)\n";
				
				searchStr.clear();
				break;
			}
	}

	return 0;
}