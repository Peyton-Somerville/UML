#include <stdio.h>
#include <stdlib.h>
#include "generic.h"
#include "generic_vector.h"
#include "my_string.h"
#include "associativearray.h"

void clear_keyboard_buffer(void);

int main(int argc, char* argv[])
{
	/*MY_STRING hString_arr[100];
	const char* string = "COPY ME!";
	int i;

	hString_arr[0] = my_string_init_c_string(string);

	for(i = 1; i < 100; i++)
		hString_arr[i] = my_string_init_default();

	for(i = 0; i < 99; i++)
		my_string_assignment((Item*)&hString_arr[i + 1], (Item)hString_arr[i]);

	for (i = 0; i < 100; i++)
	{
		printf("%d: ", i);
		my_string_insertion(hString_arr[i], stdin);
		my_string_destroy((Item*)&hString_arr[i]);
	}*/
	int i, j, x;
	int word_length, num_of_guesses;
	int position = 0;
	int counter = 0;
	int noc;
	char* temp_string = NULL;
	char alphabet[27] = { NULL };
	char letter;
	G_VECTOR hVector_arr[29];
	FILE* fp;
	MY_STRING temp = NULL;
	Item OldKey = NULL;
	Item temp2 = NULL;
	OldKey = my_string_init_default();
	temp = my_string_init_default();

	//tree_init();

	for (i = 0; i < 29; i++)
	{
		fp = fopen("dictionary.txt", "r");
		temp = my_string_init_default();
		hVector_arr[i] = g_vector_init_default(my_string_assignment, my_string_destroy, i + 1);
		while (my_string_extraction(temp, fp))
		{
			if (my_string_get_size(temp) == i + 1)
			{
				counter++;
				temp_string = my_string_c_str(temp);
				//printf("%s\n", temp_string);
				g_vector_push_back(hVector_arr[i], temp_string, position);
				position++;
				temp_string = NULL;
			}
			my_string_destroy((Item*)&temp);
			temp = my_string_init_default();
		}
		my_string_destroy((Item*)&temp);
		fclose(fp);
		position = 0;
		printf("word size: %d\tcounter = %d\n", i + 1, counter);
		counter = 0;
	}

	//print_vector_strings(hVector_arr[2]);

	printf("What length word do you want to play with?>> ");
	noc = scanf("%d", &word_length);
	clear_keyboard_buffer();
	while (noc != 1 || (word_length < 2 || word_length > 29) || (word_length == 23 || word_length == 25 || word_length == 26 || word_length == 27))
	{
		printf("Invalid word length\n");
		printf("What length word do you want to play with?>> ");
		scanf("%d", &word_length);
		clear_keyboard_buffer();
	}
	printf("Total number of words of that length: %d\n", g_vector_get_size(hVector_arr[word_length - 1]));

	printf("How many guesses would you like to have?>> ");
	noc = scanf("%d", &num_of_guesses);
	clear_keyboard_buffer();
	while (num_of_guesses < 1 || num_of_guesses > 100)
	{
		printf("Invalid number of guesses\n");
		printf("How many guesses would you like to have?>> ");
		noc = scanf("%d", &num_of_guesses);
		clear_keyboard_buffer();
	}

	for (i = 0; i < num_of_guesses; i++)
	{
		printf("Enter a letter to guess>> ");
		noc = scanf("%c", &letter);
		clear_keyboard_buffer();
		while (letter < 97 || letter > 122)
		{
			printf("That is not a letter of the alphabet dummy.\n");
			printf("Enter a letter to guess>> ");
			noc = scanf("%c", &letter);
			clear_keyboard_buffer();
		}
		for (j = 0; j < sizeof(alphabet); j++)
		{
			while (letter == alphabet[j])
			{
				printf("You have already entered this letter dummy.\n");
				printf("Enter a letter to guess>> ");
				noc = scanf("%c", &letter);
				clear_keyboard_buffer();
			}
		}
		alphabet[i] = letter;
		for (x = 0; x < sizeof(alphabet); x++)
			printf("%c  ", alphabet[x]);
		printf("\n");
	}

	for (i = 0; i < 29; i++)
	{
		g_vector_destroy(&hVector_arr[i]);
	}

	return 0;
}

void clear_keyboard_buffer(void)
{
	char c;
	scanf("%c", &c);
	while (c != '\n')
	{
		scanf("%c", &c);
	}
}