#include <stdio.h>
#include <stdlib.h>

#include "get_id.h"

//todo:  if not FIND hardcode cpuid then edit start_position
#define start_position 0

char *DATA_FILE = "data_file.out";
char *EXPENSIVE_PROGRAMM_FILE = "expensive_programm.out";

int main()
{
	FILE *f;
	if ((f = fopen(DATA_FILE, "rb")) == NULL) {
		printf("Error opening DATA_FILE.\n");
    	exit(1);
	}

	FILE *f_new;
	if ((f_new = fopen(EXPENSIVE_PROGRAMM_FILE, "wb")) == NULL) {
		printf("Error opening EXPENSIVE_PROGRAMM_FILE.\n");
    	exit(1);
	}

	
	fseek(f, start_position, SEEK_SET);

	char *my_str_id = get_cpu_id();

	int flag = 0;
	char temp[5];
	temp[4] = '\0';
	int num;
	while ((num = fread(&temp, sizeof(char), 4, f)) == 4) {
		fwrite(&temp, sizeof(char), 4, f_new);
		if (!strcmp(temp, "ID: ")) {
			printf("FIND hardcode cpuid!\n");
			flag++;
			fwrite(&(my_str_id[4]), sizeof(char), 23, f_new);
			fread(&temp, sizeof(char), 23, f);
		}

	}

	if (num) {
		fwrite(&temp, sizeof(char), num, f_new);
	}

	fclose(f_new);
	fclose(f);

	if (flag) {
		printf("the installation was successful\n");
	} else {
		printf("the installation was fails\n");
	}

	return 0;
}