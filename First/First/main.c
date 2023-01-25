#include "methods.h"

int mines = 3;

int bombs[3][2];

//игровое поле
char field[8][8];

//Координаты бомб по вертикали
int bombX[3];

//Координаты бомб по горизонтали
int bombY[3];

void PrintField()
{
	int n = 0;
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
}

int ReadPosition()
{
	printf("Введите значение от 1 до 8:\t");

	int pos;
	#pragma warning(suppress : 4996)
	scanf("%d", &pos);

	printf("\n");
	if (pos > 0 && pos <= 8)
		return --pos;
	else
	{
		printf("Введены некорректные значения, попробуйте заново.\n");
		ReadPosition();
	}
}

int Read()
{
	printf("\n1 - Play again\n0 - Stop\n");

	int r;
	#pragma warning(suppress : 4996)
	scanf("%d", &r);
	if (r == 0)
		return 0;
	else if (r == 1)
		return 1;
	else
	{
		printf("Введены некорректные значения, попробуйте заново.\n");
		Read();
	}
}

int SetPos()
{
	int posX = ReadPosition();
	int posY = ReadPosition();

	int posArr[] = {posY, posX};

	for (int i = 0; i < mines; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			int m = j + 1;
			if (bombs[i][j] == posArr[j] && bombs[i][m] == posArr[m])
			{
				printf("You lost\n");
				return 1;
			}
		}
	}
	for(int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (i == posY && j == posX)
			{
				field[i][j] = '_';
				return 0;
			}
		}	
	return -1;
}

int IsBombAround()
{

}

void BombCoord()
{
	for (int i = 0; i < mines; i++)
	{
		printf("%d: %d %d\t\t", i, bombY[i], bombX[i]);
		printf("\n");
	}
}

void StartField(int iteration)
{
	int n = 0;

	srand(time(NULL));
	
	//заполнение массива координат рандомными значениями от 0 до 7 включительно
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
				field[i][j] = '#';
	if (iteration == 0)
		GetBombs();
	
	for (int i = 0; i < mines; i++)
		field[bombX[i]][bombY[i]] = '*';
	printf("\n");

	PrintField();
	
	getchar();
}

void GetBombs()
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 2; j++)
		{
			bombs[i][j] = rand() % 10;
			if (bombs[i][j] > 7)
				bombs[i][j] -= 2;
		}

	for (int i = 0; i < mines; i++)
		bombX[i] = bombs[i][0];
	for (int i = 0; i < mines; i++)
		bombY[i] = bombs[i][1];

}

int CheckWin()
{
	char win = '#';
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (field[i][j] == win)
			{
				return 1;
			}
		}
	}
	
	return 0;
}

int main() 
{
	setlocale(LC_ALL, "Ru"); //локализация
	
	int a = 1; 
	int iteration = 0;
		
	while (a == 1)
	{
		if (iteration == 0)
		{
			StartField(iteration);
		}

		BombCoord();

		int g = SetPos();

		a = CheckWin();

		if (g == 0)
		{
			system("cls");
			PrintField();
			iteration++;
		}
		else
			a = Read();
	}

	if (a == 0)
		printf("\nYou win!\n");

	//getchar();

	return 0;
}