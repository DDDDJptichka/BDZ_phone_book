#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include <string.h>
#include <locale.h>
#include <windows.h>
#define BUFF_MAX_SIZE (FIRST_NAME_MAX_SIZE + SECOND_NAME_MAX_SIZE + THIRD_NAME_MAX_SIZE + TELEPHONE_NUMBER_MAX_SIZE + ANOTHER_INFO_MAX_SIZE)
#define NUM_OF_INPUT_COLUMNS 5
// #define MAX_GB_MEM_SIZE 3
// #define MAX_BYTE_MEM_SIZE ((size_t)(1024 * 1024 * 1024 * MAX_GB_MEM_SIZE))

node_t** create_list (const char* input){

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");

    FILE *in;
    in = fopen(input, "r");

    int split_count;
    size_t len;
    char buffer[BUFF_MAX_SIZE];

    split_count = 0;

    node_t **users = (node_t**)malloc(sizeof(node_t*));
    node_t *last_node = NULL;
    (*users) = NULL;

    while (fgets(buffer, BUFF_MAX_SIZE, in) != NULL){
        
        len = strlen(buffer);

        if (len > 0 && ((buffer[len - 1] == '\n') || (buffer[len - 1] == '\r'))) {
            
            buffer[len - 1] = '\0';
            --len;

        }
       
        char *splited_str = strtok(buffer, " ");
        node_t *node = (node_t*)malloc(sizeof(node_t));
        
        node->left = NULL;
        node->right = NULL;
        node->user.first_name[0] = '\0';
        node->user.second_name[0] = '\0';
        node->user.third_name[0] = '\0';
        node->user.telephone_number[0] = '\0';
        node->user.another_info[0] = '\0';

        while (splited_str != NULL){

            if (strlen(splited_str) > 0) {
                
                if (split_count == 0){
                        
                    strncpy(node->user.first_name, splited_str, FIRST_NAME_MAX_SIZE - 1);
                    
                }
                else if (split_count == 1){

                    strncpy(node->user.second_name, splited_str, SECOND_NAME_MAX_SIZE - 1);
            
                }
                else if (split_count == 2){

                    strncpy(node->user.third_name, splited_str, THIRD_NAME_MAX_SIZE - 1);
    
                }
                else if (split_count == 3){

                    strncpy(node->user.telephone_number, splited_str, TELEPHONE_NUMBER_MAX_SIZE - 1);
                     
                }
                else if (split_count >= 4){

                    size_t len_of_info = strlen(node->user.another_info);

                    if (len_of_info != 0){

                        node->user.another_info[len_of_info] = ' ';    

                    }

                    strcat(node->user.another_info, splited_str);

                }
            }

            ++split_count;
            splited_str = strtok(NULL, " ");
                
        }

        if (split_count == 0){

            free(node);

        }

        split_count = 0;

        if (*users == NULL){

            *users = node;

        }
        else{

            last_node->right = node;
            node->left = last_node;

        }

        last_node = node;

    }

    fclose(in);
    
    return users;
}

node_t* add_to_list(node_t** root, user_t new_user){

    node_t* new_node = (node_t*)malloc(sizeof(node_t));

    if (*root == NULL){

        *root = new_node;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->user = new_user;
        return new_node;

    }

    if ((*root)->right != NULL){

        new_node->right = (*root)->right;
        new_node->left = *root;
        new_node->user = new_user;
        (*root)->right = new_node;
        new_node->right->left = new_node;

    }
    else{

        new_node->right = NULL;
        new_node->left = *root;
        new_node->user = new_user;
        (*root)->right = new_node;

    }

    return new_node;
}

void del_from_list(node_t** list_root, node_t* del_node){

    if (del_node->left == NULL){

        *list_root = del_node->right;
        
        if (del_node->right != NULL){

            del_node->right->left = NULL;

        }

    }
    else if (del_node->right == NULL){

        del_node->left->right = NULL;

    }
    else{

        del_node->left->right = del_node->right;
        del_node->right->left = del_node->left;

    }

    free(del_node);
}

void clean_slist(snode_t* snode){

    if (snode->right != NULL){

        clean_slist(snode->right);

    }

    free(snode);

}

void clean_list(node_t* node){

    if (node->right != NULL){

        clean_list(node->right);

    }

    free(node);

}