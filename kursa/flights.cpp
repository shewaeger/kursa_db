#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "flights.h"

#include "db.h"

#define INDEX_FILENAME "flight.ind"
#define DATA_FILENAME "flight.dat"

FILE* flight_data_file, * flight_index_file;

typedef struct flight_true_s {
	long id_driver;
	long id_transport;
	long id_client;
} flight_true;

int init_flight_bd() {
	flight_index_file = fopen(INDEX_FILENAME, "rb+");
	if (flight_index_file == NULL) { // Если файла не существует
		flight_index_file = fopen(INDEX_FILENAME, "wb+");
		if (flight_index_file == NULL) {
			fprintf(stderr, "Unable to create %s file", INDEX_FILENAME);
			return -1;
		}
	}
	flight_data_file = fopen(DATA_FILENAME, "rb+");
	if (flight_data_file == NULL) {
		flight_data_file = fopen(DATA_FILENAME, "wb+");
		if (flight_data_file == NULL) {
			fprintf(stderr, "Unable to create %s file", DATA_FILENAME);
			return -1;
		}
	}
	return 0;
}

int get_flight(unsigned long id, flight* flight)
{
	db_index index;
	flight_true flight_t;
	if (get_m_index(flight_index_file, id, &index) < 0)
		return -1;

	if (get_data_by_index(flight_data_file, &index, sizeof(flight_true), &flight_t) < 0) {
		return -1;
	}

	
	flight->id_client = flight_t.id_client;
	flight->id_driver = flight_t.id_driver;
	flight->id_transport = flight_t.id_transport;
	flight->id = index.key;
	return 0;
}


int update_flight(flight* flight) {
	flight_true flight_t;
	
	flight_t.id_client = flight->id_client;
	flight_t.id_driver = flight->id_driver;
	flight_t.id_transport = flight->id_transport;

	if (update_m(flight_index_file, flight_data_file, flight->id, sizeof(flight_true), &flight_t))
		return -1;
	return 0;
}

int delete_flight(long id) {
	if (del_m(&flight_index_file, INDEX_FILENAME, id))
		return -1;
	return 0;
}

int insert_flight(flight* flight) {
	flight_true flight_t;
	long id;
	
	flight_t.id_client = flight->id_client;
	flight_t.id_driver = flight->id_driver;
	flight_t.id_transport = flight->id_transport;

	id = insert_m(flight_index_file, flight_data_file, sizeof(flight_true), &flight_t);

	if (id < 0)
		return -1;

	flight->id = id;
	return 0;
}

long get_flights_count() {
	return get_count(flight_index_file);
}

int get_all_flights(flight* flights, size_t size) {
	db_index* indexes;
	long count = get_count(flight_index_file);
	long total_elements;
	if (count < 0)
		return -1;

	indexes = (db_index*)malloc(sizeof(db_index) * count);

	total_elements = get_all_indexes(flight_index_file, indexes, count);

	if (total_elements < 0) {
		free(indexes);
		return -1;
	}

	if (total_elements > size) {
		total_elements = size;
	}

	for (int i = 0; i < total_elements; i++) {
		flight_true flight_t;
		if (get_data_by_index(flight_data_file, indexes + i, sizeof(flight_true), &flight_t)) {
			free(indexes);
			return -1;
		}

		
		flights[i].id_client = flight_t.id_client;
		flights[i].id_transport = flight_t.id_transport;
		flights[i].id_driver = flight_t.id_driver;
		flights[i].id = indexes[i].key;
	}
	free(indexes);
	return total_elements;
}

int delete_flight_where_driver_id_is(long id)
{
	db_index* indexes;
	long * delete_list;
	size_t delete_list_size = 0;
	flight_true flight_t;
	long count = get_count(flight_index_file);
	long total_elements;
	if (count < 0)
		return -1;

	indexes = (db_index*)malloc(sizeof(db_index) * count);
	delete_list = (long*)malloc(sizeof(long) * count);

	total_elements = get_all_indexes(flight_index_file, indexes, count);

	for (int i = 0; i < total_elements; i++) {
		get_data_by_index(flight_data_file, indexes + i, sizeof(flight_true), &flight_t);
		if (flight_t.id_driver == id) {
			delete_list[delete_list_size++] = indexes[i].key;
		}
	}

	for (int i = 0; i < delete_list_size; i++) {
		del_m(&flight_index_file, INDEX_FILENAME, delete_list[i]);
	}

	free(indexes);
	free(delete_list);
}

int delete_flight_where_transport_id_is(long id)
{
	db_index* indexes;
	long* delete_list;
	size_t delete_list_size = 0;
	flight_true flight_t;
	long count = get_count(flight_index_file);
	long total_elements;
	if (count < 0)
		return -1;

	indexes = (db_index*)malloc(sizeof(db_index) * count);
	delete_list = (long*)malloc(sizeof(long) * count);

	total_elements = get_all_indexes(flight_index_file, indexes, count);

	for (int i = 0; i < total_elements; i++) {
		get_data_by_index(flight_data_file, indexes + i, sizeof(flight_true), &flight_t);
		if (flight_t.id_transport == id) {
			delete_list[delete_list_size++] = indexes[i].key;
		}
	}

	for (int i = 0; i < delete_list_size; i++) {
		del_m(&flight_index_file, INDEX_FILENAME, delete_list[i]);
	}
	free(indexes);
	free(delete_list);
}

int delete_flight_where_client_id_is(long id)
{
	db_index* indexes;
	long* delete_list;
	size_t delete_list_size = 0;
	flight_true flight_t;
	long count = get_count(flight_index_file);
	long total_elements;
	if (count < 0)
		return -1;

	indexes = (db_index*)malloc(sizeof(db_index) * count);
	delete_list = (long*)malloc(sizeof(long) * count);

	total_elements = get_all_indexes(flight_index_file, indexes, count);

	for (int i = 0; i < total_elements; i++) {
		get_data_by_index(flight_data_file, indexes + i, sizeof(flight_true), &flight_t);
		if (flight_t.id_client == id) {
			delete_list[delete_list_size++] = indexes[i].key;
		}
	}

	for (int i = 0; i < delete_list_size; i++) {
		del_m(&flight_index_file, INDEX_FILENAME, delete_list[i]);
	}
	free(indexes);
	free(delete_list);
}
