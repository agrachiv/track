
#include "Diff.h"



void differentiate (char* input, char variable, bool CMDoutpoot) {

    node tree;
    tree.input (input);
    FILE* ptrResult = fopen ("Result.tex", "w");
    fprintf (ptrResult, "\\documentclass[]{article}\n\\usepackage[utf8]{inputenc}\n\\usepackage[T2A]{fontenc}\n\\usepackage[english, russian]{babel}\n\\usepackage{datetime}\n\\usepackage{amsmath}\n%%opening\n\\title{Differentiator}\n\\author{Andrey Agrachev}\n\\begin{document}\n\\maketitle\n\\section{Input}\n\\begin{gather*}\nf(%c) = ", (char) variable);
    tree.printTex (ptrResult);
    fprintf (ptrResult, "\n\\end{gather*}\n\\section{Differentiation}\n\\begin{gather*}\n");
    fprintf(ptrResult,"\\frac{df}{d%c}=(", variable);
    tree.printTex(ptrResult);
    fprintf(ptrResult,")'\\\\\n");
    tree.differentiator (variable, ptrResult);
    fprintf(ptrResult,"\\frac{df}{d%c}=", variable);
    tree.printTex(ptrResult);
    fprintf(ptrResult,"\\\\\n\\end{gather*}\n\\section{Simplifying}\n\\begin{gather*}\n");
    tree.Simplify();
    fprintf(ptrResult,"\\frac{df}{d%c}=", variable);
    tree.printTex(ptrResult);
    fprintf(ptrResult,"\n\\end{gather*}\n\\end{document}");
    fclose (ptrResult);
    if (CMDoutpoot == true) tree.print();
}

double funcVal (char* input) {
    if (strcmp (input, "sin") == 0)  return _sin;

    if (strcmp (input, "cos") == 0)  return _cos;

    if (strcmp (input, "tg") == 0)   return _tg;

    if (strcmp (input, "ctg") == 0)  return _ctg;

    if (strcmp (input, "asin") == 0) return _asin;

    if (strcmp (input, "acos") == 0) return _acos;

    if (strcmp (input, "atg") == 0)  return _atg;

    if (strcmp (input, "actg") == 0) return _actg;

    if (strcmp (input, "+") == 0)    return PLUS;

    if (strcmp (input, "-") == 0)    return MINUS;

    if (strcmp (input, "*") == 0)    return MULT;

    if (strcmp (input, "/") == 0)    return DIV;

    if (strcmp (input, "^") == 0)    return POW;

    if (strcmp (input, "exp") == 0)  return _exp;

    if (strcmp (input, "ln") == 0)   return _ln;

    assert (false);
}

char* valToFunc (double input) {

    if (input == _sin) return "sin";

    if (input == _cos) return "cos";

    if (input == _tg) return "tg";

    if (input == _ctg) return "ctg";

    if (input == _asin) return "asin";

    if (input == _acos) return "acos";

    if (input == _atg) return "atg";

    if (input == _actg) return "actg";

    if (input == PLUS) return "+";

    if (input == MINUS) return "-";

    if (input ==  MULT) return "*";

    if (input == DIV) return "/";

    if (input == POW) return "^";

    if (input == _exp) return "exp";

    if (input == _ln) return "ln";

    assert (false);
}

double counter1 (double FuncVal, double value) {

    if (FuncVal == _sin) return sin (value);

    if (FuncVal == _cos) return cos (value);

    if (FuncVal == _tg) return tan (value);

    if (FuncVal == _ctg) return 1 / (tan (value));

    if (FuncVal == _asin) return asin (value);

    if (FuncVal == _acos) return acos (value);

    if (FuncVal == _atg) return atan (value);

    if (FuncVal == _actg) return atan (1 / value);

    if (FuncVal == _exp) return exp (value);

    if (FuncVal == _ln) return log (value);

    assert (false); //unknown function
}

