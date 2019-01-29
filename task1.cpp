#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>

std::vector<std::string> words;
std::string instr;

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		int min = 0;
		int max = 0;

		std::string textPath(argv[1]);
		std::string word1(argv[2]);
		std::string word2(argv[3]);

		// Открываем хэндл к файлу
		std::ifstream textSrc(textPath);
		if (textSrc.is_open())
		{
			// Добавляем слова в контейнер по отдельности
			std::istream_iterator<std::string> input(textSrc), end;
			std::copy(input, end, back_inserter(words));
			
			// Дебаг
			std::cout << "Amount of words: " << words.size() << std::endl;
		}
		
		// Находим позицию первого слова
		auto pos = std::find(words.begin(), words.end(), word1);

		// Итерируем элементы контейнера со словами
		for (std::vector<std::string>::iterator i = words.begin(); i != words.end(); i++)
		{
			// Сравниваем содержимое
			// if (!strcmp(i->c_str(), word2.c_str()))
			if ((*i).compare(word2) == 0)
			{
				std::cout << i - words.begin() << " / " << pos - words.begin() << std::endl;

				if ((i - words.begin()) > pos - words.begin())
				{
					// Если минимум 0, то задаём минимальную разницу в расстоянии между словами
					if (min == 0)
					{
						min = max = std::distance(pos, i);
					}
					
					// Каждое новое совпадение = максимальная разница
					max = std::distance(pos, i);
				}
				else
				{
					if (min == 0)
					{
						min = max = std::distance(i, pos);
					}
					
					// Каждое новое совпадение = максимальная разница
					max = std::distance(i, pos);
				}
				
				
			}
		}

		// -1, потому что distance [first:last)
		std::cout << "Min distance: " << min - 1 << std::endl;
		std::cout << "Max distance: " << max - 1 << std::endl;

		// Закрываем хэндлы к файлу
		textSrc.close();
	}

	return 0;
}