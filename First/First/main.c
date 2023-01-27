#include "methods.h"

int bombs[MINES][2];

//игровое поле
char field[8][8];

int bombsField[8][8];

//Координаты бомб по вертикали
int bombX[MINES];

//Координаты бомб по горизонтали
int bombY[MINES];

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
	printf("Введите значение по горизонтали от 1 до 8:\t");
	int posX = ReadPosition();
	printf("Введите значение по вертикали от 1 до 8:\t");
	int posY = ReadPosition();

	for (int i = 0; i < MINES; i++)
	{
		if (bombs[i][0] == posY && bombs[i][1] == posX)
		{
			system("cls");
			printf("You lost\n");
			return 1;
		}
	}
	int bombY = posY;
	int bombX = posX;

	int countBombsAround = 0;

	//сверху
	if (bombY > 0 && bombsField[bombY - 1][bombX] == 1)
		{
			countBombsAround++;
		}
	//сверху слева
	if (bombX > 0 && bombY > 0 && bombsField[bombY - 1][bombX - 1] == 1)
	{
		countBombsAround++;
	}
	//сверху справа
	if (bombY > 0 && bombX < 7 && bombsField[bombY - 1][bombX + 1] == 1)
		{
			countBombsAround++;
		}
	//слева
	if (bombX > 0 && bombsField[bombY][bombX - 1] == 1)
		{
			countBombsAround++;
		}
	//справа
	if (bombX < 7 && bombsField[bombY][bombX + 1] == 1)
	{
		countBombsAround++;
	}
	//снизу
	if (bombY < 7 && bombsField[bombY + 1][bombX] == 1)
	{
		countBombsAround++;
	}
	//снизу слева
	if (bombY < 7 && bombX > 0 && bombsField[bombY + 1][bombX - 1] == 1)
		{
			countBombsAround++;
		}
	//снизу справа
	if (bombX < 7 && bombY < 7 && bombsField[bombY + 1][bombX + 1] == 1)
		{
			countBombsAround++;
		}
	
	char bombsAround = countBombsAround + '0';

	for(int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (i == posY && j == posX)
			{
				field[i][j] = bombsAround;
				return 0;
			}
		}

	return -1;
}

void BombCoord()
{
	for (int i = 0; i < MINES; i++)
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
	for (int i = 0; i < MINES; i++)
		bombsField[bombX[i]][bombY[i]] = 1;
	PrintField();
	printf("\n");
	
	//getchar();
}

void GetBombs()
{
	for (int i = 0; i < MINES; i++)
		for (int j = 0; j < 2; j++)
		{
			bombs[i][j] = rand() % 10;
			if (bombs[i][j] > 7)
				bombs[i][j] -= 2;
		}

	for (int i = 0; i < MINES; i++)
		bombX[i] = bombs[i][0];
	for (int i = 0; i < MINES; i++)
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

void Clear()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			bombsField[i][j] = 0;
		}
	}
}

int main() 
{
	setlocale(LC_ALL, "Ru"); //локализация
	
	int a = 1; 

	int win = 1;
	int iteration = 0;
		
	while (a == 1)
	{
		if (iteration == 0)
		{
			StartField(iteration);
		}

		//BombCoord();

		int g = SetPos();

		win = CheckWin();
		if (win == 0)
		{
			printf("\nYou win!\n");
			a = Read();
			iteration = 0;
			Clear();
		}

		if (g == 0)
		{
			system("cls");
			PrintField();
			iteration++;
			//Clear();
		}
		else
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (bombsField[i][j] == 0)
					{
						field[i][j] = '_';
					}
					else
					{
						field[i][j] = '*';
					}
				}
			}
			PrintField();
			a = Read();
			iteration = 0;
			system("cls");
			Clear();
		}
	}

	return 0;
}