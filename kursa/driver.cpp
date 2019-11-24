#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "driver.h"

#include "db.h"

#define INDEX_FILENAME "driver.ind"
#define DATA_FILENAME "driver.dat"

FILE *driver_data_file, *driver_index_file;

typedef struct driver_true_s {
	char fio[FIO_LENGTH];
} driver_true;

int init_driver_bd() {
	driver_index_file = fopen(INDEX_FILENAME, "rb+");
	if (driver_index_file == NULL) { // Если файла не существует
		driver_index_file = fopen(INDEX_FILENAME, "wb+");
		if (driver_index_file == NULL) {
			fprintf(stderr, "Unable to create %s file", INDEX_FILENAME);
			return -1;
		}
	}
	driver_data_file = fopen(DATA_FILENAME, "rb+");
	if (driver_data_file == NULL) {
		driver_data_file = fopen(DATA_FILENAME, "wb+");
		if (driver_data_file == NULL) {
			fprintf(stderr, "Unable to create %s file", DATA_FILENAME);
			return -1;
		}
	}
	return 0;
}

int get_driver(unsigned long id, driver *driver)
{
	db_index index;
	driver_true driver_t;
	if (get_m_index(driver_index_file, id, &index) < 0)
		return -1;

	if (get_data_by_index(driver_data_file, &index, sizeof(driver_true), &driver_t) < 0) {
		return -1;
	}

	strcpy(driver->fio, driver_t.fio);
	
	driver->id = index.key;
	return 0;
}


int update_driver(driver* driver) {
	driver_true driver_t;
	strcpy(driver_t.fio, driver->fio);

	if (update_m(driver_index_file, driver_data_file, driver->id, sizeof(driver_true), &driver_t))
		return -1;
	return 0;
}

int delete_driver(long id) {
	if (del_m(&driver_index_file, INDEX_FILENAME, id))
		return -1;
	return 0;
}

int insert_driver(driver* driver) {
	driver_true driver_t;
	long id;
	strcpy(driver_t.fio, driver->fio);
	id = insert_m(driver_index_file, driver_data_file, sizeof(driver_true), &driver_t);
	
	if(id < 0)
		return -1;
	
	driver->id = id;
	return 0;
}

long get_drivers_count() {
	return get_count(driver_index_file);
}

int get_all_drivers(driver* drivers, size_t size) {
	db_index* indexes;
	long count = get_count(driver_index_file);
	long total_elements;
	if (count < 0)
		return -1;
	
	indexes = (db_index *) malloc(sizeof(db_index) * count);
	
	total_elements = get_all_indexes(driver_index_file, indexes, count);
	
	if (total_elements < 0) {
		free(indexes);
		return -1;
	}

	if (total_elements > size) {
		total_elements = size;
	}
	
	for (int i = 0; i < total_elements; i++) {
		driver_true driver_t;
		if (get_data_by_index(driver_data_file, indexes + i, sizeof(driver_true), &driver_t)) {
			free(indexes);
			return -1;
		}

		strcpy(drivers[i].fio, driver_t.fio);
		drivers[i].id = indexes[i].key;
	}
	free(indexes);
	return total_elements;
}