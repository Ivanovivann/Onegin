#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>


//=============================================================================

typedef struct  {
    char* pointer;
    int lengh;
}info_string;

//=============================================================================

int size_file ();

char* filling_buffer (int size_of_file);

int counting_strings (char* buffer, int size_of_file);

info_string* filling_array_of_pointers (char* buffer, int count_strings, int size_of_file);

int compare_strings(const void * x1, const void * x2);

int skip_not_alpha (char* pointer1, int* k1, char* pointer2, int* k2);

int print_text (info_string* mass_string, int count_strings, FILE* sorted);

int reverse_compare_strings(const void * x1, const void * x2);

int reverse_skip_not_alpha (char* pointer1, int* k1, char* pointer2, int* k2, int lengh1, int lengh2);

int sort_and_print (info_string* mass_string, int count_strings, FILE* sorted);

int file_output (info_string* mass_string, int count_strings);

void free_arrays (info_string* mass_string, char* buffer);

//=============================================================================

int main() {
    int size_of_file = size_file ();

    char* buffer = filling_buffer (size_of_file);

    int count_strings = counting_strings (buffer, size_of_file);

    info_string* mass_string = filling_array_of_pointers (buffer, count_strings, size_of_file);

    file_output (mass_string, count_strings);

    free_arrays (mass_string, buffer);

    return 0;
}

//-----------------------------------------------------------------------------

int size_file () {
    struct stat info_file;
    stat ("unsorted_onegin.txt", &info_file);

    return info_file.st_size;
}

//-----------------------------------------------------------------------------

char* filling_buffer (int size_of_file) {
    FILE* unsorted = fopen ("unsorted_onegin.txt", "rb");
    assert (unsorted);

    char* buffer = (char*) calloc (size_of_file, sizeof (char));
    assert (buffer);

    int fread_er = fread (buffer, sizeof (char), size_of_file, unsorted);
    fclose (unsorted);

    assert (fread_er == size_of_file);

    return buffer;
}

//-----------------------------------------------------------------------------

int counting_strings (char* buffer, int size_of_file) {
    int count_strings = 0;

    for (int i = 0; i < size_of_file; i++)
    {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';

            count_strings++;
        }
    }

    return count_strings;
}

//-----------------------------------------------------------------------------

int file_output (info_string* mass_string, int count_strings) {
    FILE* sorted = fopen ("sorted_onegin.txt", "w");

    sort_and_print (mass_string, count_strings, sorted);

    fprintf(sorted, "\n\n");

    print_text (mass_string, count_strings, sorted);

    fclose(sorted);

    return 0;
}

//-----------------------------------------------------------------------------

info_string* filling_array_of_pointers (char* buffer, int count_strings, int size_of_file) {
    info_string* mass_string = (info_string*) calloc (count_strings, sizeof(info_string));

    mass_string[0].pointer = &buffer[0];

    int counter = 1;

    for (int i = 0; i < size_of_file; i++)
    {
        if (buffer[i] == '\0') {
            int offset = 0;
            for (offset; buffer[i + offset + 1] == ' '; offset++);

            if (i < size_of_file - 2)
                mass_string[counter].pointer = &buffer[i + offset + 1];

            mass_string[counter - 1].lengh = &buffer[i] - mass_string[counter - 1].pointer;

            counter++;

        }
    }

    return mass_string;
}

//-----------------------------------------------------------------------------

int compare_strings(const void * x1, const void * x2) {
    char* string1 = ((info_string*) x1)->pointer;
    char* string2 = ((info_string*) x2)->pointer;

    int k1 = 0,
        k2 = 0;

    skip_not_alpha (string1, &k1, string2, &k2);

    while (tolower (*(string1 + k1)) == tolower (*(string2 + k2)))
    {
        k1++;
        k2++;

        skip_not_alpha (string1, &k1, string2, &k2);
    }

    return tolower (*(string1 + k1)) - tolower (*(string2 + k2));
}

//-----------------------------------------------------------------------------

int skip_not_alpha (char* pointer1, int* k1, char* pointer2, int* k2) {
    while (isalpha(*(pointer1 + *k1)) == 0 && *(pointer1 + *k1) != '\0')
        ++*k1;

    while (isalpha(*(pointer2 + *k2)) == 0 && *(pointer2 + *k2) != '\0')
        ++*k2;

    return 0;
}

//-----------------------------------------------------------------------------

int print_text (info_string* mass_string, int count_strings, FILE* sorted) {
    //FILE* sorted = fopen ("sorted_onegin.txt", "w");

    for (int i = 0; i < count_strings; i++)
        if (mass_string[i].lengh > 1)
            fprintf (sorted, "%s", mass_string[i].pointer);

    //fclose(sorted);

    return 0;
}

//-----------------------------------------------------------------------------

int sort_and_print (info_string* mass_string, int count_strings, FILE* sorted) {

    qsort (mass_string, count_strings, sizeof (*mass_string), compare_strings);
    print_text(mass_string, count_strings, sorted);

    fprintf(sorted, "\n\n");

    qsort (mass_string, count_strings, sizeof (*mass_string), reverse_compare_strings);
    print_text(mass_string, count_strings, sorted);

    return 0;
}

//-----------------------------------------------------------------------------

int reverse_compare_strings(const void * x1, const void * x2) {
    char* string1 = ((info_string*) x1)->pointer;
    char* string2 = ((info_string*) x2)->pointer;

    int lengh1 = ((info_string*) x1)->lengh;
    int lengh2 = ((info_string*) x2)->lengh;

    int k1 = 0,
        k2 = 0;

    reverse_skip_not_alpha (string1, &k1, string2, &k2, lengh1, lengh2);

    while (tolower (*(string1 + lengh1 + k1)) == tolower (*(string2 + lengh2 + k2)))
    {
        k1--;
        k2--;

        reverse_skip_not_alpha (string1, &k1, string2, &k2, lengh1, lengh2);
    }

    return tolower (*(string1 + lengh1 + k1)) - tolower (*(string2 + lengh2 + k2));
}

//-----------------------------------------------------------------------------

int reverse_skip_not_alpha (char* pointer1, int* k1, char* pointer2, int* k2, int lengh1, int lengh2) {
    while (isalpha(*(pointer1 + lengh1 + *k1)) == 0 && *(pointer1 + lengh1 + *k1) != '\0')
        --*k1;

    while (isalpha(*(pointer2 + lengh2 + *k2)) == 0 && *(pointer2 + lengh2 + *k2) != '\0')
        --*k2;

    return 0;
}

//-----------------------------------------------------------------------------

void free_arrays (info_string* mass_string, char* buffer) {
    free(mass_string);
    free(buffer);

    return;
}
