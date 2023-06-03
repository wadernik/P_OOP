#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// Симметричное шифрование.
// Метод Вернама.
// Там должно быть 4 текстовых файла:
// - input.txt (с него считывается текст,который нужно зашифровать)
// - key.txt там ключ шифрования
// - code.txt там находится зашифрованный текст
// - encode.txt обратно расшифрованный

long mod(int a, int b)
{
	return (a % b + b) % b;
}

/**
 * Убираем все лишние пробелы и преобразуем строку к верхнему регистру
 */
void toUppercase(string& line)
{
	for (char& c : line)
	{
		if (c != ' ')
		{
			c = toupper(c);
		}
	}
}

/**
 * Для упрощения, метод работает только с одной строкой за раз
 * Поэтому если надо обработать несколько строк, можно в цикле вызвать функцию несколько раз.
 */
string Encrypt(string& line, string& key)
{
	string encryptedResult = "";
	
	int keyLength = key.length();
	int keyIterator = 0;

	for (int i = 0; i < line.length(); i++)
	{
		// Применяем трансформацию для каждого чара отдельно
		encryptedResult += char(mod(int(line[i] - 65 + key[keyIterator] - 65), 26) + 65);

		keyIterator++;

		if (keyIterator >= keyLength) {
			keyIterator = 0;
		}
	}

	return encryptedResult;
}

string Decrypt(string& line, string& key)
{
	string decryptedResult = "";

	int keyLength = key.length();
	int keyIterator = 0;

	for (int i = 0; i < line.length(); i++)
	{
		decryptedResult += char(mod(int((line[i] - 65) - (key[keyIterator] - 65)), 26) + 65);

		keyIterator++;

		if (keyIterator >= keyLength) {
			keyIterator = 0;
		}
	}

	return decryptedResult;
}

int main()
{
	vector<string> linesToEncrypt;
	string textLine;
	string key;

	// Читаем текст из файла и складывает в контейнер все строки
	ifstream textFile("input.txt");
	if (textFile.is_open())
	{
		while (getline(textFile, textLine))
		{
			// Дебаг
			cout << "Line: " << textLine << endl;

			if (!textLine.empty())
			{
				linesToEncrypt.push_back(textLine);
			}
		}

		textFile.close();
	}

	// Читаем ключ из файла. Считается, что ключ - текст в одну строку.
	ifstream keyFile("key.txt");
	if (keyFile.is_open())
	{
		getline(keyFile, key);
		keyFile.close();

		// Дебаг
		cout << "Key: " << key << endl;
	}

	if (linesToEncrypt.empty() || key.empty())
	{
		cout << "Input data is empty." << endl;
		return 1;
	}

	// Чтобы не складывать слова в контейнер, можно во время чтения из файла сразу преобразовывать строки.
	// Но из соображений безопасности, чтобы не включать логику обработки
	// прямо во время чтения из файла, преобразования производятся отдельно.
	vector<string> encryptedLines;
	vector<string> decryptedLines;
	for (vector<string>::iterator i = linesToEncrypt.begin(); i != linesToEncrypt.end(); i++)
	{
		string line = *i;
		toUppercase(line);
		toUppercase(key);

		string encryptedLine = Encrypt(line, key);
		encryptedLines.push_back(encryptedLine);

		// Дебаг
		cout << "Encrypted: " << encryptedLine << endl;

		string decryptedLine = Decrypt(encryptedLine, key);
		decryptedLines.push_back(decryptedLine);

		// Дебаг
		cout << "Decrypted: " << decryptedLine << endl;

		encryptedLine.clear();
		decryptedLine.clear();
	}

	if (encryptedLines.empty() || decryptedLines.empty())
	{
		return 1;
	}

	ofstream EncodedText("code.txt");
	for (vector<string>::iterator i = encryptedLines.begin(); i != encryptedLines.end(); i++)
	{
		EncodedText << *i << endl;
	}

	EncodedText.close();

	ofstream DecodedText("encode.txt");
	for (vector<string>::iterator i = encryptedLines.begin(); i != encryptedLines.end(); i++)
	{
		DecodedText << *i << endl;
	}

	DecodedText.close();

	return 0;
}
