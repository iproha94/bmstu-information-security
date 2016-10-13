#include <stdio.h>
#include <stdlib.h>

#include "get_id.h"

#define SIZE_ID_STR 29

char *LICENS_FILE = "licens.txt";

int main()
{
	FILE *f;
	if ((f = fopen(LICENS_FILE, "r")) == NULL) {
		printf("Error opening LICENS_FILE.\n");
    	exit(1);
	}

	char *str_id = NULL;
	size_t len = 0;
    ssize_t read;
	read = getline(&str_id, &len, f);

	char * my_str_id;
	my_str_id = get_cpu_id();


	if (!strcmp(str_id, my_str_id)) {
		printf("the verification is successful\n");
	} else {
		printf("the verification is fails\n");
	}

	fclose(f);
	free(my_str_id);
	free(str_id);

	
	return 0;
}