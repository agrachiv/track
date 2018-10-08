#include "q_eq_solver.c"
#include <string.h>

#define INPUT 1
#define DEFAULT 2


int input (double* a, double* b, double* c) {

    assert (a != NULL && b != NULL && c != NULL);
    char a_buffer[256] = {};
    char b_buffer[256] = {};
    char c_buffer[256] = {};

    scanf ("%s %s %s", a_buffer, b_buffer, c_buffer);
    *a = atof (a_buffer);
    *b = atof (b_buffer);
    *c = atof (c_buffer);

    for (int i = 0; i < 256; i++) {
        if (! ( ( (a_buffer[i] >= 48) && (a_buffer[i] <= 57) || (a_buffer[i] == '\0') || (a_buffer[i] == '.') || (a_buffer[i] == '-')) &&
                ( (b_buffer[i] >= 48) && (b_buffer[i] <= 57) || (b_buffer[i] == '\0') || (b_buffer[i] == '.') || (b_buffer[i] == '-')) &&
                ( (c_buffer[i] >= 48) && (c_buffer[i] <= 57) || (c_buffer[i] == '\0') || (c_buffer[i] == '.') || (c_buffer[i] == '-'))) ||
                ( (*a == 0.000000) && (*b == 0.000000) && (*c == 0.000000))) {
            return -1;
        }
    }

    return 0;
}

int main() {

    double a, b, c, returned_value;
    double root1, root2;
    char buffer[1] = {};
    int switcher = DEFAULT;

    printf ("Welcome to square equations solver\n");

    while (1) {

        switch (switcher) {


            case INPUT: {
                    printf ("enter 3 arguments\n");
                    if (input(&a, &b, &c) == -1)   printf ("Wrong input, try again\n");
                    else {
                        switcher = DEFAULT;
                        returned_value = q_eq_solver (a, b, c, &root1, &root2);
                        if (returned_value == TWO_ROOTS) printf ("Your equation has 2 roots:\n%e\n%e\n", root1, root2);
                        if (returned_value == NO_ROOTS) printf ("Your equation has no roots :(\n", root1, root2);
                        if (returned_value == ONE_ROOT) printf ("Your equation is linear, root is:\n%e\n", root1);
                        if (returned_value == ERROR) printf ("y = %c is the answer\n", c);
                    }
                    break;
                }

            default: {

                    printf ("enter 1 to solve new equation or 0 to exit\n");
                    scanf ("%s", buffer);

                    if (buffer[0] == '1' && strlen (buffer) == 1) switcher = INPUT;
                    else if (buffer[0] == '0' && strlen (buffer) == 1) return 0;
                    else printf ("Wrong input, try again\n");
                    break;
                }
        }
    }
}
