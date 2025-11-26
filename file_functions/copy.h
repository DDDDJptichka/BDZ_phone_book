#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#define MAX_LEN_OF_FILE 261

char input_file_name[MAX_LEN_OF_FILE], output_file_name[MAX_LEN_OF_FILE];

void initialize_in_out_files(){

    printf("¬ведите название исходного файла в формате:  название файла.расширение   <--------  ");
    scanf("%260s", input_file_name);

    printf("\n¬ведите название файла,\nв котором (который хотите создать) хотите увидеть редактированный результат базы данных\nввoд в формате:  название файла.расширение   <--------  ");
    scanf("%260s", output_file_name);

}

int copy(const char *input, const char *output){

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");

    FILE *in, *out;
    in = fopen(input, "r");

    char letter, buff[65536];
    
    if (input == "output_2.txt"){
        
        out = fopen(output, "a");

    }
    else{

        out = fopen(output, "w");

    }

    if (in == NULL){

        return -1;

    } 

    while (fgets(buff, 65536, in) != NULL){

        fputs(buff, out);

    }

    fclose(in);
    fclose(out);
}