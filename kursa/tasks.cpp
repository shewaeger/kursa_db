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
	printf("�������� ����� ����:\n");
	printf("1. �������� ��������.\n");
	printf("2. ������������� ��������.\n");
	printf("3. ������� ��������.\n");
	printf("4. �������� ��������.\n");
	printf("5. �������� ���� ���������.\n");
	printf("0. �����.\n");
}

int transport_task() {
	printf("�������� ����� ����:\n");
	printf("1. �������� ���������.\n");
	printf("2. ������������� ���������.\n");
	printf("3. ������� ���������.\n");
	printf("4. �������� ���������.\n");
	printf("5. �������� ���� ���������.\n");
	printf("0. �����.\n");
}

int flights_task() {
	printf("�������� ����� ����:\n");
	printf("1. �������� ����.\n");
	printf("2. ������������� ���������.\n");
	printf("3. ������� ���������.\n");
	printf("4. �������� ���������.\n");
	printf("5. �������� ���� ���������.\n");
	printf("0. �����.\n");
}

int client_task() {
	printf("�������� ����� ����:\n");
	printf("1. �������� �������.\n");
	printf("2. ������������� �������.\n");
	printf("3. ������� �������.\n");
	printf("4. �������� �������.\n");
	printf("5. �������� ���� ��������.\n");
	printf("0. �����.\n");
}