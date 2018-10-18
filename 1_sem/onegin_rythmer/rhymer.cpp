#include "rhymer.hpp"

#define WRONG_INPUT -1
#define LINES_IN_STROPHE 14
#define INDENT_SIZE 8
#define MATCHED_SYMBOLS_TO_rhyhm 3


rhymer::rhymer() {
    buffer = NULL;
    line_ptrs = NULL;
    buffer_size = 0;
}

int rhymer::counter_of_lines() {
    int counter = 0;

    for (int i = 0; i < buffer_size; i++) {
        if (buffer[i] == '\n')
            counter++;
    }

    return counter;
}


int rhymer::input (const char* route_to_file) {
    FILE* file = fopen (route_to_file, "rb");

    if (file == NULL)
        return WRONG_INPUT;

    fseek (file, 0, SEEK_END);
    buffer_size = ftell (file);
    fseek (file, 0, SEEK_SET);
    buffer = new char[buffer_size];
    fread (buffer, 1, buffer_size, file);
    return EXIT_SUCCESS;

}

int rhymer::buffer_clean () {
    number_of_lines = counter_of_lines();
    char* trash_line_ptrs[number_of_lines];
    trash_line_ptrs[0] = buffer;
    int lines_read = 1;
    int bad_lines = 0;

    for (char* endline_ptr = strchr (buffer, '\n'); lines_read < number_of_lines; endline_ptr = strchr (&endline_ptr[1], '\n')) {
        *endline_ptr = '\0';

        if (* (endline_ptr - 2) > 'ÿ' || * (endline_ptr - 2) < 'À')
            * (endline_ptr - 2) = '\0';

        trash_line_ptrs[lines_read] = &endline_ptr[1];
        lines_read++;
    }

    for (int i = 0; i < number_of_lines; i++) {
        if ( (*trash_line_ptrs[i] != ' ') || (strlen (trash_line_ptrs[i]) < INDENT_SIZE))
            bad_lines++;
    }

    assert ( (number_of_lines - bad_lines) % LINES_IN_STROPHE == 0); //trash left in buffer
    number_of_strophes = (number_of_lines - bad_lines) / LINES_IN_STROPHE;
    line_ptrs = new char*[number_of_lines - bad_lines];

    lines_read = 0;

    for (int i = 0; i < number_of_lines; i++) {
        if ( (*trash_line_ptrs[i] == ' ') && (strlen (trash_line_ptrs[i]) >= INDENT_SIZE)) {
            line_ptrs[ (lines_read % LINES_IN_STROPHE) *number_of_strophes + lines_read / LINES_IN_STROPHE] = trash_line_ptrs[i];
            lines_read++;
        }
    }

    number_of_lines -= bad_lines;
}

int rhymer::find_rhyme (const int line_number, const int line_in_strophe) {
    assert (line_in_strophe >= 0 && line_in_strophe < LINES_IN_STROPHE);
    assert (line_number < number_of_lines);

    for (int i = line_in_strophe * number_of_strophes; i < number_of_strophes * (line_in_strophe + 1); i++) {
        if (comparator ( (void*) &line_ptrs[line_number], (void*) &line_ptrs[i]) == 0) {
            int possible_rhyhms;

            for (possible_rhyhms = 1; comparator ( (void*) &line_ptrs[line_number], (void*) &line_ptrs[i + possible_rhyhms]) == 0; possible_rhyhms++);

            if (possible_rhyhms == 1) {
                return -1;
            } else {
                int returned_line_number = line_number - i;

                while (returned_line_number + i == line_number) {
                    returned_line_number = (rand() % possible_rhyhms);
                }

                return returned_line_number + i;
            }
        }
    }

    return -1;
}

void rhymer::find_rhymed_pair (int* line1_number_ptr, int* line2_number_ptr, int line_in_strophe) {
    assert (line_in_strophe >= 0 && line_in_strophe < LINES_IN_STROPHE);
    assert (line1_number_ptr != NULL && line2_number_ptr != NULL);

    do {
        *line1_number_ptr = rand() % number_of_strophes + line_in_strophe * number_of_strophes;
        *line2_number_ptr = find_rhyme (*line1_number_ptr, rhyme_pattern (line_in_strophe));
    } while (*line2_number_ptr == -1 || same_end (line_ptrs[*line1_number_ptr], line_ptrs[*line2_number_ptr]) == true);
}



int rhymer::sorter() {
    if (line_ptrs == NULL)
        return EXIT_FAILURE;

    for (int i = 0; i < LINES_IN_STROPHE; i++)
        qsort (line_ptrs + i * number_of_lines / LINES_IN_STROPHE, number_of_lines / LINES_IN_STROPHE, sizeof (char*), comparator);
}

int rhymer::rhyme_pattern (const int line_in_strophe) {
    switch (line_in_strophe) {
        case 0:
            return 2;

        case 1:
            return 3;

        case 4:
            return 5;

        case 6:
            return 7;

        case 8:
            return 11;

        case 9:
            return 10;

        case 12:
            return 13;

        default:
            return -1;
    }
}

void rhymer::print_strophe() {
    input (PATH);
    buffer_clean();
    sorter();
    srand (time (NULL));
    int line_number[14] = {};

    for (int i = 0; i < 14; i++)
        if (rhyme_pattern (i) != -1)
            find_rhymed_pair (&line_number[i], &line_number[rhyme_pattern (i)], i);

    for (int i = 0; i < 14; i++)
        printf ("%s\n", line_ptrs[line_number[i]]);
}

rhymer::~rhymer() {
    delete buffer;
    delete line_ptrs;
}

int comparator (const void* str1_ptr, const void* str2_ptr) {
    char* str1 = * (char**) str1_ptr;
    char* str2 = * (char**) str2_ptr;

    for (int i = 1; i <= (MATCHED_SYMBOLS_TO_rhyhm + 1); i++)
        if (str1[strlen (str1) - i] != str2[strlen (str2) - i])
            return str1[strlen (str1) - i] - str2[strlen (str2) - i];

    return 0;
}

bool same_end (const char* str1, const char* str2) {
    assert (str1 != NULL && str2 != NULL);

    for (int i = 1; str1[strlen (str1) - i] != ' '; i++)
        if (str1[strlen (str1) - i] != str2[strlen (str2) - i])
            return false;

    return true;
}


