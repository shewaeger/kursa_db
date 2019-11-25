#define _CRT_SECURE_NO_WARNINGS
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
long get_digits_from_input( const char * msg)
{
	char str[50];
	while (true) {
		printf(msg);
		fgets(str, 49, stdin);
		str[49] = 0;
		for (int i = 0; i < 50 && str[i]; i++) {
			if ((str[i] < '0' || str[i] > '9') && str[i] != '\n') {
				printf("Неверное число.\n");
				continue;
			}	
		}
		return atol(str);
	}
}
