#pragma once
#define TRANSPORT_NUM_LENGTH 10
#define TRANSPORT_MODEL_LENGTH 50
typedef struct transport_s {
	long id;
	char number[TRANSPORT_NUM_LENGTH];
	char model[TRANSPORT_MODEL_LENGTH];
} transport;
int init_transport_bd();
int get_transport(unsigned long id, transport* transport);
int update_transport(transport* transport);
int delete_transport(long id);
int insert_transport(transport* transport);
int get_all_transports(transport* transports, size_t size);
long get_transports_count();