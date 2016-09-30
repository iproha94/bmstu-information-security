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

size_t SIZE_TABLE_2 = 48;
char table_2[] = {
	32, 1, 2, 3, 4, 5,
	4, 5, 6, 7, 8, 9,
	8, 9, 10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32, 1
};

size_t SIZE_TABLE_6 = 16;
char table_6[] = {
	1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

size_t SIZE_TABLE_9 = 16;
char table_9[] = {
	0
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

size_t SIZE_TABLE_4 = 32;
char table_4[] = {
	16, 7, 20, 21, 29, 12, 28, 17,
	1, 15, 23, 26, 5, 18, 31, 10,
	2, 8, 24, 14, 32, 27, 3, 9,
	19, 13, 30, 6, 22, 11, 4, 25
};

#define SIZE_TABLE_3_I1 8
#define SIZE_TABLE_3_I2 4
#define SIZE_TABLE_3_I3 16

char table_3[SIZE_TABLE_3_I1][SIZE_TABLE_3_I2][SIZE_TABLE_3_I3] = {
	{
		{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
		{0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
		{4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
		{15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
	},

	{	
		{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
		{3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
		{0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
		{13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}	
	},

	{
		{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},	
		{13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
		{13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7}, 
		{1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}	
	},

	{
		{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15}, 
		{13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9}, 
		{10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4}, 
		{3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14} 
	},

	{
		{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9}, 
		{14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6}, 
		{4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14}, 
		{11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}	
	},

	{	
		{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11}, 
		{10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8}, 
		{9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6}, 
		{4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}	
	},

	{	
		{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1}, 
		{13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6}, 
		{1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2}, 
		{6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}	
	},

	{	
		{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7}, 
		{1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2}, 
		{7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8}, 
		{2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}	
	}
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

long feistel(long a, long k) {
	//k - 48бит 
	//48бит
	a = permutation(a, table_2, SIZE_TABLE_2);

	a ^= k;

	long result = 0;

	int num_b_block = 8;
	int bit_in_block = 6;
	long b;

	for (int i = 0; i < num_b_block; ++i) {
		long temp = a;
		int right = sizeof(long) * 8 - bit_in_block * (i + 1);

		//обнуляем левую часть
		temp <<= right;
		temp >>= right;

		b = temp >> (i * bit_in_block); 

		long ia = b & 0x20;
		ia >>= 4;
		ia |= (b & 0x1);

		long ib = b & 0x1F;
		ib >>= 1;

		b = table_3[i][ia][ib];

		result |= b << ((num_b_block - i - 1) * 4);
	}


	return permutation(result, table_4, SIZE_TABLE_4);
}

long _enciphering(long block, long k[NUM_KEYS]) {
	long left_i = block >> 32 ;
	long right_i = block & 0x0FFFFFFFF;

	long left_i1;
	long right_i1;

	for (int i = 0; i < 16; ++i) {
		left_i1 = right_i;
		right_i1 = left_i ^ feistel(right_i, k[i]);

		right_i = right_i1;
		left_i = left_i1;
	}

	block = 0;
	block |= left_i1 << 32;
	block |= right_i1;

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
	int num;
	while ((num = fread(&temp, sizeof(char), 8, f_source)) == 8) {
		temp = permutation(temp, table_1, SIZE_TABLE);
		temp = _enciphering(temp, k);
		temp = permutation(temp, table_8, SIZE_TABLE);

		fwrite(&temp, sizeof(long), 1, f_cipher);
	}

	if (num) {
		temp = permutation(temp, table_1, SIZE_TABLE);
		temp = _enciphering(temp, k);
		temp = permutation(temp, table_8, SIZE_TABLE);
		fwrite(&temp, sizeof(long), 1, f_cipher);
	}


	long size_file = ftell(f_source);
	fwrite(&size_file, sizeof(long), 1, f_cipher);

	fclose(f_source);
	fclose(f_cipher);
}

long _deciphering(long block, long k[NUM_KEYS]) {
	long left_i = block >> 32 ;
	long right_i = block & 0x0FFFFFFFF;

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

long cicle_shift(long k) {
	long bit56 = k & 0x80000000000000;
	bit56 >>= 55;
	k <<= 1;
	k &= 0xFFFFFFFFFFFFFF;
	k |= bit56;

	return k;
}

void getArrKeys(long key, long *k) {
	//по 28 бит
	long c_i;
	long d_i;

	c_i = permutation(key, table_5_C, SIZE_TABLE_5) << 28;
	d_i = permutation(key, table_5_D, SIZE_TABLE_5);

	//56 бит
	long k_i = 0;
	k_i |= d_i;
	k_i |= c_i;


	for (int i = 0; i < 16; ++i) {
		//todo сдвинуть cidi

		for (int j = 0; j < table_6[i]; ++j) {
			k_i = cicle_shift(k_i);
		}
		
		k[i] = permutation(k_i, table_7, SIZE_TABLE_7);
	}
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

	//по 48 бит 
	long k[NUM_KEYS]; 

	long key;

	key = 0xFF00FF00EF00FF00;
	getArrKeys(key, k);

	enciphering(k);


	long end = deciphering(k);
	trunc_cipher_file(end);

	return 0;
} 