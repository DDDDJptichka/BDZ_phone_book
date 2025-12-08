#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include "copy.h"
#include "add_new_person.h"
#include "make_list.h"
#include "make_tree.h"
#include "tree_operations.h"

extern char input_file_name[];
extern char output_file_name[];

int main(){

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");
    
    node_t **users;
    leaf_t **root;
    
    initialize_in_out_files();
    //copy(input_file_name, output_file_name);
    users = create_list(input_file_name);
    
    root = convert_list_to_tree(users, 1);
    fflush(stdout);
    fflush(stdin);

    int fl = select_tree_sort(root, users);

    while (fl != -1){

        fl = select_tree_sort(root, users);

    }

    convert_list_to_tree(users, 6);    
    
    return 0;
}