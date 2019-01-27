#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>

std::vector<std::string> words;
std::string instr;

int main()
{
	int min = 0;
	int max = 0;

	//Открываем хэндл к файлу
	std::ifstream textsrc("C:\\Users\\Haxxor\\Documents\\Visual Studio 2017\\Projects\\algotasks\\Debug\\textfile.txt");
	if (textsrc.is_open())
	{
		//Добавляем слова в контейнер по отдельности
		std::istream_iterator<std::string> input(textsrc), end;
		std::copy(input, end, back_inserter(words));
		//Дебаг
		std::cout << "Amount of words: " << words.size() << std::endl;
	}
	
	//Находим позицию слова "today"
	auto pos = std::find(words.begin(), words.end(), "Today");
	//Итерируем элементы контейнера со словами
	for (std::vector<std::string>::iterator i = words.begin(); i != words.end(); i++)
	{
		//Сравниваем содержимое
		if (!strcmp(i->c_str(), "day"))
		{
			//Если минимум 0, то задаём минимальную разницу в расстоянии между словами
			if (min == 0)
				min = max = std::distance(pos, i);
			
			//Каждое новое совпадение = максимальная разница
			max = std::distance(pos, i);
		}
	}

	//-1 потому что учитывается слово Today
	//можно, конечно, считать со следующего слова, но это не комильфо
	std::cout << "Min distance: " << min - 1 << std::endl;
	std::cout << "Max distance: " << max - 1 << std::endl;

	//Закрываем хэндлы к файлу
	textsrc.close();

	return 0;
}