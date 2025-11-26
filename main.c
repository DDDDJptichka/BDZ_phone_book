#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include "copy.h"
#include "add_new_person.h"
#include "make_list.h"
#include "make_tree.h"
#include "select_tree_sort.h"

extern char input_file_name[];
extern char output_file_name[];

int main(){

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");
    
    int row_num;
    node_t **users;
    leaf_t **root;
    
    initialize_in_out_files();
    copy(input_file_name, output_file_name);
    users = create_list(input_file_name, &row_num);
    

    // while ((y_or_n == 'Y') || (y_or_n == 'y')){
    //     add_new_person(y_or_n);
    //     copy("output_2.txt", output_file_name);
    //     initialize_add_new_person();

    // }

    root = convert_list_to_tree(users, row_num, 1);
    fflush(stdout);
    fflush(stdin);
    int fl = select_tree_sort(root);
    
    if (fl == 1){

        copy("output_2.txt", output_file_name);

    }

    while (fl != -1){

        fl = select_tree_sort(root);
        
        if (fl == 1){

            copy("output_2.txt", output_file_name);

        }

    }

    //add_people_to_matrix(create_matrix(input_file_name, &row_num), )
    
    //printf("\n%s, \n%d", a[1][2], a[1][2] == NULL);

    //printf("\n%d", row_num);
    //printf("\n%d", users[1].second_name[0] == '\0');

    // printf("%s ---- root\n", (*root)->user.first_name);
    // printf("%s ---- left\n", (*root)->left);
    // printf("%s ---- right\n", (*root)->right);
    // printf("%s ---- left--left\n", ((*root)->left)->left);
    // printf("%s ---- left--left--left\n", (((*root)->left)->left)->left);
    // printf("%s ---- left--left--right\n", (((*root)->left)->left)->right);


    return 0;
}