double counter2 (double FuncVal, double value1, double value2) {

    if (FuncVal == PLUS) return value1 + value2;

    if (FuncVal == MINUS) return value1 - value2;

    if (FuncVal ==  MULT) return (value1) * (value2);

    if (FuncVal == DIV) return value1 / value2;

    if (FuncVal == POW) return pow (value1, value2);

    assert (false); //unknown function
}

bool nodecmp (node* node1, node* node2) {
    if (node1->flag == node2-> flag && node1->value == node2->value) {
        if (node1->left == NULL && node2->left == NULL && node1->right == NULL && node2->right == NULL) {
            return true;
        } else {
            int l = 0;
            int r = 0;

            if (node1->left != 0) l = nodecmp (node1->left, node2->left);

            if (node1->right != 0) r = nodecmp (node1->right, node2->right);

            if (l + r == 0) {
                return true;
            } else {
                return false;
            }
        }
    } else return false;
}


node::node (char* input) {

    root = NULL;
    left = NULL;
    right = NULL;

    if (
        (strcmp (input, "sin") == 0)  ||
        (strcmp (input, "cos") == 0)  ||
        (strcmp (input, "tg") == 0)   ||
        (strcmp (input, "ctg") == 0)  ||
        (strcmp (input, "asin") == 0) ||
        (strcmp (input, "acos") == 0) ||
        (strcmp (input, "atg") == 0)  ||
        (strcmp (input, "actg") == 0) ||
        (strcmp (input, "exp") == 0)  ||
        (strcmp (input, "ln") == 0)) {



        flag = Function1;
        value = funcVal (input);

    } else if (

        (strcmp (input, "+") == 0)    ||
        (strcmp (input, "-") == 0)    ||
        (strcmp (input, "*") == 0)    ||
        (strcmp (input, "/") == 0)    ||
        (strcmp (input, "^") == 0)) {

        flag = Function2;
        value = funcVal (input);
    }


    else {

        for (int i = 1; i < strlen (input); i++) {
            assert ( (input[i] >= 48 && input[i] <= 57) || input[i] == '.'); //input is not a variable, number or function
        }

        if ( (*input < 48 || *input > 57) && (*input != 45)) {

            for (int i = 1; i < strlen (input); i++) {
                assert (strlen (input) == 1); //input is not a variable, number or function
            }

            flag = Variable;
            value = *input;
        } else {

            flag = Number;
            value = atof (input);

        }

    }
}

node::node (double input, double presetedFlag) {

    assert ( (presetedFlag == 0) || (presetedFlag == 1) || (presetedFlag == 2) || (presetedFlag == 3)); //unknown flag

    flag = presetedFlag;
    value = input;
    root = NULL;
    left = NULL;
    right = NULL;
}

node::node() {

    flag = Empty;
    value = 0;
    root = NULL;
    left = NULL;
    right = NULL;
}


void node::print() {

    if (flag == Number) printf ("%g", value);

    if (flag == Function1) {

        printf ("%s(", valToFunc (value));
        left->print();
        printf (")");
    }

    if (flag == Function2 && (value == PLUS || value == MINUS)) {
        printf ("(");
        left->print();
        printf ("%s", valToFunc (value));
        right->print();
        printf (")");
    }

    if (flag == Function2 && value ==  MULT) {
        left->print();
        printf ("*");
        right->print();
    }

    if (flag == Function2 && (value == DIV || value == POW)) {
        printf ("(");
        left->print();
        printf (")%s(", valToFunc (value));
        right->print();
        printf (")");
    }

    if (flag == Variable) printf ("%c", (int) value);


}

