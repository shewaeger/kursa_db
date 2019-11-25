#define _CRT_SECURE_NO_WARNINGS

#include "tasks.h"
#include <string.h>
#include "driver.h"
#include "transport.h"
#include "client.h"
#include "flights.h"
#include <stdio.h>
#include <malloc.h>

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
	driver driver;
	printf("������� ��� ��������:");
	fgets(driver.fio, FIO_LENGTH, stdin);
	driver.fio[strlen(driver.fio) - 1] = 0;
	insert_driver(&driver);
	
	printf("�������� ����� ��������:\n id = %d, ��� = %s\n", driver.id, driver.fio);
	return 0;
}

int edit_driver(){
	driver driver;
	char str[50];
	long size = 0;
	long id = get_digits_from_input("������� id ��������: ");
	
	if (get_driver(id, &driver)) {
		printf("������. �� ������ id\n");
		return -1;
	}

	printf("���������� ������: \n id = %d, ��� = %s\b", driver.id, driver.fio);

	printf("������� ���: ");
	fgets(str, 49, stdin);
	str[strlen(str) - 1] = 0;
	strcpy(driver.fio, str);
	update_driver(&driver);
}

int delete_driver_task(){
	long id = get_digits_from_input("������� id ��������: ");
	if (delete_driver(id)) {
		printf("�� ������� ������� �������� � id = %d\n", id);
		return -1;
	}
	delete_flight_where_driver_id_is(id);
	return 0;
}

int show_driver() {
	driver driver;
	long id = get_digits_from_input("������� id ��������: ");
	
	if (get_driver(id, &driver)) {
		printf("������. �� ������ id\n");
		return -1;
	}

	printf("��������:\n id = %d, ��� = %s\n", driver.id, driver.fio);
	return 0;
}

int show_all_drivers() {
	long total_size;
	long count = get_drivers_count();
	driver* drivers = (driver*)malloc(count * sizeof(driver));

	total_size = get_all_drivers(drivers, count);

	printf("----------------------------------------------------------\n");
	printf("| id  |                       ���                        |\n");
	printf("----------------------------------------------------------\n");
	for (int i = 0; i < total_size; i++) {
		printf("|%5d|%*s|\n", drivers[i].id, FIO_LENGTH, drivers[i].fio);
	}
	printf("----------------------------------------------------------\n");
	free(drivers);
	return 0;
}

int add_transport() {
	transport transport;
	printf("������� ������ ����������: ");
	
	fgets(transport.model, TRANSPORT_MODEL_LENGTH, stdin);
	transport.model[strlen(transport.model) - 1] = 0;
	printf("������� ����� ����������: ");
	fgets(transport.number, TRANSPORT_NUM_LENGTH, stdin);
	transport.number[strlen(transport.number) - 1] = 0;

	insert_transport(&transport);

	printf("�������� ����� ���������:\n id = %d, ������ = %s, ����� = %s\n", transport.id, transport.model, transport.number);
	return 0;
}

int edit_transport() {
	transport transport;
	char str[50];
	long size = 0;
	long id = get_digits_from_input("������� id ����������: ");

	if (get_transport(id, &transport)) {
		printf("������. �� ������ id\n");
		return -1;
	}

	printf("���������� ������:\n id = %d, ������ = %s, ����� = %s\n", transport.id, transport.model, transport.number);

	printf("������� ������: ");
	fgets(str, TRANSPORT_MODEL_LENGTH - 1, stdin);
	str[strlen(str) - 1] = 0;
	strcpy(transport.model, str);

	printf("������� �����: ");
	fgets(str, TRANSPORT_NUM_LENGTH - 1, stdin);
	str[strlen(str) - 1] = 0;
	strcpy(transport.number, str);

	update_transport(&transport);
}

int delete_transport_task() {
	long id = get_digits_from_input("������� id ����������: ");
	if (delete_transport(id)) {
		printf("�� ������� ������� ��������� � id = %d\n", id);
		return -1;
	}
	delete_flight_where_transport_id_is(id);
	return 0;
}

int show_transport() {
	transport transport;
	long id = get_digits_from_input("������� id ����������: ");

	if (get_transport(id, &transport)) {
		printf("������. �� ������ id\n");
		return -1;
	}

	printf("���������:\n id = %d, ������ = %s, ����� = %s\n", transport.id, transport.model, transport.number);
	return 0;
}

int show_all_transports() {
	long total_size;
	long count = get_transports_count();
	transport* transports = (transport*)malloc(count * sizeof(transport));

	total_size = get_all_transports(transports, count);

	printf("---------------------------------------------------------------------\n");
	printf("| id  |                       ������                     |  �����   |\n");
	printf("---------------------------------------------------------------------\n");
	for (int i = 0; i < total_size; i++) {
		printf("|%5d|%*s|%*s|\n", transports[i].id, TRANSPORT_MODEL_LENGTH, transports[i].model, TRANSPORT_NUM_LENGTH, transports[i].number);
	}
	printf("---------------------------------------------------------------------\n");
	free(transports);
	return 0;
}

