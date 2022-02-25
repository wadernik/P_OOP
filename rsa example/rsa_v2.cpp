#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

long int greatestCommonDivisor(long int a, long int b)
{
  while (a > 0)
  {
    long int tempVal;

    tempVal = a;
    a = b % a;
    b = tempVal;
  }

  return b;
}

long int calculateExponent(long int phi)
{
  long int exponent;

  for (exponent = 2; exponent < phi; exponent++)
  {
    if (greatestCommonDivisor(exponent, phi) == 1)
    {
      return exponent;
    }
  }

  return -1;
}

long int calculateNumberD(long int &exponent, long int &phi)
{
  long int numberD;
  long int i = 1;

  while (1)
  {
    i = i + phi;

    if (i % exponent == 0)
    {
      numberD = i / exponent;
      return numberD;
    }
  }
}

long int encrypt(long int c, long int &exponent, long int &modulePQ)
{
  long int current, result;

  current = c - 96;
  result = 1;

  for (long int i = 0; i < exponent; i++)
  {
    result = result * current;
    result = result % modulePQ;
  }

  return result + 96;
}

long int decrypt(long int c, long int &numberD, long int &modulePQ)
{
  long int current, result;

  current = c - 96;
  result = 1;

  for (long int i = 0; i < numberD; i++)
  {
    result = result * current;
    result = result % modulePQ;
  }

  return result + 96;
}

int main()
{
	vector<double> encryptedChars;
  vector<double> decryptedChars;
	string text;
	string key;

	long int primeNumberP, primeNumberQ;

  // Произведение P * Q, модуль
	long int modulePQ;
	// Функция Эйлера
	long int phi;
	// Экспонента. Часть от пары открытого ключа
	long int exponent;
	// Часть от пары закрытого ключа
	long int numberD;

	// Читаем текст из файла и складывает в контейнер
	ifstream textFile ("input.txt");
	if (textFile.is_open())
	{
		getline(textFile, text);
		textFile.close();

		cout << "Text: " << text << endl;
	}

	// Читаем ключи из файла. Считаем, что в первой строке лежит P, во второй - Q.
	ifstream keyFile ("keys.txt");
	if (keyFile.is_open())
	{
		getline(keyFile, key);

		primeNumberP = stol(key);
		key.clear();

		getline(keyFile, key);
		primeNumberQ = stol(key);

		keyFile.close();

    cout << "PrimeP: " << primeNumberP << endl;
    cout << "PrimeQ: " << primeNumberQ << endl;
	}

  // Вычисляем публичный и закрытый ключ
	// Вычисляем произведение P * Q
	modulePQ = primeNumberP * primeNumberQ;
	cout << "Mod: " << modulePQ << endl;

	// Вычисляем функцию Эйлера
	phi = (primeNumberP - 1) * (primeNumberQ - 1);
	cout << "Phi: " << phi << endl;

	// Вычисляем экспоненту, часть публичного
	exponent = calculateExponent(phi);
	// Вычисляем закрытый ключ
	numberD = calculateNumberD(exponent, phi);

	cout << "Public key pair: {Mod = [" << modulePQ << "] | exp = [" << exponent << "]" << endl;
	cout << "Private key pair: {Mod = [" << modulePQ << "] | D = [" << numberD << "]" << endl;

	// Шифруем каждый символ текста
	for (long int i = 0; i < text.length(); i++)
	{
    encryptedChars.push_back(encrypt(text[i], exponent, modulePQ));
	}

	// Выводим зашифрованный текст и сохраняем в файл
  ofstream encryptedTextFile("out_encrypted.txt");
	cout << "Encrypted text: ";
	for (auto i = encryptedChars.begin(); i != encryptedChars.end(); i++)
  {
    cout << char(*i);
    encryptedTextFile << char(*i);
  }

  encryptedTextFile.close();

  cout << endl;

	// Расшифровываем обратно
	for (long int i = 0; i < encryptedChars.size(); i++)
	{
    decryptedChars.push_back(decrypt(encryptedChars[i], numberD, modulePQ));
	}

  // Выводим расшифрованный текст и сохраняем в файл
  ofstream decryptedTextFile("out_decrypted.txt");
  cout << "Decrypted text: ";
	for (auto i = decryptedChars.begin(); i != decryptedChars.end(); i++)
	{
    cout << char(*i);
    decryptedTextFile << char(*i);
	}

  decryptedTextFile.close();
	cout << endl;

  return 0;
}
