#include "tasks.h"

#include "driver.h"
#include "transport.h"
#include "client.h"
#include "flights.h"
#include <stdio.h>

int init() {
	if (init_client_bd())
		return -1;
	if (init_transport_bd())
		return -1;
	if (init_driver_bd())
		return -1;
	if (init_flight_bd())
		return -1;
}
int add_driver() {
}

int edit_driver(){
}

int delete_driver(){
}

int show_driver() {
}

int show_all_drivers() {
}

int driver_tasks() {
	printf("Выберите пункт меню:\n");
	printf("1. Добавить водителя.\n");
	printf("2. Редактировать водителя.\n");
	printf("3. Удалить водителя.\n");
	printf("4. Показать водителя.\n");
	printf("5. Показать всех водителей.\n");
	printf("0. Назад.\n");
}

int transport_task() {
	printf("Выберите пункт меню:\n");
	printf("1. Добавить транспорт.\n");
	printf("2. Редактировать транспорт.\n");
	printf("3. Удалить транспорт.\n");
	printf("4. Показать транспорт.\n");
	printf("5. Показать весь транспорт.\n");
	printf("0. Назад.\n");
}

int flights_task() {
	printf("Выберите пункт меню:\n");
	printf("1. Добавить рейс.\n");
	printf("2. Редактировать транспорт.\n");
	printf("3. Удалить транспорт.\n");
	printf("4. Показать транспорт.\n");
	printf("5. Показать весь транспорт.\n");
	printf("0. Назад.\n");
}

int client_task() {
	printf("Выберите пункт меню:\n");
	printf("1. Добавить клиента.\n");
	printf("2. Редактировать клиента.\n");
	printf("3. Удалить клиента.\n");
	printf("4. Показать клиента.\n");
	printf("5. Показать всех клиентов.\n");
	printf("0. Назад.\n");
}