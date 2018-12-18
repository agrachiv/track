#include "Diff.cpp"

int main() {
    char tmp[32];
    char variable;
    int trigger = 0;
    printf("Enter equation, diff variable and 1 or 0 for CMD outpoot\n");
    scanf("%s\n", tmp);
    scanf("%c\n", &variable);
    scanf("%d", &trigger);
    differentiate(tmp, variable, trigger);
    return 0;
}



