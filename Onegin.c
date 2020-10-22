#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


//=============================================================================

int params_of_file(FILE* input, int* size_input);

int bubble_sort(int count_strings, char** strings);

int compare_strings(char** strings, int j);

int my_swap (char** strings, int j);

int print_text_in_file (int count_strings, char** strings);

int input_mass (FILE* unsorted, char** strings, char* text, int count_symbols);

//=============================================================================


int main() {
    FILE* unsorted = fopen ("unsorted_onegin.txt", "r");

    int count_symbols = 0;
    int count_strings = params_of_file(unsorted, &count_symbols);

    printf ("Size of file is %d\n", count_symbols);
    printf ("Strings in file is %d\n", count_strings);

    rewind (unsorted);

    char*  text    = (char*) calloc (count_symbols + 1, sizeof(char));
    char** strings = (char**) calloc (count_strings, sizeof(char*));

    input_mass (unsorted, strings, text, count_symbols);

    fclose (unsorted);

    bubble_sort(count_strings, strings);

    print_text_in_file (count_strings, strings);

    free(strings);
    free(text);

    return 0;
}

//-----------------------------------------------------------------------------

int params_of_file(FILE* input, int* size_input) {
    int size_file          = 0,
        size_strings_input = 0;
    int c                  = 0;

    while ((c = getc(input)) != EOF)
    {
        size_file++;

        if (c == '\n')
            size_strings_input++;
    }

    *size_input = size_file;

    return size_strings_input;
}

//-----------------------------------------------------------------------------

int bubble_sort(int count_strings, char** strings) {
    for (int i = 0; i < count_strings; i++)
        for (int j = 0; j < count_strings - 1; j++)
        {
            int condition = compare_strings(strings, j);

            if (condition == -1)
                my_swap (strings, j);
        }

    return 0;
}

//-----------------------------------------------------------------------------

int compare_strings(char** strings, int j) {
    int k = 0;

    while ((*(strings[j] + k)) == (*(strings[j + 1] + k)))
        k++;

    if ((*(strings[j] + k)) > (*(strings[j + 1] + k)))
        return -1;

    if ((*(strings[j] + k)) < (*(strings[j + 1] + k)))
        return 1;

    return 0;
}

//-----------------------------------------------------------------------------

int my_swap (char** strings, int j) {
    char* str = strings[j];
    strings[j] = strings[j + 1];
    strings[j + 1] = str;

    return 0;
}

//-----------------------------------------------------------------------------

int print_text_in_file (int count_strings, char ** strings) {
    FILE* sorted = fopen("sorted_onegin.txt", "w");

    for (int i = 0; i < count_strings; i++)
    {
        if (*strings[i] != '\n') {
            for (int k = 0; *((strings[i]) + k) != '\n'; k++)
                putc (*((strings[i]) + k), sorted);

            fprintf (sorted, "\n");
        }
    }

    fclose (sorted);

    return 0;
}

//-----------------------------------------------------------------------------

int input_mass (FILE* unsorted, char** strings, char* text, int count_symbols) {
    int j = 1;

    strings[0] = &text[0];

    for (int i = 0; i < count_symbols; i++)
    {
        int symbol = getc(unsorted);
        text[i] = symbol;

        if ((symbol == '\n') && (i != count_symbols - 1)) {
            strings[j] = &text[i + 1];
            j++;
        }

        //printf ("%c", text[i]);
    }

    return 0;
}
