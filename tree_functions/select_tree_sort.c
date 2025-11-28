#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include "add_new_person.h"
#include "make_tree.h"
#include "make_list.h"
#include "search.h"

int select_tree_sort(leaf_t** root, node_t** list_root){
    
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");

    char flag_of_operation;
    int search_flag, check_input;
    char buffer[500];

    check_input = 0;

    printf("\nСписок возможных операций: \n\nНайти информацию о пользователе   ------- Введите: S\nДобавить пользователя ------------------- Введите: A\nУдалить пользователя -------------------- Введите: D\nЗавершить работу ------------------------ Введите: Z\n\n");
    //getchar();
    flag_of_operation = getc(stdin);

    switch (flag_of_operation){

    case 'S':
        
        printf("\nПо какому полю ищем?\n\n");
        printf("1 - по имени\n2 - по фамилии\n3 - по отчеству\n4 - по номеру телефона\n5 - по доп. информации\n\n");
        check_input = scanf("%d", &search_flag);

        while ((check_input != 1) && (search_flag != 1) && (search_flag != 2) && (search_flag != 3) && (search_flag != 4) && (search_flag != 5)){

            printf("\nСмотри, че пишешь\nПо какому полю ищем?\n\n");
            printf("1 - по имени\n2 - по фамилии\n3 - по отчеству\n4 - по номеру телефона\n5 - по доп. информации\n\n");
            check_input = scanf("%d", &search_flag);
            fflush(stdout);
            fflush(stdin);
            
        }
        
        printf("\nВведите слово для поиска\n\n");
        scanf("%499s", buffer);
        printf("\n");

        search_user(*root, buffer, search_flag);
        fflush(stdout);
        fflush(stdin);
        return 0;

    case 'A':{

        user_t new_user = add_new_person();

        add_to_list(list_root, new_user);
        balancing_of_tree(root, add_leaf(root, new_user));
        printf("\n----------------------Пользователь добавлен----------------------\n");
        return 1;
    }

    case 'Z':

        return -1;

    default:

        return -2;
    
    }

}