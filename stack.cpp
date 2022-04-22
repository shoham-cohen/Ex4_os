#include <stdio.h>
#include <string>
#include "stack.hpp"
#include <iostream>
#include <mutex>


using namespace std;
using namespace my_namespace;

pthread_mutex_t  my_lock = PTHREAD_MUTEX_INITIALIZER;

//default constractor
my_namespace::Node::Node(){
    this -> next = NULL;
}

my_namespace::Node::Node(string &data){
    this -> next = NULL;
    this -> data = data;
}

my_namespace::Stack::Stack(){
    this -> head = new Node();
    this -> length = 0;
}

int my_namespace::Stack::push(string data){
    pthread_mutex_lock(&my_lock);
    //data cant be longer than 1024 bytes
    if(data.size() > 1024){
        pthread_mutex_unlock(&my_lock);
        throw runtime_error("cant handle with string that longer than 1024 chars");
    }
    Node *new_node = new Node(data);
    new_node -> next = this -> head;
    this -> head = new_node;
    this -> length += 1;
    pthread_mutex_unlock(&my_lock);
    return 1;
}

string my_namespace::Stack::pop(){
    Node *temp = this->head;
    this-> head = temp->next_node();
    string res = temp->get_data();
    this->length -= 1;
    return res;
}

string my_namespace::Stack::top(){
    pthread_mutex_lock(&my_lock);
    string res = this->top_helper();
    pthread_mutex_unlock(&my_lock);
    return res;
}

string my_namespace::Stack::top_helper(){
    return this->head->data;
}