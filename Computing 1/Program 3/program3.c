/*
	Author: Peyton Somerville
	Course: Computing 1
	Date: 12/12/18

	Description: This program reads names and quiz scores from a file and outputs them into another file in a different format, then copies the output file back to the input file. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void write_scores(void);
void open_files(void);

void find_names(FILE *fp_quiz, FILE *fp_average);
char* read_string(FILE* fp, char* buffer, int size);
void find_scores(FILE *fp_quiz, FILE *fp_average);
int main(void)
{
	write_scores();

	open_files();

	return 0;
}

void write_scores(void)
{
	FILE *fp;

	fp = fopen("quiz.txt", "w");
	if (fp == NULL)
	{
		printf("Failed to open file.\n");
		exit(1);
	}

	fprintf(fp, "%s %s %d %d %d %d %d\n%s %s %d %d %d %d %d %d %d %d %d %d\n%s %s\n%s %s %d %d %d %d %d %d %d",
		"John", "Smith", 98, 99, 76, 76, 8,
		"Bill", "Guy", 42, 53, 64, 75, 85, 45, 86, 99, 88, 99,
		"Harry", "Potter",
		"Mike", "Springfield", 99, 99, 99, 99, 99, 96, 82);

	fclose(fp);
}

void open_files(void)
{
	FILE *fp_quiz, *fp_average;
	char c;

	fp_quiz = fopen("quiz.txt", "r");
	if (fp_quiz == NULL)
	{
		printf("Failed to open file.\n");
		exit(1);
	}

	fp_average = fopen("average.txt", "w");
	if (fp_average == NULL)
	{
		printf("Failed to open file.\n");
		exit(1);
	}


	c = getc(fp_quiz);
	while (c != EOF)
	{
		ungetc(c, fp_quiz);
		find_names(fp_quiz, fp_average);
		find_scores(fp_quiz, fp_average);
		fprintf(fp_average, "\n");
		c = getc(fp_quiz);
	}

	fclose(fp_quiz);
	fclose(fp_average);
	
	fp_quiz = fopen("quiz.txt", "w");
	if (fp_quiz == NULL)
	{
		printf("Failed to open file.\n");
		exit(1);
	}

	fp_average = fopen("average.txt", "r");
	if (fp_average == NULL)
	{
		printf("Failed to open file.\n");
		exit(1);
	}

	do
	{
		c = fgetc(fp_average);
		if (c != EOF)
			fputc(c, fp_quiz);
	}while (c != EOF); 

	fclose(fp_quiz);
	fclose(fp_average); 
}

void find_names(FILE *fp_quiz, FILE *fp_average)
{
	char first_name[50] = "\0", last_name[50] = "\0";
	int i, size_first = sizeof(first_name) / sizeof(char), size_last = size_last = sizeof(last_name) / sizeof(char);

	read_string(fp_quiz, first_name, size_first);

	read_string(fp_quiz, last_name, size_last);

	fprintf(fp_average, "%s", last_name);
	fprintf(fp_average, ", ");
	fprintf(fp_average, "%s ", first_name);
}

char* read_string(FILE* fp, char* buffer, int size)
{
	int i = 0;
	char c;

	c = getc(fp);

	while (c != EOF && isspace(c))
	{
		c = getc(fp);
	}

	if (c == EOF || size <= 1)
	{
		return NULL;
	}

	buffer[i] = (char)c;
	i++;

	c = getc(fp); //try

	//is the file empty, do i want it, do i have room 
	while (c != EOF && !isspace(c) && i < size - 1) //check
	{
		buffer[i] = c; //do
		i++;
		c = getc(fp); //try
	}

	if (c != EOF)
	{
		ungetc(c, fp);
	}
	buffer[i] = '\0';
	return buffer;
}

void find_scores(FILE *fp_quiz, FILE *fp_average)
{
	int sum = 0;
	double average;
	char number[50] = "\0", c;
	int size = sizeof(number);

	c = getc(fp_quiz);
	while (c != EOF && isspace(c))
	{
		c = getc(fp_quiz);
	}
	if (isdigit(c) != 0)
	{
		ungetc(c, fp_quiz);
		read_string(fp_quiz, number, size);
		c = getc(fp_quiz);
		while (c != EOF && isspace(c))
		{
			c = getc(fp_quiz);
		}
		fprintf(fp_average, "%s ", number);
		sum = sum + atoi(number);
	}
	while (isdigit(c) != 0)
	{
		if (isdigit(c) != 0)
		{
			ungetc(c, fp_quiz);
			read_string(fp_quiz, number, size);
			fprintf(fp_average, "%s ", number);
			c = getc(fp_quiz);
			while (c != EOF && isspace(c))
			{
				c = getc(fp_quiz);
			}
		}
		else
			ungetc(c, fp_quiz);
		sum = sum + atoi(number);
	}
	ungetc(c, fp_quiz);

	average = sum / 10.0;
	fprintf(fp_average, "  %.1lf", average);
}

