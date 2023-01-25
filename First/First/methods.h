#include<stdio.h> 
#include<locale.h> 
#include<stdlib.h> 
#include<time.h>
#include<conio.h>

//Выводит начальное игровое поле на консоль
void StartField(int);

//Выводит и обновляет поле в процессе игры
void PrintField(); 

//Генерирует бомбы
void GetBombs();