int add_flight() {
	flight flight;
	long res;
	while (true) {
		driver driver;
		res = get_digits_from_input("������� id �������� (��� 0 ��� �� �����): ");
		if (res == 0)
			return 0;
		if (get_driver(res, &driver)) {
			printf("�������� �� ������.\n");
			continue;
		}

		printf("��������� ��������:\nid = %d, ��� = %s\n", driver.id, driver.fio);
		flight.id_driver = driver.id;
		break;
	}

	while (true) {
		transport transport;
		res = get_digits_from_input("������� id ���������� (��� 0 ��� �� �����): ");
		if (res == 0)
			return 0;
		if (get_transport(res, &transport)) {
			printf("��������� �� ������.\n");
			continue;
		}

		printf("��������� ���������:\n id = %d, ������ = %s, ����� = %s\n", transport.id, transport.model, transport.number);
		flight.id_transport = transport.id;
		break;
	}

	while (true) {
		client client;
		res = get_digits_from_input("������� id ������� (��� 0 ��� �� �����): ");
		if (res == 0)
			return 0;
		if (get_client(res, &client)) {
			printf("������ �� ������.\n");
			continue;
		}

		printf("��������� ������:\n id = %d, ��� = %s, ����� = %s\n", client.id, client.fio, client.address);
		flight.id_client = client.id;
		break;
	}
	
	insert_flight(&flight);
	return 0;

}

int edit_flight() {
	flight flight;
	long res;
	res = get_digits_from_input("������� id �����");
	if (get_flight(res, &flight)) {
		printf("���� �� ������.");
		return -1;
	}
	while (true) {
		driver driver;
		res = get_digits_from_input("������� id �������� (��� 0 ��� �� ����������): ");
		if (res == 0)
			break;
		if (get_driver(res, &driver)) {
			printf("�������� �� ������.\n");
			continue;
		}

		printf("��������� ��������:\nid = %d, ��� = %s", driver.id, driver.fio);
		flight.id_driver = driver.id;
		break;
	}

	while (true) {
		transport transport;
		res = get_digits_from_input("������� id ���������� (��� 0 ��� �� ����������): ");
		if (res == 0)
			break;
		if (get_transport(res, &transport)) {
			printf("��������� �� ������.\n");
			continue;
		}

		printf("��������� ���������:\n id = %d, ������ = %s, ����� = %s\n", transport.id, transport.model, transport.number);
		flight.id_transport = transport.id;
		break;
	}

	while (true) {
		client client;
		res = get_digits_from_input("������� id ������� (��� 0 ��� �� ����������): ");
		if (res == 0)
			break;
		if (get_client(res, &client)) {
			printf("������ �� ������.\n");
			continue;
		}

		printf("��������� ������:\n id = %d, ��� = %s, ����� = %s\n", client.id, client.fio, client.address);
		flight.id_client = client.id;
		break;
	}

	update_flight(&flight);
	return 0;
}

int delete_flight_task() {
	long id = get_digits_from_input("������� id �����: ");
	if (delete_flight(id)) {
		printf("�� ������� ������� ���� � id = %d\n", id);
		return -1;
	}
	return 0;
}

int show_flight() {
	flight flight;
	client client;
	driver driver;
	transport transport;
	long id = get_digits_from_input("������� id �����: ");
	if (get_flight(id, &flight)) {
		printf("�� ������� ����� ����\n");
		return -1;
	}

	get_client(flight.id_client, &client);
	get_driver(flight.id_driver, &driver);
	get_transport(flight.id_transport, &transport);

	printf("������:\n id = %d, ��� = %s, ����� = %s\n", client.id, client.fio, client.address);
	printf("���������:\n id = %d, ������ = %s, ����� = %s\n", transport.id, transport.model, transport.number);
	printf("��������:\n id = %d, ��� = %s\n", driver.id, driver.fio);
	return 0;
}

int show_all_flights() {
	long total_size;
	long count = get_flights_count();
	flight* flights = (flight*)malloc(count * sizeof(flight));

	total_size = get_all_flights(flights, count);

	printf("-----------------------------------------------------------\n");
	printf("|  id   |  id �������   |  id ����������  |  id ��������  |\n");
	printf("-----------------------------------------------------------\n");
	for (int i = 0; i < total_size; i++) {
		printf("|%7d|%15d|%17d|%15d|\n", flights[i].id, flights[i].id_client, flights[i].id_transport, flights[i].id_driver);
	}
	printf("--------------------------------------------------------------------------------------------------------------\n");
	free(flights);
	return 0;
}

