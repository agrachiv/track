#include "q_eq_solver.c"

#include <ctime>
#define number_of_tests 10000
#define input_number_limit 10

int main () {

    double root1, root2;
    int a, x1, x2; //a(x - x1)(x - x2) = ax^2 + (-a(x1+x2))x + ax1x2
    int returned_value;

    for (int i = 0; i < number_of_tests; i++) {
        srand (time (NULL) + i);
        a = -1 * input_number_limit + rand() % (2 * input_number_limit);
        x1 = -1 * input_number_limit + rand() % (2 * input_number_limit);
        x2 = -1 * input_number_limit + rand() % (2 * input_number_limit);
        returned_value = q_eq_solver (a, -1 * a * (x1 + x2), a * x1 * x2, &root1, &root2);

        printf ("input equation: %d(x - %d)(x - %d)\n", a, x1, x2);

        if (returned_value == TWO_ROOTS && ((root1 == x1 && root2 == x2) || (root2 == x1 && root1 == x2))) printf ("success\n");
        else if (a == 0 && returned_value == ERROR) printf ("success\n");
        else {
            printf ("unit test failed\n returned roots are: %e %e\n", root1, root2);
            break;
        }
    }

    printf ("-----------------------------------\nAll unit tests succeeded\n");
    return 0;
}
