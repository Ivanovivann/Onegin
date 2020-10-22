#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>


//=============================================================================

/*!
    \brief This function counts strings ahd symbols in input file
    \param [in] input - pointer on input file
    \param [in] size_input - address of the variable that will contain the number of rows after the function is executed
    \return Quantity strings in input file
*/

int params_of_file(FILE* input, int* size_input);

//-----------------------------------------------------------------------------

/*!
    \brief This function sorts array
    \param [in] count_strings - quantity of elements of array strings
    \param [in] strings - array of pointers on strings
    \return 0
*/

int bubble_sort(int count_strings, char** strings);

//-----------------------------------------------------------------------------

/*!
    \brief This function compares 2 strings
    \param [in] strings - array of pointers on strings
    \param [in] j - number of first string
    \return 0 if lines are the same
    \return 1 if the first line early in the alphabet
    \return -1 if the second line early in the alphabet
*/

int compare_strings(char** strings, int j);

//-----------------------------------------------------------------------------

/*!
    \brief This function swap pointers
    \param [in] strings - array of pointers on strings
    \param [in] j - number of first string
    \return 0
*/

int my_swap (char** strings, int j);

//-----------------------------------------------------------------------------

/*!
    \brief This function print text in file
    \param [in] count_strings - quantity of elements  of array
    \param [in] strings - array of pointers on strings
    \return 0
*/

int print_text_in_file (int count_strings, char** strings);

//-----------------------------------------------------------------------------

/*!
    \brief This function print text in file
    \param [in] input - pointer on input file
    \param [in] strings - array of pointers on strings
    \param [in] text - array of symbols from file
    \param [in] count_symbols - quantity of elements of array text
    \return 0
*/

int input_mass (FILE* input, char** strings, char* text, int count_symbols);

//=============================================================================


int main() {
    FILE* unsorted = fopen ("unsorted_onegin.txt", "r");

    int count_symbols = 0;
    int count_strings = params_of_file(unsorted, &count_symbols);

    //printf ("Size of file is %d\n", count_symbols);
    //printf ("Strings in file is %d\n", count_strings);

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
    {
        for (int j = 0; j < count_strings - 1; j++)
        {
            if (compare_strings(strings, j) < 0)
                my_swap (strings, j);
        }
    }

    return 0;
}

//-----------------------------------------------------------------------------

int compare_strings(char** strings, int j) {
    int k1 = 0,
        k2 = 0;

    while (isalpha(*(strings[j] + k1)) == 0)
        k1++;

    while (isalpha(*(strings[j + 1] + k2)) == 0)
        k2++;

    while((*(strings[j] + k1)) == (*(strings[j + 1] + k2)))
    {
        k1++;
        k2++;

        if ((*(strings[j] + k1)) == '\n')
            return 1;

        if ((*(strings[j + 1] + k2)) == '\n')
            return -1;

        while (isalpha(*(strings[j] + k1)) == 0)
            k1++;

        while (isalpha(*(strings[j + 1] + k2)) == 0)
            k2++;
    }

    return *(strings[j + 1] + k2) - *(strings[j] + k1);
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
        int counter = 0;

        while (*(strings[i] + counter) == ' ')
            counter++;

        if (*strings[i + counter] != '\n') {
            for (int k = counter; *((strings[i]) + k) != '\n'; k++)
                putc (*((strings[i]) + k), sorted);
            
            putc ('\n', sorted);
        }
    }

    fclose (sorted);

    return 0;
}

//-----------------------------------------------------------------------------

int input_mass (FILE* input, char** strings, char* text, int count_symbols) {
    rewind (input);

    int j = 1;

    strings[0] = &text[0];

    for (int i = 0; i < count_symbols; i++)
    {
        int symbol = getc(input);
        text[i] = symbol;

        if ((symbol == '\n') && (i != count_symbols - 1)) {
            strings[j] = &text[i + 1];
            j++;
        }

        //printf ("%c", text[i]);
    }

    return 0;
}
