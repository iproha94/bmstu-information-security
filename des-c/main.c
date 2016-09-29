#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <time.h>
#include <stdlib.h>

char *SOURCE_FILE = "../data/source_file.txt";
char *CIPHER_FILE = "../data/cipher_file.txt";
char *PLAIN_FILE_TEMP = "../data/plain_file_temp.txt";
char *PLAIN_FILE = "../data/plain_file.txt";


size_t SIZE_TABLE = 64;
size_t NUM_KEYS = 16;


char table_1[] = {
	58,	50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
};

char table_8[] = {
	40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25
};


size_t SIZE_TABLE_5 = 28;
char table_5_C[] = {
	57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36
};

char table_5_D[] = {
	63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4	
};

size_t SIZE_TABLE_7 = 48;
char table_7[] = {
	14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4,
	26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40,
	51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};

long permutation_bit(long data, char i_from, char i_to) {
	return (data >> (i_from - 1) & 1) << i_to;
}

long permutation(long data, char* table, size_t size_table) {
	long b = 0;

	for (int i = 0; i < size_table; ++i) {
		b |= permutation_bit(data, table[i], i);
	}

	return b;
}

long feistel(int a, long k) {

	return k;
}

long _enciphering(long block, long k[NUM_KEYS]) {
	long left_i = block >> 32 ;
	long right_i = block & 0x00000000FFFFFFFF;

	// printf("%ld, %ld, %ld \n", block, left_i, right_i);

	long left_i1;
	long right_i1;

	for (int i = 0; i < 16; ++i) {
		left_i1 = right_i;
		right_i1 = left_i ^ feistel(right_i, k[i]);

		right_i = right_i1;
		left_i = left_i1;

		// printf("%ld, %ld \n", left_i, right_i);

	}

	block = 0;
	block |= left_i1 << 32;
	block |= right_i1;

	// printf("%ld\n", block);

	return block;
}

void enciphering(long k[NUM_KEYS]) {
	FILE *f_source, *f_cipher;

	if ((f_source = fopen(SOURCE_FILE, "rb")) == NULL) {
		printf("Ошибка при открытии source_file.\n");
    	exit(1);
	}

	if ((f_cipher = fopen(CIPHER_FILE, "wb")) == NULL) {
		printf("Ошибка при открытии cipher_file.\n");
    	exit(1);
	}

	long temp;
	while (fread(&temp, sizeof(long), 1, f_source) == 1) {
		temp = permutation(temp, table_1, SIZE_TABLE);
		temp = _enciphering(temp, k);
		temp = permutation(temp, table_8, SIZE_TABLE);

		fwrite(&temp, sizeof(long), 1, f_cipher);
	}
	temp = permutation(temp, table_1, SIZE_TABLE);
	temp = _enciphering(temp, k);
	temp = permutation(temp, table_8, SIZE_TABLE);

	fwrite(&temp, sizeof(long), 1, f_cipher);

	long size_file = ftell(f_source);
	fwrite(&size_file, sizeof(long), 1, f_cipher);

	fclose(f_source);
	fclose(f_cipher);
}

long _deciphering(long block, long k[NUM_KEYS]) {
	long left_i = block >> 32 ;
	long right_i = block & 0x00000000FFFFFFFF;

	long left_i_1;
	long right_i_1;

	for (int i = 15; i >= 0; --i) {
		right_i_1 = left_i;
		left_i_1 = right_i ^ feistel(left_i, k[i]);

		right_i = right_i_1;
		left_i = left_i_1;
	}

	block = 0;
	block |= left_i_1 << 32;
	block |= right_i_1;

	return block;
}

long deciphering(long k[NUM_KEYS]) {
	FILE *f_plain, *f_cipher;

	if ((f_plain = fopen(PLAIN_FILE_TEMP, "wb")) == NULL) {
		printf("Ошибка при открытии plain_file.\n");
    	exit(1);
	}

	if ((f_cipher = fopen(CIPHER_FILE, "rb")) == NULL) {
		printf("Ошибка при открытии cipher_file.\n");
    	exit(1);
	}

	// fread(&num_end_block, sizeof(long), 1, f_cipher);
	long temp;
	long end_temp;
	while (fread(&temp, sizeof(long), 1, f_cipher) == 1) {
		end_temp = temp;
		temp = permutation(temp, table_1, SIZE_TABLE);
		temp = _deciphering(temp,k);
		temp = permutation(temp, table_8, SIZE_TABLE);
		fwrite(&temp, sizeof(long), 1, f_plain);
	}

	fclose(f_plain);
	fclose(f_cipher);

	return end_temp;
}

void trunc_cipher_file(long end_temp) {
	FILE *f_plain, *f_plain2;


	if ((f_plain = fopen(PLAIN_FILE_TEMP, "rb")) == NULL) {
		printf("Ошибка при открытии .\n");
    	exit(1);
	}

	if ((f_plain2 = fopen(PLAIN_FILE, "wb")) == NULL) {
		printf("Ошибка при открытии.\n");
    	exit(1);
	}

	char c;

	for (int i = 0; i < end_temp; ++i) {
		fread(&c, sizeof(char), 1, f_plain);
		fwrite(&c, sizeof(char), 1, f_plain2);
	}

	fclose(f_plain);
	fclose(f_plain2);
}

int main() {
	srand(time(NULL));

	printf("Start des encoding \n");

	if (sizeof(long) != 8) {
		printf("This programm does not work, because sizeof(long) == %d != 8 ", sizeof(long));
    	exit(1);
	}

	if (sizeof(int) != 4) {
		printf("This programm does not work, because sizeof(int) == %d != 4 ", sizeof(long));
    	exit(1);
	}

	long key = *"abcdefgh";

	//по 28 бит
	long c_i;
	long d_i;

	c_i = permutation(key, table_5_C, SIZE_TABLE_5) << 28;
	d_i = permutation(key, table_5_D, SIZE_TABLE_5);

	//по 48 бит 
	long k[NUM_KEYS];

	for (int i = 0; i < 16; ++i) {
		//56 бит
		long k_i = 0;

		//todo сдвинуть cidi
		
		k_i |= d_i;
		k_i |= c_i;

		k[i] = 0;
		k[i] = permutation(k_i, table_7, SIZE_TABLE_7);
	}

	//todo убрать
	for (int i = 0; i < 16; ++i) {
		k[i] = rand();
	}

	enciphering(k);
	long end = deciphering(k);
	trunc_cipher_file(end);

	return 0;
} 
