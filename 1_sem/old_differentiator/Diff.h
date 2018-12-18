#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

void differentiate(char* input, double variable, bool CMDoutpoot); //main function (equation, diff varible, 1 for CMp outpoot 0 for Tex); Result.tex used as outpoot anyway

enum flags {
    Number = 0,
    Function1 = 1, //one argument function
    Variable = 2,  //1 symbol only
    Function2 = 3, //double arguments function
    Empty = -1 //warning flag not set!!!
};

enum operators {_sin, _cos, _tg, _ctg, _asin, _acos, _atg, _actg, PLUS, MINUS, MULT, DIV, POW, _exp, _ln}; //all functions allowed

//calulators and tables//////////////////////////////////////////
double funcVal(char* input);
char* valToFunc(double input);
double counter1(double FuncVal, double value);
double counter2(double FuncVal, double value1, double value2);
/////////////////////////////////////////////////////////////////

class node {
    public:

        double flag; //enum flags
        double value; //ACII for vars, table def for functions
        node* root; //root ptr unused
        node* left;
        node* right;

        node(); //empty constructor
        node(char* input); //constructor automatically interprets string into a value, variable or function
        node(double input, double flag); //non-automatic constructor
        void print(); //test function just prints into a console
        void printTex(FILE* ptrResult); //prints tree into Tex file by ptrResult pointer
        bool isleaf(); //checks whenever current node leaf or not
        void addl (char* newdef); //adds node with 'newdef' value
        void addr (char* newdef);
        void remover(); //removes current node and all daughter nodes
        void addRootPointers(); //adds missing root pointers unused
        bool calculate(); //calculates current node
        bool simplify(); //simplifies neutral and identical operations etc x*0 x*1 x+0 0/x x^1 x^0 0^x 1^x x*2->2x
        void Simplify(); //Simplifies the equation as much ass possible using calculate and simplify functions
        void duplicate(node* duplicatedNode); //copies the tree, using pointer to the dedicated memory
        void differentiator(char variable,FILE* ptrResult); //requires ASCE code of the differentiation variable
        char* input(char* buffer); //transforms string into a tree
};





