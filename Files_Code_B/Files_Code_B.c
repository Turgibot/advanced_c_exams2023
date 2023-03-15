#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define SIZE 80
#define NUM_USERS 5

typedef struct userColor {
	char name[SIZE];
	int colorNum;
}UserColor;

char** getColors(char* colorFilePath, int* size);
void freeMem(char** arr, int size);
void showColors(char** arr, int size);
void saveUserColorsToFile(char** colors, UserColor userColors[], int numUsers, char* filePath);
void main() {
	int size;
	UserColor userColors[NUM_USERS];
	char** colors = getColors("colors.txt", &size);
	showColors(colors, size);
	for (size_t i = 0; i < NUM_USERS; i++)
	{
		printf("\nwhat is your name?");
		scanf("%s", &(userColors[i].name));
		printf("\nwhat is your color number?");
		scanf("%d", &(userColors[i].colorNum));
	}
	saveUserColorsToFile(colors, userColors, NUM_USERS, "userColors.txt");
	freeMem(colors, size);
}

void showColors(char** arr, int size) {
	for (size_t i = 0; i < size; i++)
	{
		printf("%d. %s",i, arr[i]);
	}
}


void saveUserColorsToFile(char** colors, UserColor userColors[], int numUsers, char* filePath) {
	FILE* file = fopen(filePath, "w");
	assert(file);
	for (size_t i = 0; i < numUsers; i++)
	{
		fprintf(file, "%s : %s", userColors[i].name, colors[userColors[i].colorNum]);
	}
	fclose(file);
}

void freeMem(char** arr, int size) {
	for (size_t i = 0; i < size; i++)
	{
		free(arr[i]);
	}
	free(arr);
}

char** getColors(char* colorFilePath, int* size) {
	FILE* colorsFile = fopen(colorFilePath, "r");
	assert(colorsFile);
	char buffer[SIZE];
	int count = 0;
	while (!feof(colorsFile))
		if (fgets(buffer, SIZE, colorsFile) != NULL)
			count++;
	rewind(colorsFile);
	*size = count;

	char** colors = (char**)malloc(count * sizeof(char*));
	count = 0;
	while (!feof(colorsFile))
		if (fgets(buffer, SIZE, colorsFile) != NULL) {
			colors[count] = malloc(strlen(buffer) + 1);
			strcpy(colors[count], buffer);
			count++;
		}
	fclose(colorsFile);
	return colors;
}
