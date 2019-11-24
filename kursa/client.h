#pragma once
#pragma once
#define CLIENT_FIO_LENGTH 50
#define CLIENT_ADDRESS_LENGTH 50
typedef struct client_s {
	long id;
	char fio[CLIENT_FIO_LENGTH];
	char address[CLIENT_ADDRESS_LENGTH];
} client;
int init_client_bd();
int get_client(unsigned long id, client* client);
int update_client(client* client);
int delete_client(long id);
int insert_client(client* client);
int get_all_clients(client* clients, size_t size);
