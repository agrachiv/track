#ifndef AKINATOR_H
#define AKINATOR_H

#include "node/node.cpp"
#include <stdio.h>
#include <string>

enum indents {
    BRACE_SHIFT = 1,
    BRACE_AND_SPACE_SHIFT = 2,
};

class akinator {
private:
    node* tree_root_ptr;
    char* data_file_path;

    void construct_data_tree ();
    void recursive_construct (char* current_data_buffer, node* current_node_ptr);
    void question_binary     (node* current_node_ptr);
    void add_new_personality (node* current_node_ptr);
    void decode (FILE* file_ptr, node* current_node_ptr);
public:
    akinator() = delete;
    ~akinator();
    akinator(const char* new_data_file_path);
    void play();

};

char* get_data_buffer(const FILE* file_ptr);
size_t get_file_size(const FILE* file_ptr);
void add_terminating_symbols(char* input_string);

#endif // AKINATOR_H
