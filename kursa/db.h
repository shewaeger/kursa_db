#include <stdio.h>

typedef struct db_index_s {
	long key;
	long num;
} db_index;

int get_m_index(FILE *file_index, unsigned long pos, db_index * index);
int del_m(FILE** file_index,const char* filename, unsigned long pos);
int update_m(FILE* file_index, FILE* file_data, unsigned long pos, size_t size, void * buffer);
long insert_m(FILE* file_index, FILE* file_data, size_t size, void * buffer);
long get_count(FILE* file_index);
long get_all_indexes(FILE* file_index, db_index* indexes, size_t max_size);
long get_data_by_index(FILE* file_data, db_index* index, size_t data_size, void* buffer);