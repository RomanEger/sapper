#include "methods.h"

int bombs[3][2];

//игровое поле
char field[8][8];

//Координаты бомб по вертикали
int bombX[3];

//Координаты бомб по горизонтали
int bombY[3];

void BombCoord()
{
	for (int i = 0; i < 3; i++)
	{
		printf("%d: %d %d\t\t", i, bombX[i], bombY[i]);
		printf("\n");
	}
}

void StartField()
{
	int n = 0;

	srand(time(NULL));
	/*for (int i = 0; i < 3; i++)
	{
		bombX[i] = rand() % 10;
		if (bombX[i] > 7)
			bombX[i] -= 2;
	}
	for (int i = 0; i < 3; i++)
	{
		bombY[i] = rand() % 10;
		if (bombY[i] > 7)
			bombY[i] -= 2;
	}*/
	
	//заполнение массива координат рандомными значениями от 0 до 7 включительно
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			bombs[i][j] = rand() % 10;
			if (bombs[i][j] > 7)
				bombs[i][j] -= 2;
		}

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
				field[i][j] = '#';
	
	printf("  ");
	for (int i = 1; i < 9; i++)
		printf("%d ", i);
	printf("\n");

	for (int i = 0; i < 8; i++)
	{
		n++;
		printf("%d ", n);
		for (int j = 0; j < 8; j++)
		{
			printf("%c ", field[i][j]);
		}
		printf("\n");
	}
	
	getchar();
	system("cls");
	
	GameField();

	BombCoord();

	getchar();
}

void GameField()
{
	for (int i = 0; i < 3; i++)
		bombX[i] = bombs[i][0];
	for (int i = 0; i < 3; i++)
		bombY[i] = bombs[i][1];

	int n = 0;

	printf("  ");
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			field[i][j] = '#';
	for (int i = 0; i < 3; i++)
		field[bombX[i]][bombY[i]] = '*';

	for (int i = 1; i < 9; i++)
		printf("%d ", i);
	printf("\n");
	for (int i = 0; i < 8; i++)
	{
		n++;
		printf("%d ", n);
		for (int j = 0; j < 8; j++)
		{
			printf("%c ", field[i][j]);
		}
		printf("\n");
	}
}

int main() 
{
	setlocale(LC_ALL, "Ru"); //локализация
	
	StartField();

	return 0;
}