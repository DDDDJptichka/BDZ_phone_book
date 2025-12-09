#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include "init_files.h"
#include "add_new_person.h"
#include "make_list.h"
#include "make_tree.h"
#include "do_operations.h"
#define PRINT_FLAG 6
#define FIRSTNAME 1
#define EXIT -1

extern char input_file_name[];
extern char output_file_name[];

int main(){

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");
    
    node_t **users;
    leaf_t **root;
    int operation_code;
    
    initialize_in_out_files();
    users = create_list(input_file_name);  
    root = convert_list_to_tree(users, FIRSTNAME);
    operation_code = do_operation(root, users);

    while (operation_code != EXIT){

        operation_code = do_operation(root, users);

    }

    FILE *out;

    out = fopen(output_file_name, "w");
    print_tree(convert_list_to_tree(users, PRINT_FLAG), out);
    fclose(out);
    
    if (*users != NULL){

        clean_list(*users);
        free(users);

    }

    if (*root != NULL){

        clean_tree(*root);
        free(root);

    }

    return 0;
}