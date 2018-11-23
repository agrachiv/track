/*
 * node.cpp - extremly basic binary tree with char* data
 * @author Andrey Agrachev agrachiv99@gmail.com
 */

#include "node.h"

node::node(const char* input_string): _string(nullptr), left_ptr(nullptr), right_ptr(nullptr) {
    assert (input_string != nullptr);
    try {
        _string = new char[strlen(input_string)];
    } catch (const std::bad_alloc&) {
        assert(false);
    }
    assert(_string != nullptr);
    strcpy(_string, input_string);
    assert(strcmp(_string, input_string) == 0);
}

node::~node() {
    if (left_ptr != nullptr)
        delete left_ptr;
    if (right_ptr != nullptr)
        delete right_ptr;
    delete _string;
}

void node::set_string(const char* new_string){
    assert (new_string != nullptr);
    _string = new char[strlen(new_string)];
    strcpy(_string, new_string);
}

char* node::get_string() {
    return _string;
}

void node::add_to_left (const char* new_string) {
    assert(left_ptr == nullptr);
    try {
        left_ptr = new node (new_string);
    } catch (const std::bad_alloc&) {
        assert(false);
    }
}

void node::add_to_right (const char* new_string) {
    assert(right_ptr == nullptr);
    try {
        right_ptr = new node (new_string);
    } catch (const std::bad_alloc&) {
        assert(false);
    }
}

void node::add_to_left () {
    assert(left_ptr == nullptr);
    try {
        left_ptr = new node;
    } catch (const std::bad_alloc&) {
        assert(false);
    }
}

void node::add_to_right () {
    assert(right_ptr == nullptr);
    try {
        right_ptr = new node;
    } catch (const std::bad_alloc&) {
        assert(false);
    }
}

void node::delete_left_branch() {
    assert(left_ptr != nullptr);
    delete left_ptr;
    left_ptr = nullptr;
}

void node::delete_right_branch() {
    assert(right_ptr != nullptr);
    delete right_ptr;
    left_ptr = nullptr;
}

bool node::is_leaf() {
    if (left_ptr == nullptr && right_ptr == nullptr)
        return true;
    return false;
}


