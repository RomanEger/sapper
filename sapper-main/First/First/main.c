#include "methods.h"
//���������� ����� �������
#define SIZEOF(a) sizeof(a)/sizeof(*a)

int bombs[MINES][2];



//������� ����
char field[8][8];

int bombsField[8][8];

char winField[8][8];

//���������� ���� �� ���������
int bombX[MINES];

//���������� ���� �� �����������
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
		printf("������� ������������ ��������, ���������� ������.\n");
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
		printf("������� ������������ ��������, ���������� ������.\n");
		Read();
	}
}

int SetPos()
{
	printf("������� XY ������\t ");
	int XY = ReadPosition();
	//printf("������� �������� �� ����������� �� 1 �� 8:\t");
	int posX = (XY / 10) - 1 ;
	//printf("������� �������� �� ��������� �� 1 �� 8:\t");
	int posY = (XY % 10) - 1 ;


	//���� ����� �� ����� �� ���!!!
	for (int i = 0; i < MINES; i++)
	{
		if (bombs[i][0] == posY && bombs[i][1] == posX)
		{
			system("cls");
			printf("You lost\n");
			return 1;
		}
	}

	//int countBombsAround = CountBobsAround(posX,posY);
	
	
		
	int cache[8 * 8];
	for (int i = 0; i < 8 * 8;i++)
		cache[i] = 0;

	return OpenSpace(posX, posY,cache);

		

	
}

int CountBobsAround(int posX,int posY)
{
	int bombY = posY;
	int bombX = posX;

	int countBombsAround = 0;

	int localX = -1;
	int localY = -1;
	do
	{
		//�������� �� ����� �� ������� �������
		if (bombY + localY < 0 || bombX + localX < 0 || bombY + localY >= 8 || bombX + localX >= 8)
		{
			localX++;
			if (localX == 2)
			{
				localX = -1;
				localY++;
			}
			if (localY == 2)
				break;
			continue;
		}
		if (bombsField[bombY + localY][bombX + localX] == -1)
		{
			countBombsAround++;
		}
		localX++;
		if (localX == 2)
		{
			localX = -1;
			localY++;
		}

	} while (localY != 2);
	//������
	
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
				winField[i][j] = '.';
				field[i][j] = bombsAround;
				return 0;
			}
		}
	return -1;

}
//���� �������� ������ ������
int OpenSpace(int posX, int posY, int cache[])
{
	if (posX < 0 || posY < 0 || posX>7 || posY>7)
		return 0;
	
	//���� �� ��� ������ ��� ���������
	for (int i = 0; i < 8*8; i++)
	{
		if (cache[i] == 0)
		{
			cache[i] = (posX+1) * 10 + (posY+1);
			break;
		}
		else if (cache[i] == (posX + 1) * 10 + (posY + 1))
			return 0;	
	}
	int aroundBombs = CountBobsAround(posX, posY);

	if (aroundBombs != 0)
	{
		return SetNumberCell(posX, posY, aroundBombs);
	}
	else
	{
		
		//����� ������� ���� ������������� ��� ������ ������� �� �������
		int localX = -1;
		int localY = -1;
		do
		{
			//posX = Ogranichenie(posX);
			//posY = Ogranichenie(posY);
			//if (posX == 0 || posY == 0 || posX == 8 || posY == 8)
			//����������� posXY
			//if(posX< 0 || posY < 0 || posX>8 || posY>8)
			//	break;
			SetNumberCell(posX, posY, aroundBombs);
			
			//�������� ��� ������ � ������� ��� ���� ������ 
			OpenSpace(posX + localX, posY + localY, cache);
			
			localX++;
			if (localX == 2)
			{
				localX = -1;
				localY++;
			}
			
		} while (localY != 2);
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
	
	//���������� ������� ��������� ���������� ���������� �� 0 �� 7 ������������
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
		bombsField[bombX[i]][bombY[i]] = -1;
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
	setlocale(LC_ALL, "Ru"); //�����������
	
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