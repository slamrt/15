#include<stdio.h>
#include<time.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include "Win10.h"
#include <stdlib.h>
#define ROW 4
#define COL 4
#define SIZE 16
using namespace std;
//координаты
struct Coord {
	int row, col;
};


//карта-поле
int Map[ROW][COL];
int masCheck[SIZE];





//поиск координатов нуля
Coord GetNil() {
	Coord result{ 0, 0 };
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (Map[i][j] == 0) {
				result.row = i;
				result.col = j;
				return result;
			}
		}
	}
	return result;
}
//имя, рекорд++, запись имени
struct Gamer {
	string name;
	int record = 0;
	void recordPlus() {
		record++;
	}
	void newName() {
		getline(cin, name);
	}
};


//Создание поля
void CreateMap();
//отрисовка поля
void DrawMap();
//отрисовка доп меню с инструкциями во время игры(внизу)
void DrawSideMenu();
//закончена ли игра
bool isFinished();
//отрисовка начального меню
void DrawMenu();
//чтобы числа-элементы карты не повторялись
bool isRepeating(int value);
//вывести правила игры
void DrawRules();
//логика игры
void startGame();

int main() {
	//srand(time(0));
	setlocale(LC_ALL, "RUSSIAN");
	CreateMap();
	DrawMenu();

}

Gamer gamer;
void startGame() {

	int key = 0;
	Coord Nil;
	Nil = GetNil();

	DrawMap();
	DrawSideMenu();
	while (true) {
		//if (_kbhit())
		{
			key = _getch();
		}

		switch (key) {
		case _KEY::UP:
			if (Nil.row < ROW - 1) {
				swap(Map[Nil.row][Nil.col], Map[Nil.row + 1][Nil.col]);
				Nil.row++;
				gamer.recordPlus();
			}
			break;

		case _KEY::DOWN:
			if (Nil.row > 0) {
				swap(Map[Nil.row][Nil.col], Map[Nil.row - 1][Nil.col]);
				Nil.row--;
				gamer.recordPlus();
			}
			break;
		case _KEY::LEFT:
			if (Nil.col < COL - 1) {
				swap(Map[Nil.row][Nil.col], Map[Nil.row][Nil.col + 1]);
				Nil.col++;
				gamer.recordPlus();
			}
			break;
		case _KEY::RIGHT:
			if (Nil.col > 0) {
				swap(Map[Nil.row][Nil.col], Map[Nil.row][Nil.col - 1]);
				Nil.col--;
				gamer.recordPlus();
			}
			break;
		case _KEY::ESC:
			system("cls");
			DrawMenu();
			break;
		case _KEY::ENTER:
			bool isWin = isFinished();
			if (isWin) {
				SetPos(20, 10);
				cout << "Поздравляем! Вы выиграли. Ваш рекорд = " << gamer.record << endl << endl;
				cout << "Давайте запишем ваш рекорд. Напишите, пожалуйста, свое имя: ";
				gamer.newName();
				ofstream file("Records.txt");
				if (file.is_open() == true) {
					file << gamer.name;
					file << " ";
					file << gamer.record << endl;
					file.flush();
					file.close();
					gamer.name = "";
					gamer.record = 0;
					break;
				}
				else {
					cout << "Ошибка при записи рекорда в файл. Простите";
				}
			}
			else {
				SetPos(20, 10);
				cout << "Игра не окончена. Пожалуйста, ознакомьтесь с правилами в главном меню. Нажмите ENTER чтобы продолжить";
				cin.get();
				system("cls");

			}
			break;
		}


		DrawMap();
		DrawSideMenu();

	}
}

void DrawMenu()
{
	string menu[] = {
	 "1. Играть ",
	 "2. Правила",
	 "3. Рекорды",
	};
	int key = 0;

	while (true) {
		SetPos(0, 0);
		for (int i = 0; i < sizeof(menu) / sizeof(menu[0]); i++) {
			cout << menu[i] << endl;
		}

		//if (_kbhit())
		{
			key = _getch();
		}
		switch (key) {
		case 49:
			startGame();
			break;
		case 50:
			SetPos(15, 0);
			DrawRules();
			system("pause");
			system("cls");
			break;
		case 51:

			ifstream inFile("Records.txt");

			if (inFile.is_open()) {
				while (!inFile.eof())
				{
					string temp;
					getline(inFile, temp);
					cout << endl << temp << endl;
				}
				inFile.close();
			}
			else {
				cout << "Ошибка открытия файла для чтения!" << endl;
				cout << "Ошибка: файл MyFile.txt не найден!" << endl;
			}
			cin.get(); cin.get();
			system("pause");
			system("cls");
			break;
		};


	}
}


void DrawSideMenu() {

	cout << "Кол-во ходов: " << gamer.record << endl;
	cout << "Enter - завершить игру." << endl;
	cout << "ESC - выйти в главное меню.";
}

void DrawMap() {
	SetPos(0, 0);
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			cout << Map[i][j] << "\t";
		}
		cout << endl;
	}
}

void CreateMap() {

	srand((unsigned int)time(NULL));
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL;) {
			bool isOk = false;
			while (!isOk) {
				int randNum = rand() % SIZE;
				if (!isRepeating(randNum)) {
					Map[i][j] = randNum;
					isOk = true;
					j++;
					break;
				}
			}
		}
	}
}

bool isRepeating(int value) {
	if (masCheck[value]) {
		return true;
	}
	masCheck[value] = true;
	return false;
}

bool isFinished() {
	int arr[ROW * COL] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0 };
	int k = 0;
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (Map[i][j] != arr[k]) {
				return false;
			}
			k++;
		}
	}
	return true;
}

void DrawRules() {
	cout << "Популярная головоломка ПЯТНАШКА была придумана еще в конце 19 века. Классическое игровое поле представляет собой матрицу 4х4 клеток, на котором по порядку (слева - направо и сверху - вниз) располагаются цифры от 1 до 15. Последняя клетка – пустая. Клетки перемешиваются определенным образом, и задача игрока состоит в том, чтобы восстановить их первоначальное правильное расположение. Делать это можно лишь путем перемещения на пустую клетку другой, соседней с ней клетки (расположенной слева, справа, сверху или снизу от пустой).ENTER = вернуться в главное меню";
}