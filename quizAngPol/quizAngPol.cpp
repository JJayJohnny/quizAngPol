#include "pch.h"
#include <iostream>
#include <fstream>
#include <map>
#include <conio.h>
#include <string>
#include <ctime>
#include <random>

using namespace std;

fstream file;

map<string, string> words;

void save()
{
	file.open("words.txt", ios::out);
	for (map<string, string>::iterator it = words.begin(); it != words.end(); it++)
	{
		file << it->first << endl;
		file << it->second << endl;
	}
	file.close();
}

void addWord()
{
	string english, polish;
	cout << "Podaj angielskie slowko: ";
	cin >> english;
	cout << "Podaj polskie znaczenie: ";
	cin >> polish;
	words[english] = polish;
	save();
}

void showWords()
{
	for (map<string, string>::iterator it = words.begin(); it != words.end(); it++)
	{
		cout << it->first << " " << it->second << endl;
	}
	system("pause");
}

void deleteWord()
{
	string word;
	cout << "Podaj slowo do usuniecia (ang.): ";
	cin >> word;
	words.erase(word);
	save();
}

void test()
{
	cout << "Ile pytan? ";
	int n;
	cin >> n;
	
	srand(time(NULL));
	int points = 0;
	for (int i = 0; i < n; i++)
	{
		cout << "Pytanie " << i + 1 << endl;
		int rnd = rand() % words.size();
		map<string, string>::iterator rndIt = words.begin();
		advance(rndIt, rnd);
		string ang = rndIt->first;
		string pol = rndIt->second;
		cout << ang << " - ";
		string odp;
		cin >> odp;
		if (odp == pol)
		{
			cout << "Dobrze!" << endl;
			points++;
		}
		else
			cout << "Niestety zle. Poprawna odp. to " << pol << endl;
	}
	cout << "Koniec testu. Liczba punktow: " << points << endl;
	system("pause");
}

void menu()
{
	system("cls");
	cout << "Menu:" << endl;
	cout << "1) Przeglad slowek" << endl;
	cout << "2) Dodawanie slowek" << endl;
	cout << "3) Usuwanie slowek" << endl;
	cout << "4) Test" << endl;
	cout << "5) Koniec" << endl;
}

int main()
{
	file.open("words.txt", ios::in);
	//wczytywanie pliku
	if (file.good())
	{
		string english;
		string polish;
		int k = 0;
		while (!file.eof())
		{
			if(k==0)
				getline(file, english);
			else
			{
				getline(file, polish);
				words[english] = polish;
				k = -1;
			}
			k++;
		}
		file.close();
	}

	//menu

	char option;

	menu();
	while (cin >> option)
	{
		switch (option)
		{
		case '1':
			showWords();
			break;
		case '2':
			addWord();
			break;
		case '3':
			deleteWord();
			break;
		case '4':
			test();
			break;
		case '5':
			exit(0);
		default:
			break;
		}
		menu();
	}

	return 0;
}

