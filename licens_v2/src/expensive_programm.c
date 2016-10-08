#include <stdio.h>
#include <stdlib.h>

#include "get_id.h"

//program code should not contain sequence symbols "ID: " except in str_id

int main()
{
	char * my_str_id;
	my_str_id = get_cpu_id();

	printf("Read cpuid ");
	printf("%s\n", my_str_id);

	char * str_id = "ID: XX XX XX XX XX XX XX XX\n";
	printf("Hardcode cpuid ");
	printf("%s\n", str_id);

	if (!strcmp(str_id, my_str_id)) {
		printf("the verification is successful\n");
	} else {
		printf("the verification is fails\n");
	}

	free(my_str_id);
	return 0;
}