void node::printTex (FILE* ptrResult) {


    if (flag == Number) fprintf (ptrResult, "%g", value);

    if (flag == Function1) {

        fprintf (ptrResult, "%s(", valToFunc (value));
        left->printTex (ptrResult);
        fprintf (ptrResult, ")");
    }

    if (flag == Function2 && (value == PLUS || value == MINUS)) {
        fprintf (ptrResult, "(");
        left->printTex (ptrResult);
        fprintf (ptrResult, "%s", valToFunc (value));
        right->printTex (ptrResult);
        fprintf (ptrResult, ")");
    }

    if (flag == Function2 && value ==  MULT) {
        left->printTex (ptrResult);
        if (left->flag == Number && right->flag == Number) fprintf (ptrResult, "*");
        right->printTex (ptrResult);
    }

    if (flag == Function2 && value == POW) {
        fprintf (ptrResult, "{");
        left->printTex (ptrResult);
        fprintf (ptrResult, "}%s{", valToFunc (value));
        right->printTex (ptrResult);
        fprintf (ptrResult, "}");
    }

    if (flag == Function2 && value == DIV) {
        fprintf (ptrResult, "\\frac{");
        left->printTex (ptrResult);
        fprintf (ptrResult, "}{");
        right->printTex (ptrResult);
        fprintf (ptrResult, "}");
    }

    if (flag == Variable) fprintf (ptrResult, "%c", (int) value);
}

bool node::isleaf () {
    if (left == NULL && right == NULL) {
        return 1;
    } else {
        return 0;
    }
}

void node::addl (char* newdef) {
    assert (left == NULL);
    left = new node (newdef);
    left->root = this;
}

void node::addr (char* newdef) {
    assert (right == NULL);
    right = new node (newdef);
    right->root = this;
}

void node::remover() {

    if (left != NULL) {
        left->remover();
    }

    if (right != NULL) {
        left->remover();
    }

    delete left;
    delete right;

    left = NULL;
    right = NULL;
}

void node::addRootPointers() {
    if (left != NULL) {
        left->root = this;
        left->addRootPointers();
    }

    if (right != NULL) {
        right->root = this;
        right->addRootPointers();
    }


}

bool node::calculate() {
    bool _return = false;

    if (flag == Number) {
        assert (left == NULL); //corrupted tree
        assert (right == NULL);

    } else if (flag == Function1) {
        assert (right == NULL); //corrupted tree
        assert (left != NULL);

        if (left->flag != Number && left->flag != Variable) {
            left->calculate();
        }

        if (left->flag == Number) {
            flag = Number;
            value = counter1 (value, left->value);
            delete left;
            left = NULL;
            right = NULL;
            _return = true;
        }

    } else if (flag == Function2) {
        assert (left != NULL); //corrupted tree
        assert (right != NULL);

        if (left->flag != Number && left->flag != Variable) {
            _return = _return + left->calculate();
        }

        if (right->flag != Number && right->flag != Variable) {
            _return = _return + right->calculate();
        }

        if ( (left->flag == Number) && (right->flag == Number)) {

            flag = Number;
            value = counter2 (value, left->value, right->value);
            delete left;
            left = NULL;
            delete right;
            right = NULL;
            _return = true;

        }

    }

    return _return;
}

