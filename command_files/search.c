#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structs.h"

unsigned short flag_of_search;
unsigned int num_of_user = 0;

static int compare_strs_for_search (const char* keyword, leaf_t* current_leaf){

    switch (flag_of_search)
    {
    case 1:
    
        return strncasecmp(keyword, current_leaf->user.first_name, strlen(keyword));
    
    case 2:

        return strncasecmp(keyword, current_leaf->user.second_name, strlen(keyword));
    
    case 3:

        return strncasecmp(keyword, current_leaf->user.third_name, strlen(keyword));

    case 4:

        return strncasecmp(keyword, current_leaf->user.telephone_number, strlen(keyword));
    
    case 5:

        return strncasecmp(keyword, current_leaf->user.another_info, strlen(keyword));

    }

    return -2;
}

int search_user(leaf_t* root, const char *keyword, unsigned short int flag){

    leaf_t *current_leaf = root;
    flag_of_search = flag;

    while (current_leaf != NULL){

        if (compare_strs_for_search(keyword, current_leaf) > 0){

            current_leaf = current_leaf->right;

        }
        else if (compare_strs_for_search(keyword, current_leaf) < 0){

            current_leaf = current_leaf->left;

        }
        else{

            printf("%s %s %s %s %s\n", current_leaf->user.first_name, current_leaf->user.second_name, current_leaf->user.third_name, current_leaf->user.telephone_number, current_leaf->user.another_info);
            ++num_of_user;
            search_user(current_leaf->left, keyword, flag_of_search);
            search_user(current_leaf->right, keyword, flag_of_search);
            break;

        }

    }

    return 0;

}