#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#include <clocale>



int main() {
	setlocale(LC_ALL, "Russian");

	printf("Выберите пункт меню:\n");
	printf("1. Операции с водителями\n");
	printf("2. Операции с транспортом\n");
	printf("3. Операции с клиентами\n");
	printf("4. Операции с рейсами\n");

}