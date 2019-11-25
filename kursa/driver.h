#pragma once
#define FIO_LENGTH 50
typedef struct driver_s {
	long id;
	char fio[FIO_LENGTH];
} driver;
int init_driver_bd();
int get_driver(unsigned long id, driver* driver);
int update_driver(driver* driver);
int delete_driver(long id);
int insert_driver(driver* driver);
int get_all_drivers(driver* drivers, size_t size);
long get_drivers_count();