bool node::simplify() {

    addRootPointers();
    bool _return = false;

    if (flag == Function2 && left->flag == Number && ( (value == PLUS && left->value == 0) || (value ==  MULT && left->value == 1))) { //0+x = x || 1*x=x
        delete left;
        value = right->value;
        flag = right->flag;
        node* tmp = right;
        left = right->left;
        right = right->right;
        delete tmp;
        _return = true;
    }

    if (flag == Function2 && right->flag == Number && ( (value == PLUS && right->value == 0) || (value ==  MULT && right->value == 1))) { //x+0 = x || x*1=x

        delete right;
        value = left->value;
        flag = left->flag;
        node* tmp = left;

        right = left->right;

        left = left->left;

        delete tmp;
        _return = true;
    }


    if (flag == Function2 && (value == MINUS)) {
        if (right->flag == Number && right->value == 0) { //x-0 = x
            delete right;
            value = left->value;
            flag = left->flag;
            node* tmp = left;
            right = left->right;

            left = left->left;

            delete tmp;
            _return = true;
            simplify();
        }
    }

    if (flag == Function2 && (value == DIV || value ==  MULT)) {
        if (left->flag == Number && left->value == 0) { // 0/x = 0 0*x=0
            right->remover();
            left->remover();
            right = NULL;
            left = NULL;
            value = 0;
            flag = Number;
            _return = true;
        }
    }

    if (flag == Function2 && value ==  MULT) {
        if (right->flag == Number && right->value == 0) { // x*0 = 0;
            right->remover();
            left->remover();
            right = NULL;
            left = NULL;
            value = 0;
            _return = true;
            flag = Number;
        }
    }

    if (flag == Function2 && value == POW) {
        if (right->flag == Number && right->value == 0) {
            right->remover();
            left->remover();
            right = NULL;
            left = NULL;
            value = 1;
            flag = Number;
            _return = true;
        }
    }

    if (flag == Function2 && value == POW) {

        if (right->flag == Number && right->value == 1) {
            delete right;
            node* tmp = left;
            value = left->value;
            flag = left->flag;
            right = left->right;
            left = left->left;
            delete left;
            _return = true;
        }
    }

    if (flag == Function2 && value == POW) {
        if (left->flag == Number && left->value == 1) {
            right->remover();
            left->remover();
            right = NULL;
            left = NULL;
            value = 1;
            flag = Number;
            _return = true;
        }

    }

    if (flag == Function2 && value ==  MULT && right->flag == Number && left->flag != Number) {
        node* tmp = NULL;
        tmp = left;
        left = right;
        right = tmp;
        _return = true;
    }


    if (left != NULL && (left->flag == Function1 || left->flag == Function2)) {
        _return = _return + left->simplify();
    }

    if (right != NULL && (right->flag == Function1 || right->flag == Function2)) {
        _return = _return + right->simplify();
    }

    return _return;

}

void node::Simplify() {
    bool changes = true;

    while (changes == true) {
        changes = calculate() + simplify();
    }
}

void node::duplicate (node* duplicatedNode) {

    duplicatedNode->value = value;
    duplicatedNode->flag = flag;


    if (left != NULL) {
        node* tmpPointer1 = new node();
        duplicatedNode->left = tmpPointer1;
        left->duplicate (tmpPointer1);
    }

    if (right != NULL) {
        node* tmpPointer2 = new node();
        duplicatedNode->right = tmpPointer2;
        right->duplicate (tmpPointer2);
    }

}

