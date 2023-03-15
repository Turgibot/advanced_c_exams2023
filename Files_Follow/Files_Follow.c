#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MAX_LEN 80
#define NUM_ITEMS 6
#define MIN_QTT 5

typedef struct item {
	char name[MAX_LEN];
	int quantity;
}Item;

void main()
{
	FILE* fp1, * fp2, * fp3;
	Item items[NUM_ITEMS];
	int i, qtt;
	fp1 = fopen("file1.txt", "r");
	fp2 = fopen("file2.txt", "r");
	fp3 = fopen("file3.txt", "w");
	assert(fp1 && fp2 && fp3);
	for (int i = 0; i < NUM_ITEMS; i++)
	{
		fscanf(fp1, "%s %d\n", items[i].name, &(items[i].quantity));
	}
	while (!feof(fp2)) {
		fscanf(fp2, "%d %d\n", &i, &qtt);
		items[i-1].quantity -= qtt;
	}
	for (int i = 0; i < NUM_ITEMS; i++)
	{
		char* msg = "";
		if (items[i].quantity <= MIN_QTT)
			msg = "<IN SHORTAGE>";
		fprintf(fp3, "%s %s %d\n",msg, items[i].name, items[i].quantity);
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
}