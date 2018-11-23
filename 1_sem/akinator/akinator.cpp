#include "akinator.h"

//  non-member functions

size_t get_file_size (FILE* file_ptr) {

    fseek (file_ptr, 0, SEEK_END);
    size_t file_size = ftell (file_ptr);
    fseek (file_ptr, 0, SEEK_SET);
    return file_size;
}

char* get_data_buffer (FILE* file_ptr) {

    char* data_buffer = nullptr;
    size_t file_size = get_file_size(file_ptr);

    try {
        data_buffer = new char[file_size];
    } catch (const std::bad_alloc&) {
        assert(false);
    }

    fread (data_buffer, 1, file_size, file_ptr);
    add_terminating_symbols(data_buffer);

    return data_buffer;
}

void add_terminating_symbols(char* input_string) {
    int input_string_length = strlen(input_string);
    for (int i = 1; i < input_string_length; i++)
        if (input_string[i] == ' ')
            input_string[i] = '\0';
}

//  member-functions

akinator::akinator(const char* new_data_file_path): data_file_path(nullptr) {
    try {
        data_file_path = new char[strlen(new_data_file_path)];
    } catch (const std::bad_alloc&) {
        assert(false);
    }
    assert(data_file_path != nullptr);
    strcpy(data_file_path, new_data_file_path);
    assert(strcmp(data_file_path, new_data_file_path) == 0);
    construct_data_tree();
}

void akinator::construct_data_tree() {

    FILE* file_ptr = fopen(data_file_path, "rb");
    if (file_ptr == nullptr) {
        tree_root_ptr = new node();
        return;
    }
    char* data_buffer = get_data_buffer(file_ptr);
    assert (data_buffer[0] == '('); //corrupted_buffer
    tree_root_ptr = new node;
    recursive_construct(data_buffer, tree_root_ptr);

    delete data_buffer;
    fclose(file_ptr);
}

void akinator::recursive_construct(char* current_data_buffer, node* current_node_ptr) {

    if (*current_data_buffer != '(')
        return;
    current_node_ptr->set_string(&current_data_buffer[BRACE_SHIFT]);
    char* left_buffer = &current_data_buffer[BRACE_AND_SPACE_SHIFT + strlen(&current_data_buffer[BRACE_SHIFT])];
    int right_buffer_shift = BRACE_SHIFT;
    for (int brace_depth = 1; brace_depth != 0; right_buffer_shift++) {
        if (left_buffer[right_buffer_shift] == '(') {
            brace_depth++;
        }
        if (left_buffer[right_buffer_shift] == ')') {
            brace_depth--;
        }
    }
    char* right_buffer = &left_buffer[right_buffer_shift];

    if (*left_buffer == '(' && *right_buffer == '(') {
        current_node_ptr->add_to_left  ();
        current_node_ptr->add_to_right ();
        recursive_construct (left_buffer,  current_node_ptr->left_ptr );
        recursive_construct (right_buffer, current_node_ptr->right_ptr);
    }
}

void akinator::play() {
    if (tree_root_ptr->get_string() == nullptr) {
        tree_root_ptr->set_string("neizvestny_personaj");
    }
    question_binary(tree_root_ptr);
}

void akinator::add_new_personality(node* current_node_ptr) {
    char new_personality_name[32] = {};
    char new_personality_property[64] = {};
    current_node_ptr->add_to_left(current_node_ptr->get_string());

    printf ("\nVvedite imya zagadonnogo personazha (vmesto probela ispolzuyte '_')\n");
    scanf ("%s", new_personality_name);
    printf ("\nChem zagadannuy vami personaj otlichaetsa ot personaja: %s?\n", current_node_ptr->get_string());
    scanf ("%s", new_personality_property);
    current_node_ptr->set_string(new_personality_property);
    current_node_ptr->add_to_right(new_personality_name);
    printf ("\nV sleduyushiy raz ya ne promahnus!\n");
}

void akinator::question_binary(node* current_node_ptr) {
    char ans = {};
    if (current_node_ptr->is_leaf() == 1) {
        printf ("\nVash personaj: %s?\n", current_node_ptr->get_string());
        scanf ("%s", &ans);
        if (ans == 'n')
            add_new_personality(current_node_ptr);
        else if (ans == 'y')
            printf("\nYa kak vsegda ugadal!\n");
        else
            question_binary(current_node_ptr);
    } else {
        printf ("\nVash personaj %s y/n?\n", current_node_ptr->get_string());
        scanf ("%s", &ans);
        if (ans == 'n')
            question_binary(current_node_ptr->left_ptr);
        else if (ans == 'y')
            question_binary(current_node_ptr->right_ptr);
        else
            question_binary(current_node_ptr);
    }
}

akinator::~akinator() {
    FILE* file_ptr = fopen(data_file_path, "w");
    decode(file_ptr, tree_root_ptr);
    fclose(file_ptr);
    delete tree_root_ptr;
    delete data_file_path;

}

void akinator::decode(FILE* file_ptr, node* current_node_ptr) {
    fprintf (file_ptr, "(%s ", current_node_ptr->get_string());
    if (current_node_ptr->is_leaf() == false) {
        decode (file_ptr, current_node_ptr->left_ptr);
        decode (file_ptr, current_node_ptr->right_ptr);
    }
    fprintf (file_ptr, ")");
}


