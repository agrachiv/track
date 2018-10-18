#include "rhymer.cpp"

int main() {
    setlocale (LC_ALL, "Rus");
    rhymer onegin;
    onegin.print_strophe();
    onegin.~rhymer();
    return 0;
}
