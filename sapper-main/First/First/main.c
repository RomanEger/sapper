#include "methods.h"
//Вычисление длины массива
#define SIZEOF(a) sizeof(a)/sizeof(*a)

int bombs[MINES][2];



//игровое поле
char field[8][8];

int bombsField[8][8];

char winField[8][8];

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
	if (pos > 10 && pos <= 88 && pos%10 != 0)
		return pos;
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
	printf("Введите XY клетки\t ");
	int XY = ReadPosition();
	//printf("Введите значение по горизонтали от 1 до 8:\t");
	int posX = (XY / 10) - 1 ;
	//printf("Введите значение по вертикали от 1 до 8:\t");
	int posY = (XY % 10) - 1 ;


	//Если Нажал на бобму то все!!!
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

	int countBombsAround = CountBobsAround(posX,posY);
	
	
		
	int cache[8 * 8];
	for (int i = 0; i < 8 * 8;i++)
		cache[i] = 0;

	return OpenSpace(posX, posY, countBombsAround,cache);

		

	
}

int CountBobsAround(int posX,int posY)
{
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
	return countBombsAround;
}

int SetNumberCell(int posX, int posY, int countBombs)
{
	char bombsAround = countBombs + '0';
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (i == posY && j == posX)
			{
				winField[i][j] = '_';
				field[i][j] = bombsAround;
				return 0;
			}
		}
	return -1;

}
//Само открытие пустых клеток
int OpenSpace(int posX, int posY, int bombs, int cache[])
{
	
	
	//Была ли эта клетка уже проверена
	for (int i = 0; i < 8*8; i++)
	{
		if (cache[i] == 0)
		{
			cache[i] = (posX+1) * 10 + (posY+1);
			break;
		}
		else if (cache[i] == (posX + 1) * 10 + (posY + 1))
			return;
		
	}

	if (bombs != 0)
	{
		return SetNumberCell(posX, posY, bombs);
	}
	else
	{
		
		//Левый верхний угол относительной той клетки которую мы выбрали
		int localX = -1;
		int localY = -1;
		while (localY != 2)
		{
			int aroundBombs = CountBobsAround(posX + localX, posY + localY);
			SetNumberCell(posX, posY, aroundBombs);
			//ограничение posXY
			posX = Ogranichenie(posX);
			posY = Ogranichenie(posY);
			if (posX == 0 || posY == 0 || posX == 8 || posY == 8)
				break;
			
			//Открытие еще клетки и подсчет кол бомб вокруг 
			OpenSpace(posX + localX, posY + localY, aroundBombs,cache);
			
			if (localX == 1)
			{
				localX = -1;
				localY++;
			}
			localX++;
			
		}
	}
	return 0;
	
}

int Ogranichenie(int a)
{
	if (a < 0)
		return 0;
	else if (a > 8)
		return 8;
	else
		return a;
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
		{
				field[i][j] = '#';
				winField[i][j] = '#';
		}
	
	if (iteration == 0)
		GetBombs();
	for (int i = 0; i < MINES; i++)
	{
		bombsField[bombX[i]][bombY[i]] = 1;
		winField[bombX[i]][bombY[i]] = '*';
	}
	
	PrintField();
	printf("\n");
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
			if (winField[i][j] == win)
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