void node::differentiator (char variableValue, FILE* ptrResult) {

    if (flag == Number && value != 0) {
        value = 0;

    }

    if ( (flag == Variable) && (value != variableValue)) {
        value = 0;
        flag = Number;
    }

    if ( (flag == Variable) && (value == variableValue)) {
        value = 1;
        flag = Number;
    }

    if (flag == Function2 && value == PLUS) {
        left->differentiator (variableValue, ptrResult);
        right->differentiator (variableValue, ptrResult);
    }

    if (flag == Function2 && value == MINUS) {
        left->differentiator (variableValue, ptrResult);
        right->differentiator (variableValue, ptrResult);
    }

    if (flag == Function2 && value ==  MULT) {

        node* newLeftNode = new node();
        duplicate (newLeftNode);
        node* newRightNode = new node();
        duplicate (newRightNode);
        delete left;
        delete right;
        left = newLeftNode;
        right = newRightNode;
        value = PLUS; //+
        left->left->differentiator (variableValue, ptrResult);
        right->right->differentiator (variableValue, ptrResult);

    }

    if (flag == Function2 && value == DIV) {
        node* uNode = new node();
        node* uNode2 = new node();
        node* vNode = new node();
        node* vNode2 = new node();
        node* vNode3 = new node();
        left->duplicate (uNode);
        left->duplicate (uNode2);
        right->duplicate (vNode);
        right->duplicate (vNode2);
        right->duplicate (vNode3);
        delete left;
        delete right;
        left = new node ("-");
        left->left = new node ("*");
        left->right = new node ("*");
        left->left->left = uNode;
        left->left->right = vNode;
        left->right->left = vNode2;
        left->right->right = uNode2;
        right = new node ("^");
        right->left = vNode3;
        right->right = new node ("2");
        left->left->left->differentiator (variableValue, ptrResult);
        left->right->left->differentiator (variableValue, ptrResult);

    }

    if (flag == Function2 && value == POW) {

        node* uNode1 = new node();
        node* uNode2 = new node();
        node* uNode3 = new node();
        node* uNode4 = new node();
        left->duplicate (uNode1);
        left->duplicate (uNode2);
        left->duplicate (uNode3);
        left->duplicate (uNode4);

        node* vNode1 = new node();
        node* vNode2 = new node();
        node* vNode3 = new node();
        node* vNode4 = new node();
        right->duplicate (vNode1);
        right->duplicate (vNode2);
        right->duplicate (vNode3);
        right->duplicate (vNode4);

        delete left;
        delete right;

        value = PLUS; //+
        left = new node ("*");
        left->left = new node ("*");
        left->right = uNode1;
        left->left->left = vNode1;
        left->left->right = new node ("^");
        left->left->right->left = uNode2;
        left->left->right->right = new node ("-");
        left->left->right->right->left = vNode2;
        left->left->right->right->right = new node ("1");
        right = new node ("*");
        right->right = new node ("ln");
        right->right->left = uNode4;
        right->left = new node ("*");
        right->left->left = new node ("^");
        right->left->left->left = uNode3;
        right->left->left->right = vNode3;
        right->left->right = vNode4;
        uNode1->differentiator (variableValue, ptrResult);
        vNode4->differentiator (variableValue, ptrResult);

    }

    if (flag == Function1 && value == 1) {

        value =  MULT; // *
        flag = Function2;
        node* newNode = new node();
        left->duplicate (newNode);
        right = new node ("cos");
        right->left = newNode;
        left->differentiator (variableValue, ptrResult);


    }

    if (flag == Function1 && value == _cos) {
        value =  MULT; //*
        flag = Function2;
        node* newNode = new node();
        left->duplicate (newNode);
        right = new node ("*");
        right->left = new node ("-1");
        right->right = new node ("sin");
        right->right->left = newNode;
        left->differentiator (variableValue, ptrResult);

    }

    if (flag == Function1 && value == _tg) {

        value = DIV; // /
        flag = Function2;
        node* newNode = new node();
        left->duplicate (newNode);
        right = new node ("^");
        right->left = new node ("cos");
        right->left->left = newNode;
        right->right = new node ("2");
        left->differentiator (variableValue, ptrResult);

    }

    if (flag == Function1 && value == _ctg) {

        value = DIV; // /
        flag = Function2;
        node* newNode = new node();
        left->duplicate (newNode);
        right = new node ("*");
        right->left = new node ("-1");
        right->right = new node ("^");
        right->right->left = new node ("cos");
        right->right->left->left = newNode;
        right->right->right = new node ("2");
        left->differentiator (variableValue, ptrResult);

    }

    if (flag == Function1 && value == _exp) {
        value =  MULT; //*
        flag = Function2;
        node* newNode = new node();
        left->duplicate (newNode);
        right = new node ("exp");
        right->left = newNode;
        left->differentiator (variableValue, ptrResult);

    }

    if (flag == Function1 && value == _ln) {

        value = DIV; // /
        flag = Function2;
        node* newNode = new node();
        left->duplicate (newNode);
        right = newNode;
        left->differentiator (variableValue, ptrResult);
    }

    if (flag == Function1 && value == _asin) {

        value = DIV; // /
        flag = Function2;

        node* newNode = new node();
        left->duplicate (newNode);

        right = new node ("^");
        right->left = new node ("-");
        right->left->left = new node ("1");
        right->left->right = new node ("^");
        right->left->right->left = newNode;
        right->left->right->right = new node ("2");
        right->right = new node ("/");
        right->right->left = new node ("1");
        right->right->right = new node ("2");
        left->differentiator (variableValue, ptrResult);
    }

    if (flag == Function1 && value == _acos) {
        value = DIV; // /
        flag = Function2;

        node* newNode = new node();
        left->duplicate (newNode);

        right = new node ("*");
        right->left = new node ("-1");
        right->right = new node ("^");
        right->right->left = new node ("-");
        right->right->left->left = new node ("1");
        right->right->left->right = new node ("^");
        right->right->left->right->left = newNode;
        right->right->left->right->right = new node ("2");
        right->right->right = new node ("/");
        right->right->right->left = new node ("1");
        right->right->right->right = new node ("2");
        left->differentiator (variableValue, ptrResult);

    }

    if (flag == Function1 && value == _actg) {
        value = DIV; // /
        flag = Function2;

        node* newNode = new node();
        left->duplicate (newNode);

        right = new node ("*");
        right->left = new node ("-1");
        right->right = new node ("+");
        right->right->left = new node ("^");
        right->right->left->left = newNode;
        right->right->left->right = new node ("2");
        right->right->right = new node ("1");
        left->differentiator (variableValue, ptrResult);

    }

    if (flag == Function1 && value == _atg) {
        value = DIV; // /
        flag = Function2;

        node* newNode = new node();
        left->duplicate (newNode);

        right = new node ("+");
        right->left = new node ("^");
        right->left->left = newNode;
        right->left->right = new node ("2");
        right->right = new node ("1");
        left->differentiator (variableValue, ptrResult);

    }
}

