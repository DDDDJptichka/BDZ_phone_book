#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structs.h"

unsigned short flag_of_search;
unsigned int num_of_user = 0;

int compare_strs_for_search (const char* keyword, leaf_t* current_leaf){

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

int search_user(leaf_t* root, snode_t** snd_root, snode_t** last_node, const char *keyword, unsigned short int flag){

    int cmp_res;

    flag_of_search = flag;
    cmp_res = 0;

    if (root != NULL){

        cmp_res = compare_strs_for_search(keyword, root);

        if (cmp_res > 0){

            search_user(root->right, snd_root, last_node, keyword, flag_of_search);

        }
        else if (cmp_res < 0){

            search_user(root->left, snd_root, last_node, keyword, flag_of_search);

        }
        else{

            snode_t* snode = (snode_t*)malloc(sizeof(snode_t));
            snode->leaf = root;
            snode->right = NULL;

            if (*last_node != NULL){

                (*last_node)->right = snode;

            }
            else{

                *snd_root = snode;

            }

            *last_node = snode;
            
            ++num_of_user;
            printf("%d: %s %s %s %s %s\n", num_of_user, root->user.first_name, root->user.second_name, root->user.third_name, root->user.telephone_number, root->user.another_info);
            search_user(root->left, snd_root, last_node, keyword, flag_of_search);
            search_user(root->right, snd_root, last_node, keyword, flag_of_search);

        }

    }

    return num_of_user;

}

void clean_num(unsigned short int zero){

    num_of_user = zero;

}