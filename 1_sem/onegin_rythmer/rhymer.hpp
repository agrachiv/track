#ifndef RHYMER_H
#define RHYMER_H

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#include <assert.h>

#define PATH "eonegin.txt"


class rhymer {
    public:
        rhymer(); //c-tor
        void print_strophe(); //prints randomly generated strophe in console
        ~rhymer(); //d-tor
    private:
        char* buffer;
        int buffer_size;
        char** line_ptrs;
        int number_of_lines; //number of lines in Evgeniy Onegin
        int number_of_strophes;

        int input (const char* route_to_file); //fills buffer from the file
        int buffer_clean(); //fills line_ptrs and cleans all trash lines
        int sorter(); //sorts line pointers by the end of the strings separately (by the position in strophe)
        int counter_of_lines(); //counts lines in buffer
        int find_rhyme (const int line_number, const int line_in_strophe); //returns number of rhymed line by position in strophe, returns -1 if there are no rhymes
        void find_rhymed_pair (int* line1_number_ptr, int* line2_number_ptr, int line_in_strophe); //finds rhymed pair using special pattern
        int rhyme_pattern (const int line_in_strophe); // rhythm pattern ABABAABBABBABB
};

int comparator (const void* str1_ptr, const void* str2_ptr); //qsort comparator
bool same_end (const char* str1, const char* str2); //returns true if two strings ends with same word

#endif // RHYMER_H
