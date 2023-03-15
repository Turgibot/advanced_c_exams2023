#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define MAX_LEN 80
#define NUM_ITEMS 6
#define MIN_QTT 5


typedef struct date {
	int day;
	int month;
	int year;
}Date;
typedef struct car {
	char* manufacturer;
	int year;
	Date date;
}Car;

Car* createCar(char* data);
Car* findCar(FILE* file, int year);
void subString(int startPosition, int len, char* source, char destination[]);
void main()
{
	FILE* fp1;
	char buffer[MAX_LEN];
	
	fp1 = fopen("file1.txt", "r");
	assert(fp1);
	int count = 0;
	while (!feof(fp1)) {
		fgets(buffer, 21, fp1);
		if(strlen(buffer)==20)
			count++;
	}
	Car* cars = (Car*)malloc(count*sizeof(Car));
	rewind(fp1);
	for (int i = 0; i < count; i++)
	{
		fgets(buffer, 21, fp1);
		Car* tmp = createCar(buffer);
		cars[i] = *tmp;
		
	}
	Car* foundCar;
	if (foundCar = findCar(fp1, 2009)) {
		printf("Yes");
	}
	else{
		printf("No");
	}
	fclose(fp1);
	 
}


void subString(int startPosition, int len, char* source, char destination[])
{
	int c = 0;
	while (c < len) {
		destination[c] = source[startPosition + c];
		c++;
	}
	destination[c] = '\0';
}
Car* createCar(char* data) {
	char buffer[MAX_LEN];
	Date date;
	Car* car = (Car*)malloc(sizeof(Car));

	subString(0, 2, data, buffer);
	date.day = atoi(buffer);
	subString(2, 2, data, buffer);
	date.month = atoi(buffer);
	subString(4, 2, data, buffer);
	date.year = atoi(buffer);
	car->date = date;

	subString(6, 10, data, buffer);
	car->manufacturer = (char*)malloc(strlen(buffer) + 1);
	strcpy(car->manufacturer, buffer);
	
	subString(16, 4, data, buffer);
	car->year = atoi(buffer);
	return car;

}
Car* findCar(FILE* file, int year) {
	Car* car = NULL;
	char buffer[MAX_LEN];
	rewind(file);
	while (!feof(file)) {
		fgets(buffer, 21, file);
		if (strlen(buffer) == 20) {
			car = createCar(buffer);
			if (car->year == year)
				return car;
			free(car->manufacturer);
			free(car);
		}
	}
	return NULL;
}