char* node::input (char* buffer) {
    //тут нужна проверка что строка не гавно в принципе постараюсь по ходy анализа это проверять
    /**приоритеты операций:
    ()
    func1
    ^
    *:
    +-
    **/
    bool _break = false;
    int countBrackets = 0;

    if (strlen (buffer) == 1 && (buffer[0] < 48 || buffer[0] > 57)) {
        flag = Variable;
        value = buffer[0];
        _break = true;
        assert (countBrackets == 0); //broken brackets

    }

    for (int i = strlen (buffer) - 1; i >= 0; i--) {

        if (buffer[i] == '(') countBrackets++;

        if (buffer[i] == ')') countBrackets--;

        if (countBrackets == 0) {
            if (buffer[i] == '+' || buffer[i] == '-') {

                flag = Function2;

                if (buffer[i] == '+') value = funcVal ("+");

                if (buffer[i] == '-') value = funcVal ("-");

                buffer[i] = '\0';

                assert (strlen (buffer) != 0);
                assert (strlen (&buffer[i + 1]) != 0);

                left = new node();
                left->input (buffer);
                right = new node();
                right->input (&buffer[i + 1]);
                _break = true;
                assert (countBrackets == 0); //broken brackets
                break; //?
            }
        }
    }

    if (_break == false) {

        for (int i = strlen (buffer) - 1; i >= 0; i--) {

            if (buffer[i] == '(') countBrackets++;

            if (buffer[i] == ')') countBrackets--;

            if (countBrackets == 0) {
                if (buffer[i] == '*' || buffer[i] == '/') {

                    flag = Function2;

                    if (buffer[i] == '*') value = funcVal ("*");

                    if (buffer[i] == '/') value = funcVal ("/");

                    buffer[i] = '\0';

                    assert (strlen (buffer) != 0);
                    assert (strlen (&buffer[i + 1]) != 0);

                    left = new node();
                    left->input (buffer);
                    right = new node();
                    right->input (&buffer[i + 1]);
                    _break = true;
                    assert (countBrackets == 0); //broken brackets
                    break; //?
                }
            }
        }
    }

    if (_break == false) {

        for (int i = 0; i < strlen (buffer); i++) {

            if (buffer[i] == '(') countBrackets++;

            if (buffer[i] == ')') countBrackets--;

            if (countBrackets == 0) {
                if (buffer[i] == '^') {

                    flag = Function2;
                    value = funcVal ("^");

                    buffer[i] = '\0';

                    assert (strlen (buffer) != 0);
                    assert (strlen (&buffer[i + 1]) != 0);

                    left = new node();
                    left->input (buffer);
                    right = new node();
                    right->input (&buffer[i + 1]);
                    _break = true;
                    assert (countBrackets == 0); //broken brackets
                    break; //?
                }
            }
        }
    }

    if (_break == false) {
        ;

        for (int i = 0; i < strlen (buffer); i++) {

            if (buffer[i] == '(') countBrackets++;

            if (buffer[i] == ')') countBrackets--;

            if (countBrackets == 0) {
                if (buffer[i] == 's') {
                    flag = Function1;
                    value = funcVal ("sin");
                    left = new node;
                    left->input (&buffer[i + 3]);
                    _break = true;
                    assert (countBrackets == 0); //broken brackets
                    break;
                } else if (buffer[i] == 'c' && buffer[i + 1] == 'o') {
                    flag = Function1;
                    value = funcVal ("cos");
                    left = new node;
                    left->input (&buffer[i + 3]);
                    _break = true;
                    assert (countBrackets == 0); //broken brackets
                    break;
                } else if (buffer[i] == 't') {
                    flag = Function1;
                    value = funcVal ("tg");
                    left = new node;
                    left->input (&buffer[i + 2]);
                    _break = true;
                    assert (countBrackets == 0); //broken brackets
                    break;
                } else if (buffer[i] == 'c' && buffer[i + 1] == 't') {
                    flag = Function1;
                    value = funcVal ("ctg");
                    left = new node;
                    left->input (&buffer[i + 3]);
                    _break = true;
                    assert (countBrackets == 0); //broken brackets
                    break;
                } else if (buffer[i] == 'a') {
                    if (buffer[i + 1] == 's') {
                        flag = Function1;
                        value = funcVal ("asin");
                        left = new node;
                        left->input (&buffer[i + 4]);
                        _break = true;
                        assert (countBrackets == 0); //broken brackets
                        break;

                    } else if (buffer[i + 1] == 'c' && buffer[i + 2] == 'o') {
                        flag = Function1;
                        value = funcVal ("acos");
                        left = new node;
                        left->input (&buffer[i + 4]);
                        _break = true;
                        assert (countBrackets == 0); //broken brackets
                        break;
                    } else if (buffer[i + 1] == 't') {
                        flag = Function1;
                        value = funcVal ("atg");
                        left = new node;
                        left->input (&buffer[i + 3]);
                        _break = true;
                        assert (countBrackets == 0); //broken brackets
                        break;
                    } else if (buffer[i + 1] == 'c' && buffer[i + 2] == 't') {
                        flag = Function1;
                        value = funcVal ("actg");
                        left = new node;
                        left->input (&buffer[i + 4]);
                        _break = true;
                        assert (countBrackets == 0); //broken brackets
                        break;
                    }
                } else if (buffer[i] == 'e') {
                    flag = Function1;
                    value = funcVal ("exp");
                    left = new node;
                    left->input (&buffer[i + 3]);
                    _break = true;
                    assert (countBrackets == 0); //broken brackets
                    break;
                } else if (buffer[i] == 'l') {
                    flag = Function1;
                    value = funcVal ("ln");
                    left = new node;
                    left->input (&buffer[i + 2]);
                    _break = true;
                    assert (countBrackets == 0); //broken brackets
                    break;
                }
            }
        }
    }

    if (_break == false) {
        if (buffer[0] == '(' && buffer[strlen (buffer) - 1] == ')') {
            buffer[strlen (buffer) - 1] = '\0';
            input (&buffer[1]);
            _break = true;
            assert (countBrackets == 0); //broken brackets
        }
    }

    if (_break == false) {
        flag = Number;
        value = atof (buffer);
    }

}


