#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include "structs.h"

user_t add_new_person(){

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");

    FILE *out = fopen("output_2.txt", "w");

    user_t user;

    printf("\nВведите ИМЯ нового человека:    <--------   ");
    scanf("%99s", user.first_name);

    printf("\nВведите ФАМИЛИЮ нового человека:    <--------   ");
    scanf("%99s", user.second_name);

    printf("\nВведите ОТЧЕСТВО нового человека:    <--------   ");
    scanf("%99s", user.third_name);

    printf("\nВведите НОМЕР ТЕЛЕФОНА нового человека:    <--------   ");
    scanf("%29s", user.telephone_number);
    
    printf("\nВведите ДОПОЛНИТЕЛЬНУЮ ИНФОРМАЦИЮ о новом человеке:    <--------   ");
    getchar();
    
    fgets(user.another_info, ANOTHER_INFO_MAX_SIZE, stdin);

    user.another_info[strlen(user.another_info) - 1] = '\0';

    fprintf(out, "\n%s %s %s %s %s", user.first_name, user.second_name, user.third_name, user.telephone_number, user.another_info);

    fclose(out);

    return user;
}