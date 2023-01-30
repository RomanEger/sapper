#include "methods.h"
//void Level()
//{
//	int lvl;
//	printf("�������� ������� ���������\n1. ������� (1-10 ���, ���� 9�9).\n2. ������� (1-40 ���, ���� 16�16).\n");
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
//			printf("������� ������������ ��������, ������� ����� ������ ��� �����������...");
//			getchar();
//			system("cls");
//			Level();
//			break;
//		}
//	}
//}

int bombs[MINES][2];

//������� ����
char field[SIDE][SIDE];

//���� � ������
int bombsField[SIDE][SIDE];

//��� �������� �� ������
char winField[SIDE][SIDE];

//���������� ���� �� ���������
int bombX[MINES];

//���������� ���� �� �����������
int bombY[MINES];

//������������ �������� ���� � ����� ����
void FinalField()
{
	for (int i = 0; i < SIDE; i++)
		for (int j = 0; j < SIDE; j++)
			if (bombsField[i][j] == 0)
				field[i][j] = '_';
			else
				field[i][j] = '*';
}

//����� �������� ���� �� �����
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

//���������� �������, ��������� � ����������
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
		printf("������� ������������ ��������, ���������� ������.\n");
		ReadPosition();
	}
}

//��������� ������ ���� ����� ��� ��������� �� ����� ���������
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
		printf("������� ������������ ��������, ���������� ������.\n");
		Restart();
	}
}

//������� ��������� � ���������, ���� ����� ����� �� ����, ������������ ���-�� ��� ������ 
//� ������ ������� �� ��������� �������
int SetPos()
{
	printf("������� �������� �� ����������� �� 1 �� 9:\t");
	int posX = ReadPosition();
	printf("������� �������� �� ��������� �� 1 �� 9:\t");
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

	//������
	if (bombY > 0 && bombsField[bombY - 1][bombX] == 1)
		{
			countBombsAround++;
		}
	//������ �����
	if (bombX > 0 && bombY > 0 && bombsField[bombY - 1][bombX - 1] == 1)
	{
		countBombsAround++;
	}
	//������ ������
	if (bombY > 0 && bombX < SIDE-1 && bombsField[bombY - 1][bombX + 1] == 1)
		{
			countBombsAround++;
		}
	//�����
	if (bombX > 0 && bombsField[bombY][bombX - 1] == 1)
		{
			countBombsAround++;
		}
	//������
	if (bombX < SIDE-1 && bombsField[bombY][bombX + 1] == 1)
	{
		countBombsAround++;
	}
	//�����
	if (bombY < SIDE-1 && bombsField[bombY + 1][bombX] == 1)
	{
		countBombsAround++;
	}
	//����� �����
	if (bombY < SIDE-1 && bombX > 0 && bombsField[bombY + 1][bombX - 1] == 1)
		{
			countBombsAround++;
		}
	//����� ������
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

//������� �� ����� ���������� ����
//������ ��� ������ 
void BombCoord()
{
	for (int i = 0; i < MINES; i++)
	{
		printf("%d: %d %d\t\t", i, bombY[i], bombX[i]);
		printf("\n");
	}
}

//��������� ������� ����, ���������� ����, �������� ������� ������ ���� �� �����
void StartField(int iteration)
{
	int n = 0;

	srand(time(NULL));
	
	//���������� ������� ��������� ���������� ���������� �� 0 �� 7 ������������
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

//���������� ����
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

//���������, ���������� �� ������� ������
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

//"�������" ������ � ������������ ���� ��� �������� ����
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
	setlocale(LC_ALL, "Ru"); //�����������
	
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