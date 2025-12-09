#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include "structs.h"
#define MAX_LEN_OF_FILE 261
#define KBx64 8 * 1024 * 8

char input_file_name[MAX_LEN_OF_FILE], output_file_name[MAX_LEN_OF_FILE];

void initialize_in_out_files(){

    printf("¬ведите название исходного файла в формате:  название файла.расширение   <--------  ");
    scanf("%260s", input_file_name);

    printf("\n¬ведите название файла,\nв котором (который хотите создать) хотите увидеть редактированный результат базы данных\nввoд в формате:  название файла.расширение   <--------  ");
    scanf("%260s", output_file_name);

    fflush(stdin);
    fflush(stdout);

}