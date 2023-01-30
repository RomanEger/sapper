#include "methods.h"
//void Level()
//{
//	int lvl;
//	printf("Выберите уровень сложности\n1. Простой (1-10 мин, поле 9х9).\n2. Средний (1-40 мин, поле 16х16).\n");
//	
//	#pragma warning(suppress : 4996)
//	scanf("%d", &lvl);
//
//	switch (lvl)
//	{
//	case 1:
//	{
//		
//		break;
//	}
//	case 2: 
//	{
//		#undef MINES
//		#define MINES 40
//		#undef SIDE
//		#define SIDE 16
//		break;
//	}
//		default: 
//		{
//			printf("Введено некорректное значение, нажмите любую кнопку для продолжения...");
//			getchar();
//			system("cls");
//			Level();
//			break;
//		}
//	}
//}

int bombs[MINES][2];

//игровое поле
char field[SIDE][SIDE];

//поле с минами
int bombsField[SIDE][SIDE];

//для проверки на победу
char winField[SIDE][SIDE];

//Координаты бомб по вертикали
int bombX[MINES];

//Координаты бомб по горизонтали
int bombY[MINES];

//демонстрация игрового поля в конце игры
void FinalField()
{
	for (int i = 0; i < SIDE; i++)
		for (int j = 0; j < SIDE; j++)
			if (bombsField[i][j] == 0)
				field[i][j] = '_';
			else
				field[i][j] = '*';
}

//вывод игрового поля на экран
void PrintField()
{
	int n = 0;
	printf("   ");
	for (int i = 1; i <= SIDE; i++)
		printf("%d ", i);
	printf("\n");
	printf("   ");
	for (int i = 1; i <= SIDE; i++)
		printf("__");
	printf("\n");

	for (int i = 0; i < SIDE; i++)
	{
		n++;
		if (i < 9)
			printf("%d |", n);
		else
			printf("%d|", n);
		for (int j = 0; j < SIDE; j++)
		{
			printf("%c ", field[i][j]);
		}
		printf("\n");
	}
}

//возвращает позицию, введенную с клавиатуры
int ReadPosition()
{
	int pos;
	#pragma warning(suppress : 4996)
	scanf("%d", &pos);

	printf("\n");
	if (pos > 0 && pos <= SIDE)
		return --pos;
	else
	{
		printf("Введены некорректные значения, попробуйте заново.\n");
		ReadPosition();
	}
}

//позволяет начать игру снова или завершить ее после проигрыша
int Restart()
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
		Restart();
	}
}

//выводит сообщение о проигрыше, если игрок попал на мину, подсчитывает кол-во мин вокруг 
//в идеале разбить на несколько функций
int SetPos()
{
	printf("Введите значение по горизонтали от 1 до 9:\t");
	int posX = ReadPosition();
	printf("Введите значение по вертикали от 1 до 9:\t");
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
	if (bombY > 0 && bombX < SIDE-1 && bombsField[bombY - 1][bombX + 1] == 1)
		{
			countBombsAround++;
		}
	//слева
	if (bombX > 0 && bombsField[bombY][bombX - 1] == 1)
		{
			countBombsAround++;
		}
	//справа
	if (bombX < SIDE-1 && bombsField[bombY][bombX + 1] == 1)
	{
		countBombsAround++;
	}
	//снизу
	if (bombY < SIDE-1 && bombsField[bombY + 1][bombX] == 1)
	{
		countBombsAround++;
	}
	//снизу слева
	if (bombY < SIDE-1 && bombX > 0 && bombsField[bombY + 1][bombX - 1] == 1)
		{
			countBombsAround++;
		}
	//снизу справа
	if (bombX < SIDE-1 && bombY < SIDE-1 && bombsField[bombY + 1][bombX + 1] == 1)
		{
			countBombsAround++;
		}
	
	char bombsAround = countBombsAround + '0';

	for(int i = 0; i < SIDE; i++)
		for (int j = 0; j < SIDE; j++)
		{
			if (i == posY && j == posX)
			{
				winField[i][j] = '_';
				field[i][j] = bombsAround;
				return 0;
			}
		}

	return 1;
}

//выводит на экран координаты бомб
//только для тестов 
void BombCoord()
{
	for (int i = 0; i < MINES; i++)
	{
		printf("%d: %d %d\t\t", i, bombY[i], bombX[i]);
		printf("\n");
	}
}

//заполняет массивы поля, координата бомб, вызывает функцию вывода поля на экран
void StartField(int iteration)
{
	int n = 0;

	srand(time(NULL));
	
	//заполнение массива координат рандомными значениями от 0 до 7 включительно
	for (int i = 0; i < SIDE; i++)
		for (int j = 0; j < SIDE; j++)
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

//генерирует мины
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

//проверяет, достигнуты ли условия победы
int CheckWin()
{
	char win = '#';
	for (int i = 0; i < SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
		{
			if (winField[i][j] == win)
			{
				return 1;
			}
		}
	}
	
	return 0;
}

//"очищает" массив с координатами бомб при рестарте игры
void Clear()
{
	for (int i = 0; i < SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
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
			//Level();
			system("cls");
			StartField(iteration);
		}


		int g = SetPos();

		win = CheckWin();
		if (win == 0)
		{
			system("cls");
			FinalField();
			PrintField();
			printf("\nYou win!\n");
			a = Restart();
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
			system("cls");
			FinalField();
			PrintField();
			a = Restart();
			iteration = 0;
			system("cls");
			Clear();
		}
	}

	return 0;
}