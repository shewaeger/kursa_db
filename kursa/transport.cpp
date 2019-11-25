#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "transport.h"

#include "db.h"

#define INDEX_FILENAME "transport.ind"
#define DATA_FILENAME "transport.dat"

FILE* transport_data_file, * transport_index_file;

typedef struct transport_true_s {
	char number[TRANSPORT_NUM_LENGTH];
	char model[TRANSPORT_MODEL_LENGTH];
} transport_true;

int init_transport_bd() {
	transport_index_file = fopen(INDEX_FILENAME, "rb+");
	if (transport_index_file == NULL) { // Если файла не существует
		transport_index_file = fopen(INDEX_FILENAME, "wb+");
		if (transport_index_file == NULL) {
			fprintf(stderr, "Unable to create %s file", INDEX_FILENAME);
			return -1;
		}
	}
	transport_data_file = fopen(DATA_FILENAME, "rb+");
	if (transport_data_file == NULL) {
		transport_data_file = fopen(DATA_FILENAME, "wb+");
		if (transport_data_file == NULL) {
			fprintf(stderr, "Unable to create %s file", DATA_FILENAME);
			return -1;
		}
	}
	return 0;
}

int get_transport(unsigned long id, transport* transport)
{
	db_index index;
	transport_true transport_t;
	if (get_m_index(transport_index_file, id, &index) < 0)
		return -1;

	if (get_data_by_index(transport_data_file, &index, sizeof(transport_true), &transport_t) < 0) {
		return -1;
	}

	strcpy(transport->number, transport_t.number);
	strcpy(transport->model, transport_t.model);
	transport->id = index.key;
	return 0;
}


int update_transport(transport* transport) {
	transport_true transport_t;
	strcpy(transport_t.number, transport->number);
	strcpy(transport_t.model, transport->model);
	if (update_m(transport_index_file, transport_data_file, transport->id, sizeof(transport_true), &transport_t))
		return -1;
	return 0;
}

int delete_transport(long id) {
	if (del_m(&transport_index_file, INDEX_FILENAME, id))
		return -1;
	return 0;
}

int insert_transport(transport* transport) {
	transport_true transport_t;
	long id;
	strcpy(transport_t.number, transport->number);
	strcpy(transport_t.model, transport->model);
	id = insert_m(transport_index_file, transport_data_file, sizeof(transport_true), &transport_t);

	if (id < 0)
		return -1;

	transport->id = id;
	return 0;
}

long get_transports_count() {
	return get_count(transport_index_file);
}

int get_all_transports(transport* transports, size_t size) {
	db_index* indexes;
	long count = get_count(transport_index_file);
	long total_elements;
	if (count < 0)
		return -1;

	indexes = (db_index*)malloc(sizeof(db_index) * count);

	total_elements = get_all_indexes(transport_index_file, indexes, count);

	if (total_elements < 0) {
		free(indexes);
		return -1;
	}

	if (total_elements > size) {
		total_elements = size;
	}

	for (int i = 0; i < total_elements; i++) {
		transport_true transport_t;
		if (get_data_by_index(transport_data_file, indexes + i, sizeof(transport_true), &transport_t)) {
			free(indexes);
			return -1;
		}

		strcpy(transports[i].number, transport_t.number);
		strcpy(transports[i].model, transport_t.model);
		transports[i].id = indexes[i].key;
	}
	free(indexes);
	return total_elements;
}