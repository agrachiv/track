/*
 * node.h - extremly basic binary tree with char* data
 * @author Andrey Agrachev agrachiv99@gmail.com
 */

#ifndef NODE_H
#define NODE_H

#include <exception>
#include <assert.h>
#include <string.h>

class node {

private:
    char* _string;

public:
    node* right_ptr;
    node* left_ptr;

    node():_string(nullptr), left_ptr(nullptr), right_ptr(nullptr) {}
    node(const char* input_string);
    ~node();

    void  set_string   (const char* new_string);
    char* get_string   ();
    void  add_to_left  (const char* new_string);
    void  add_to_right (const char* new_string);
    void  add_to_left  ();
    void  add_to_right ();
    void  delete_left_branch  ();
    void  delete_right_branch ();
    bool  is_leaf ();
};

#endif // NODE_H
