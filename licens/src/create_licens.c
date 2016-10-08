#include <stdio.h>
#include "get_id.h"
#include <stdlib.h>

char *LICENS_FILE = "licens.txt";


int main()
{
	FILE *f;
	if ((f = fopen(LICENS_FILE, "w")) == NULL) {
		printf("Error opening LICENS_FILE.\n");
    	exit(1);
	}

	char * str_id;
	fprintf(f, "%s", str_id = get_cpu_id());

	fclose(f);
	free(str_id);
	return 0;
}