int add_client() {
	client client;
	printf("������� ��� �������: ");
	fgets(client.fio, FIO_LENGTH, stdin);
	client.fio[strlen(client.fio) - 1] = 0;

	printf("������� ����� �������: ");
	fgets(client.address, CLIENT_ADDRESS_LENGTH, stdin);
	client.address[strlen(client.address) - 1] = 0;
	insert_client(&client);

	printf("�������� ����� ������:\n id = %d, ��� = %s, ����� = %s\n", client.id, client.fio, client.address);
	return 0;
}

int edit_client() {
	client client;
	char str[50];
	long size = 0;
	long id = get_digits_from_input("������� id �������: ");

	if (get_client(id, &client)) {
		printf("������. �� ������ id\n");
		return -1;
	}

	printf("���������� ������:\n id = %d, ��� = %s, ����� = %s\n", client.id, client.fio, client.address);

	printf("������� ���: ");
	fgets(str, 49, stdin);
	str[strlen(str) - 1] = 0;
	strcpy(client.fio, str);

	printf("������� �����: ");
	fgets(str, 49, stdin);
	str[strlen(str) - 1] = 0;
	strcpy(client.address, str);

	update_client(&client);
}

int delete_client_task() {
	long id = get_digits_from_input("������� id �������: ");
	if (delete_client(id)) {
		printf("�� ������� ������� ������� � id = %d\n", id);
		return -1;
	}
	delete_flight_where_client_id_is(id);
	return 0;
}

int show_client() {
	client client;
	long id = get_digits_from_input("������� id �������: ");

	if (get_client(id, &client)) {
		printf("������. �� ������ id\n");
		return -1;
	}

	printf("������:\n id = %d, ��� = %s, ����� = %s\n", client.id, client.fio, client.address);
	return 0;
}

int show_all_clients() {
	long total_size;
	long count = get_clients_count();
	client* clients = (client*)malloc(count * sizeof(client));

	total_size = get_all_clients(clients, count);

	printf("-------------------------------------------------------------------------------------------------------------\n");
	printf("| id  |                       ���                        |                    �����                         |\n");
	printf("-------------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < total_size; i++) {
		printf("|%5d|%*s|%*s|\n", clients[i].id, CLIENT_FIO_LENGTH, clients[i].fio, CLIENT_ADDRESS_LENGTH, clients[i].address);
	}
	printf("--------------------------------------------------------------------------------------------------------------\n");
	free(clients);
	return 0;
}

int driver_tasks() {
	while(true){
		printf("\n�������� ����� ����:\n");
		printf("1. �������� ��������.\n");
		printf("2. ������������� ��������.\n");
		printf("3. ������� ��������.\n");
		printf("4. �������� ��������.\n");
		printf("5. �������� ���� ���������.\n");
		printf("0. �����.\n");
	
		switch (get_digits_from_input("������� �����: ")) {
		case 1:
			add_driver();
			break;
		case 2:
			edit_driver();
			break;
		case 3:
			delete_driver_task();
			break;
		case 4:
			show_driver();
			break;
		case 5:
			show_all_drivers();
			break;
		case 0:
			return 0;
		}
	}
}

int transport_task() {
	while (true) {
		printf("\n�������� ����� ����:\n");
		printf("1. �������� ���������.\n");
		printf("2. ������������� ���������.\n");
		printf("3. ������� ���������.\n");
		printf("4. �������� ���������.\n");
		printf("5. �������� ���� ���������.\n");
		printf("0. �����.\n");
		
		switch (get_digits_from_input("������� �����: ")) {
		case 1:
			add_transport();
			break;
		case 2:
			edit_transport();
			break;
		case 3:
			delete_transport_task();
			break;
		case 4:
			show_transport();
			break;
		case 5:
			show_all_transports();
			break;
		case 0:
			return 0;
		}
	}
}

int flights_task() {
	while (true) {
		printf("\n�������� ����� ����:\n");
		printf("1. �������� ����.\n");
		printf("2. ������������� ����.\n");
		printf("3. ������� ����.\n");
		printf("4. �������� ����.\n");
		printf("5. �������� ��� �����.\n");
		printf("0. �����.\n");
		switch (get_digits_from_input("������� �����: ")) {
		case 1:
			add_flight();
			break;
		case 2:
			edit_flight();
			break;
		case 3:
			delete_flight_task();
			break;
		case 4:
			show_flight();
			break;
		case 5:
			show_all_flights();
			break;
		case 0:
			return 0;
		}
	}
}

int client_task() {
	while(true){
		printf("\n�������� ����� ����:\n");
		printf("1. �������� �������.\n");
		printf("2. ������������� �������.\n");
		printf("3. ������� �������.\n");
		printf("4. �������� �������.\n");
		printf("5. �������� ���� ��������.\n");
		printf("0. �����.\n");
		switch (get_digits_from_input("������� �����: ")) {
		case 1:
			add_client();
			break;
		case 2:
			edit_client();
			break;
		case 3:
			delete_client_task();
			break;
		case 4:
			show_client();
			break;
		case 5:
			show_all_clients();
			break;
		case 0:
			return 0;
		}
	}
}