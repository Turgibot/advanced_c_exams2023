#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define NUM_QUESTIONS 10
#define NUM_STUDENTS 5
#define POINTS 10
#define CORRECT 'C'
#define INCORRECT 'I'
char* readCorrectAnswers(FILE* in);
char* readStudentAnswers(FILE* in, int nStud);
void writeResult(FILE* out, char result);
void giveGrade(FILE* out);

void main() {
	FILE* fAnswers = fopen("answers.txt", "r");
	FILE* fStudentAnswers = fopen("studAnswers.txt", "r");
	FILE* fStudentResults = fopen("studResults.txt", "w+");
	assert(fAnswers && fStudentAnswers && fStudentResults);

	char* correctAnswers = readCorrectAnswers(fAnswers);
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		char* studentAnswers = readStudentAnswers(fStudentAnswers, i);
		for (int j = 0; j < NUM_QUESTIONS; j++)
		{
			char result = correctAnswers[j] == studentAnswers[j] ? CORRECT : INCORRECT;
			writeResult(fStudentResults, result);
		}
		giveGrade(fStudentResults);
		free(studentAnswers);
	}
	free(correctAnswers);
	fclose(fAnswers);
	fclose(fStudentAnswers);
	fclose(fStudentResults);
	printf("Finished giving grade to students");
}


char* readCorrectAnswers(FILE* in) {
	char* buffer = (char*)malloc(sizeof(char)*(NUM_QUESTIONS + 1));
	assert(buffer);
	char ch = '\n';
	int pos = 0;
	while (ch != EOF) {
		if (ch != '\n') {
			buffer[pos++] = ch;
		}
		ch = fgetc(in);
	}
	buffer[NUM_QUESTIONS] = '\0';
	return buffer;
}

char* readStudentAnswers(FILE* in, int sNum) {
	char* buffer = (char*)malloc(NUM_QUESTIONS + 1);
	fseek(in, sNum*(NUM_QUESTIONS + 2), SEEK_SET);// + \0 + \n
	fgets(buffer, NUM_QUESTIONS + 1, in);
	return buffer;
}

void writeResult(FILE* out, char result) {
	fseek(out, 0, SEEK_END);
	fputc(result, out);
}

void giveGrade(FILE* out) {
	int grade = 0;
	fseek(out, -NUM_QUESTIONS, SEEK_END);
	for (int i = 0; i < NUM_QUESTIONS; i++)
	{
		char result = fgetc(out);
		if (result == CORRECT)
			grade += POINTS;
	}
	fprintf(out, " Grade: %d\n", grade);
}