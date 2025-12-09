#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include "add_new_person.h"
#include "make_tree.h"
#include "make_list.h"
#include "search.h"

int last_search_flag = 0;

int do_operation(leaf_t** root, node_t** list_root){
    
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");

    char flag_of_operation;
    int search_flag = 0;
    char buffer[500];

    printf("\nСписок возможных операций: \n\nНайти информацию о пользователе --------- Введите: S\nДобавить пользователя ------------------- Введите: A\nУдалить пользователя -------------------- Введите: D\nЗавершить работу ------------------------ Введите: Z\n\n");
    flag_of_operation = getc(stdin);

    if ((flag_of_operation == 'S') || (flag_of_operation == 'D')){
        
        if (*root == NULL){

            printf("\n\nИскать/удалять некого, входных данных нет :(\n\n");
            fflush(stdout);
            fflush(stdin);
            return 0;

        }   

        snode_t** search_list = (snode_t**)malloc(sizeof(snode_t*));
        snode_t** last_snode = (snode_t**)malloc(sizeof(snode_t*));
        *search_list = NULL;
        *last_snode = NULL;
        unsigned int num_of_searched_users = 0;

        printf("\nПо какому полю ищем?\n\n");
        printf("1 - по имени\n2 - по фамилии\n3 - по отчеству\n4 - по номеру телефона\n5 - по доп. информации\n\n");
        scanf("%d", &search_flag);

        while ((search_flag != 1) && (search_flag != 2) && (search_flag != 3) && (search_flag != 4) && (search_flag != 5)){

            printf("\nСмотри, че пишешь!\n\nПо какому полю ищем?\n\n");
            printf("1 - по имени\n2 - по фамилии\n3 - по отчеству\n4 - по номеру телефона\n5 - по доп. информации\n\n");
            scanf("%d", &search_flag);
            fflush(stdout);
            fflush(stdin);
            
        }

        clean_num(0);
        printf("\nВведите слово для поиска\n\n");
        scanf("%499s", buffer);
        printf("\n");

        if (last_search_flag == search_flag){

            num_of_searched_users = search_user(*root, search_list, last_snode, buffer, search_flag);

        }
        else{

            clean_tree(*root);
            leaf_t** new_root = convert_list_to_tree(list_root, search_flag);
            *root = *new_root;
            free(new_root);
            num_of_searched_users = search_user(*root, search_list, last_snode, buffer, search_flag);

        }

        last_search_flag = search_flag;

        if (num_of_searched_users == 0){

            printf("------------- Такого пользователя не существует -------------\n");
            fflush(stdout);
            fflush(stdin);
            free(search_list);
            free(last_snode);
            return 0;

        }

        fflush(stdout);
        fflush(stdin);

        if ((flag_of_operation == 'D') && (root != NULL)){

            printf("\nВведите номер пользователя, которого хотите удалить\n\n");
            unsigned int input_check, num_of_user;
            input_check = scanf("%d", &num_of_user);

            while ((input_check == 0) || (num_of_user == 0) || (num_of_searched_users < num_of_user)){

                printf("\nВведите номер пользователя, которого хотите удалить\n\n");
                fflush(stdin);
                input_check = scanf("%d", &num_of_user);

            }

            fflush(stdout);
            fflush(stdin);
            
            snode_t** del_node = search_list;
                    
            for (unsigned int i = 1; i < num_of_user; ++i){

                *del_node = (*del_node)->right;

            }

            leaf_t* leaf_to_del = (*del_node)->leaf;
            node_t* node_to_del = (*del_node)->leaf->node;

            delete_leaf(root, leaf_to_del);
            del_from_list(list_root, node_to_del);
            clean_slist(*search_list);
            free(search_list);
            free(last_snode);

            printf("\n\n----------------------Пользователь удален----------------------\n\n");

        }
        
        clean_slist(*search_list);
        free(search_list);
        free(last_snode);
        
        return 0;
    }
    else if (flag_of_operation == 'A'){

        user_t new_user = add_new_person();
        node_t* new_node = add_to_list(list_root, new_user);

        if (root == NULL){

            add_leaf(NULL, new_node);
            return 1;

        }

        balancing_of_tree(root, add_leaf(root, new_node));
        printf("\n----------------------Пользователь добавлен----------------------\n");

        return 1;
    }
    else if (flag_of_operation == 'Z'){

        return -1;
    }
    else{

        return -2;
    
    }

}