#define _CRT_SECURE_NO_WARNINGS
#include "db.h"
#include <string.h>
#include <malloc.h>

int find_index_by_key(FILE* file_index, long key, db_index* index) {
	db_index indexes[10];
	size_t size_i;
	if (fseek(file_index, 0, SEEK_SET)) {
		return -1;
	}

	while (!feof(file_index)) {
		size_i = fread(&indexes, sizeof(db_index), 10, file_index);
		if (size_i < 10 && !feof(file_index)) { // если прочитали не все и не достигли конца файла, то где то была ошибка.
			return -1;
		}

		for (int i = 0; i < size_i; i++) {
			if (indexes[i].key == key) {
				memcpy(index, indexes + i, sizeof(db_index));
				return 0;
			}
		}
	}
	return 1;
}

int get_m_index(FILE* file_index, unsigned long pos, db_index* index)
{

	if (find_index_by_key(file_index, pos, index ) != 0) {
		return 0;
	}

}

int del_m(FILE** file_index,const char * filename, unsigned long pos)
{
	long position;
	db_index* indexes;
	size_t indexes_size;

	if (fseek(*file_index, 0, SEEK_END)) {
		return -1;
	}

	position = ftell(*file_index);
	if (position < 0 || position % sizeof(db_index) != 0)
		return -1;

	indexes = (db_index *) malloc(position);
	
	if (indexes == NULL)
		return -1;
	
	if (fseek(*file_index, 0, SEEK_SET)) {
		free(indexes);
		return -1;
	}
		
	
	indexes_size = position / sizeof(db_index);
	if (fread(indexes, sizeof(db_index), indexes_size, *file_index) != indexes_size) {
		free(indexes);
		return -1;
	}
	fclose(*file_index);
	*file_index = fopen(filename, "wb+");
	if (file_index == NULL) {
		free(indexes);
		return -1;
	}
	
	for (int i = 0; i < indexes_size; i++) {
		if (indexes[i].key != pos) {
			fwrite(&indexes[i], sizeof(db_index), 1, *file_index);
		}
	}
	free(indexes);
	return 0;
}

int update_m(FILE* file_index, FILE* file_data, unsigned long pos, size_t size, void * buffer)
{
	db_index index;
	int res = find_index_by_key(file_index, pos, &index);
	if (res > 0) // если не нашел
		return 1;
	if (res < 0) //если была ошибка
		return -1;

	fseek(file_data, (index.num - 1) * size, SEEK_SET);
	
	long pos_tell = ftell(file_data);
	if (fwrite(buffer, size, 1, file_data) != 1) {
		return -1;
	}

	return 0;
}

long insert_m(FILE* file_index, FILE* file_data, size_t size, void * buffer)
{
	long position;
	long key = 0;
	db_index last_index;
	if (fseek(file_index, 0, SEEK_END)) {
		return -1; //error
	}

	position = ftell(file_index);
	
	if (position < 0) {
		return -1; //error
	}

	if (position != 0) {
		if (fseek(file_index, -(long)sizeof(db_index), SEEK_END))
			return -1; //error

		if (1 != fread(&last_index, sizeof(db_index), 1, file_index)) {
			return -1;
		}
	}
	else {
		last_index.key = 0;
	}

	last_index.key++;

	if (fseek(file_data, 0, SEEK_END)) {
		return -1;
	}

	if (ftell(file_data) % size != 0) {
		return -1; //если указатель на конец последней записи не кратен размеру, то значит мы записываем не в тот файл.
	}

	if (fwrite(buffer, size, 1, file_data) != 1) {
		return -1; //error
	}
	
	position = ftell(file_data);

	if (position < 0) {
		return -1;
	}

	last_index.num = position / size;

	if (fseek(file_index, 0, SEEK_END)) {
		return -1;
	}

	if (fwrite(&last_index, sizeof(last_index), 1, file_index) != 1) {
		return -1;
	}

	return last_index.key;
}

long get_count(FILE* file_index)
{
	long position;
	if (fseek(file_index, 0, SEEK_END))
		return -1;

	position = ftell(file_index);
	if (position < 0)
		return -1;

	return position / sizeof(db_index);
	
}

long get_all_indexes(FILE* file_index, db_index * indexes, size_t max_size)
{
	long position;
	long total_elements;
	if (fseek(file_index, 0, SEEK_END)) {
		return -1;
	}

	position = ftell(file_index);
	if (position < 0)
		return -1;

	if (max_size < position / sizeof(db_index)) {
		total_elements = max_size;
	}
	else
		total_elements = position / sizeof(db_index);

	if (fseek(file_index, 0, SEEK_SET)) {
		return -1;
	}

	if (fread(indexes, sizeof(db_index), total_elements, file_index) != total_elements) {
		return -1;
	}
	return total_elements;
}

long get_data_by_index(FILE* file_data, db_index* index, size_t data_size, void* buffer) {
	if (fseek(file_data, (index->num - 1) * data_size, SEEK_SET)) {
		return -1;
	}

	if (fread(buffer, data_size, 1, file_data) != 1) {
		return -1;
	}

	return 0;
}