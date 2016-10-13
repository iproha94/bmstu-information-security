#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_ID_STR 29

char *INFO_FILE = ".cpuinfo.txt";

char *get_cpu_id() {
	char str_command[100];

	str_command[0] = '\0';
	strcat(str_command, "dmidecode --type processor > ");
	int status = system(strcat(str_command, INFO_FILE));

	FILE *f;
	if ((f = fopen(INFO_FILE, "r")) == NULL) {
		printf("Ошибка при открытии INFO_FILE.\n");
    	exit(1);
	}

	char * line = NULL;
	char * start_substr = NULL;
	char * id = malloc(SIZE_ID_STR);

    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, f)) != -1) {
    	if (start_substr = strstr(line, "ID")) {
    		strcpy(id, start_substr);
    		break;
    	}
    }

    if (line) free(line);

	fclose(f);

	str_command[0] = '\0';
	strcat(str_command, "rm ");
	status = system(strcat(str_command, INFO_FILE));

	return id;
} 
