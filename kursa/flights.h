#pragma once
#define FIO_LENGTH 50
typedef struct flight_s {
	long id;
	long id_driver;
	long id_transport;
	long id_client;
} flight;
int init_flight_bd();
int get_flight(unsigned long id, flight* flight);
int update_flight(flight* flight);
int delete_flight(long id);
int insert_flight(flight* flight);
int get_all_flights(flight* flights, size_t size);
