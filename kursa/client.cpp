#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "client.h"

#include "db.h"

#define INDEX_FILENAME "client.ind"
#define DATA_FILENAME "client.dat"

FILE* client_data_file, * client_index_file;

typedef struct client_true_s {
	char fio[CLIENT_FIO_LENGTH];
	char address[CLIENT_ADDRESS_LENGTH];
} client_true;

int init_client_bd() {
	client_index_file = fopen(INDEX_FILENAME, "rb+");
	if (client_index_file == NULL) { // Если файла не существует
		client_index_file = fopen(INDEX_FILENAME, "wb+");
		if (client_index_file == NULL) {
			fprintf(stderr, "Unable to create %s file", INDEX_FILENAME);
			return -1;
		}
	}
	client_data_file = fopen(DATA_FILENAME, "rb+");
	if (client_data_file == NULL) {
		client_data_file = fopen(DATA_FILENAME, "wb+");
		if (client_data_file == NULL) {
			fprintf(stderr, "Unable to create %s file", DATA_FILENAME);
			return -1;
		}
	}
	return 0;
}

int get_client(unsigned long id, client* client)
{
	db_index index;
	client_true client_t;
	if (get_m_index(client_index_file, id, &index) < 0)
		return -1;

	if (get_data_by_index(client_data_file, &index, sizeof(client_true), &client_t) < 0) {
		return -1;
	}

	strcpy(client->fio, client_t.fio);
	strcpy(client->address, client_t.address);

	client->id = index.key;
	return 0;
}


int update_client(client* client) {
	client_true client_t;
	strcpy(client_t.fio, client->fio);
	strcpy(client_t.address, client->address);
	if (update_m(client_index_file, client_data_file, client->id, sizeof(client_true), &client_t))
		return -1;
	return 0;
}

int delete_client(long id) {
	if (del_m(&client_index_file, INDEX_FILENAME, id))
		return -1;
	return 0;
}

int insert_client(client* client) {
	client_true client_t;
	long id;
	strcpy(client_t.fio, client->fio);
	strcpy(client_t.address, client->address);
	id = insert_m(client_index_file, client_data_file, sizeof(client_true), &client_t);
	if (id < 0)
		return -1;
	client->id = id;
	return 0;
}

long get_clients_count() {
	return get_count(client_index_file);
}

int get_all_clients(client* clients, size_t size) {
	db_index* indexes;
	long count = get_count(client_index_file);
	long total_elements;
	if (count < 0)
		return -1;

	indexes = (db_index*)malloc(sizeof(db_index) * count);

	total_elements = get_all_indexes(client_index_file, indexes, count);

	if (total_elements < 0) {
		free(indexes);
		return -1;
	}

	if (total_elements > size) {
		total_elements = size;
	}

	for (int i = 0; i < total_elements; i++) {
		client_true client_t;
		if (get_data_by_index(client_data_file, indexes + i, sizeof(client_true), &client_t)) {
			free(indexes);
			return -1;
		}

		strcpy(clients[i].fio, client_t.fio);
		strcpy(clients[i].address, client_t.address);
		clients[i].id = indexes[i].key;
	}
	free(indexes);
	return total_elements;
}