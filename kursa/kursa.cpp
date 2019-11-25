#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <clocale>
#include "tasks.h"



int main() {
	setlocale(LC_ALL, "Russian");
	init();
	while (true) {
		printf("Выберите пункт меню:\n");
		printf("1. Операции с водителями\n");
		printf("2. Операции с транспортом\n");
		printf("3. Операции с клиентами\n");
		printf("4. Операции с рейсами\n");
		printf("0. Выход\n");
		switch (get_digits_from_input("Введите число: ")) {
		case 1:
			driver_tasks();
			break;
		case 2:
			transport_task();
			break;
		case 3:
			client_task();
			break;
		case 4:
			flights_task();
			break;
		case 0:
			return 0;
		}
	}
}