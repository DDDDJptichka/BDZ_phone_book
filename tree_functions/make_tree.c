#include "structs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

unsigned short flag_of_search;

int compare_strs(user_t user, leaf_t *leaf){

    switch (flag_of_search)
    {
    case 1:
    
        return strcasecmp(user.first_name, leaf->user.first_name);
    
    case 2:

        return strcasecmp(user.second_name, leaf->user.second_name);
    
    case 3:

        return strcasecmp(user.third_name, leaf->user.third_name);

    case 4:

        return strcasecmp(user.telephone_number, leaf->user.telephone_number);
    
    case 5:

        return strcasecmp(user.another_info, leaf->user.another_info);    

    case 6:

        if (strcasecmp(user.first_name, leaf->user.first_name) == 0){

            if (strcasecmp(user.second_name, leaf->user.second_name) == 0){

                return strcasecmp(user.third_name, leaf->user.third_name);

            }

            return strcasecmp(user.second_name, leaf->user.second_name);

        }

        return strcasecmp(user.first_name, leaf->user.first_name);

    }
    
    return -2;
}

leaf_t* add_leaf(leaf_t **root, node_t* new_node){

    leaf_t *new_leaf = (leaf_t*)malloc(sizeof(leaf_t));

    new_leaf->color = 'R';
    new_leaf->user = new_node->user;
    new_leaf->left = NULL;
    new_leaf->right = NULL;
    new_leaf->parent = NULL;
    new_leaf->node = new_node;
    
    leaf_t *parent_leaf = *root;

    if (*root == NULL){

        *root = new_leaf;
        new_leaf->color = 'B';

        return new_leaf;

    }

    while (parent_leaf != NULL){

        new_leaf->parent = parent_leaf;

        if (compare_strs(new_node->user, parent_leaf) > 0){

            parent_leaf = parent_leaf->right;

        }
        else{

            parent_leaf = parent_leaf->left;

        }

    }

    parent_leaf = new_leaf->parent;
    
    if (compare_strs(new_node->user, new_leaf->parent) > 0){

        parent_leaf->right = new_leaf;

    }
    else{

        parent_leaf->left = new_leaf;

    }

    return new_leaf;
}

int left_rotate(leaf_t **root, leaf_t *leaf){

    if ((leaf == NULL) || (leaf->right == NULL)){

        return 0;

    }

    leaf_t *temporary_leaf = leaf->right;

    leaf->right = temporary_leaf->left;

    if (temporary_leaf->left != NULL){

        temporary_leaf->left->parent = leaf;

    }

    temporary_leaf->parent = leaf->parent;

    if (leaf->parent != NULL){

        if (leaf->parent->left == leaf){

            leaf->parent->left = temporary_leaf;

        }
        else{

            leaf->parent->right = temporary_leaf;

        }

    }
    else{

        *root = temporary_leaf;

    }

    leaf->parent = temporary_leaf;
    temporary_leaf->left = leaf;

    return 0;
    
}

int right_rotate(leaf_t **root, leaf_t *leaf){

    if ((leaf == NULL) || (leaf->left == NULL)){

        return 1;

    }

    leaf_t *temporary_leaf = leaf->left;

    leaf->left = temporary_leaf->right;

    if (temporary_leaf->right != NULL){

        temporary_leaf->right->parent = leaf;

    }

    temporary_leaf->parent = leaf->parent;

    if (leaf->parent != NULL){

        if (leaf->parent->right == leaf){

            leaf->parent->right = temporary_leaf;

        }
        else{

            leaf->parent->left = temporary_leaf;
            
        }

    }
    else{

        *root = temporary_leaf;

    }

    leaf->parent = temporary_leaf;
    temporary_leaf->right = leaf;

    return 0;
}

void balancing_of_tree(leaf_t **root, leaf_t *leaf){

    leaf_t *uncle;

    while ((leaf != *root) && (leaf->parent->color == 'R')){

        if (leaf->parent->parent->left == leaf->parent){

            uncle = leaf->parent->parent->right;

            if ((uncle != NULL) && (uncle->color == 'R')){

                leaf->parent->color = 'B';
                uncle->color = 'B';
                leaf->parent->parent->color = 'R';
                leaf = leaf->parent->parent;

            }
            else{

                if (leaf == leaf->parent->right){

                    leaf = leaf->parent;
                    left_rotate(root, leaf);

                }

                leaf->parent->color = 'B';
                leaf->parent->parent->color = 'R';
                right_rotate(root, leaf->parent->parent);

            }

        }
        else{

            uncle = leaf->parent->parent->left;

            if ((uncle != NULL) && (uncle->color == 'R')){

                leaf->parent->color = 'B';
                uncle->color = 'B';
                leaf->parent->parent->color = 'R';
                leaf = leaf->parent->parent;

            }
            else{

                if (leaf == leaf->parent->left){

                    leaf = leaf->parent;
                    right_rotate(root, leaf);

                }

                leaf->parent->color = 'B';
                leaf->parent->parent->color = 'R';
                left_rotate(root, leaf->parent->parent);

            }

        }

    }

    (*root)->color = 'B';

}

leaf_t** convert_list_to_tree(node_t **node, unsigned short flag){

    node_t *curr_node = *node;
    leaf_t **root = (leaf_t**)malloc(sizeof(leaf_t*));

    *root = NULL;

    flag_of_search = flag;
    
    while (curr_node != NULL){

        balancing_of_tree(root, add_leaf(root, curr_node));
        curr_node = curr_node->right;

    }

    return root;
}

leaf_t* find_min_leaf(leaf_t *leaf){

    while ((leaf != NULL) && (leaf->left != NULL)){

        leaf = leaf->left;

    }

    return leaf;

}

void switch_local_roots(leaf_t **root, leaf_t *local_root_1, leaf_t *local_root_2){

    if (local_root_1->parent == NULL){

        *root = local_root_2;

    }
    else if (local_root_1 == local_root_1->parent->left){

        local_root_1->parent->left = local_root_2;

    }
    else{

        local_root_1->parent->right = local_root_2;

    }
    
    if (local_root_2 != NULL){

        local_root_2->parent = local_root_1->parent;

    }
    

}

void balancing_tree_for_del(leaf_t **root, leaf_t *leaf){

    if (leaf == NULL){

        return;

    }

    while (((leaf == NULL) || (leaf->color == 'B')) && (leaf != *root)){

        if (leaf == leaf->parent->left){

            leaf_t *leaf_bro = leaf->parent->right;

            if ((leaf_bro != NULL) && (leaf_bro->color == 'R')){

                leaf_bro->color = 'B';
                leaf->parent->color = 'R';
                left_rotate(root, leaf->parent);
                leaf_bro = leaf->parent->right;

            }

            if ((leaf_bro != NULL) && (((leaf_bro->left == NULL) || (leaf_bro->left->color == 'B')) && ((leaf_bro->right == NULL) || (leaf_bro->right->color == 'B')))){

                leaf_bro->color = 'R';
                leaf = leaf->parent;

            }
            else{

                if ((leaf_bro != NULL) && ((leaf_bro->right == NULL) || (leaf_bro->right->color == 'B'))){

                    if (leaf_bro->left != NULL){

                        leaf_bro->left->color = 'B';

                    }

                    leaf_bro->color = 'R';
                    right_rotate(root, leaf_bro);
                    leaf_bro = leaf->parent->right;

                }

                if (leaf_bro != NULL){

                    leaf_bro->color = leaf->parent->color;
                    
                    if (leaf_bro->right != NULL){

                        leaf_bro->right->color = 'B';

                    }
                }
                
                leaf->parent->color = 'B';
                left_rotate(root, leaf->parent);
                leaf = *root;
            }
        }
        else{

            leaf_t *leaf_bro = leaf->parent->left;

            if ((leaf_bro != NULL) && (leaf_bro->color == 'R')){

                leaf_bro->color = 'B';
                leaf->parent->color = 'R';
                right_rotate(root, leaf->parent);
                leaf_bro = leaf->parent->left;

            }

            if ((leaf_bro != NULL) && (((leaf_bro->right == NULL) || (leaf_bro->right->color == 'B')) && ((leaf_bro->left == NULL) || (leaf_bro->left->color == 'B')))){

                leaf_bro->color = 'R';
                leaf = leaf->parent;

            }
            else{

                if ((leaf_bro != NULL) && ((leaf_bro->left == NULL) || (leaf_bro->left->color == 'B'))){

                    if (leaf_bro->right != NULL){

                        leaf_bro->right->color = 'B';

                    }

                    leaf_bro->color = 'R';
                    left_rotate(root, leaf_bro);
                    leaf_bro = leaf->parent->left;

                }

                if (leaf_bro != NULL){

                    leaf_bro->color = leaf->parent->color;

                    if (leaf_bro->left != NULL){

                        leaf_bro->left->color = 'B';

                    }

                }

                leaf->parent->color = 'B';
                right_rotate(root, leaf->parent);
                leaf = *root;

            }

        }

    }

    if (leaf != NULL){

        leaf->color = 'B';

    }

}

void delete_leaf(leaf_t **root, leaf_t *leaf){

    leaf_t *curr = leaf;
    leaf_t *new_leaf = NULL;
    char curr_leaf_color = leaf->color;

    if ((leaf->left == NULL) && (leaf->right == NULL)){

        if (leaf->parent == NULL){

            *root == NULL;
            free(leaf);
            return;

        }

        leaf_t* parent = leaf->parent;
        new_leaf = NULL;

        if (parent->left == leaf){

            parent->left = NULL;

        }
        else{

            parent->right = NULL;

        }

        if (curr_leaf_color == 'B'){

            balancing_tree_for_del(root, NULL);

        }

        free(leaf);
        return;
        
    }
    else if (leaf->left == NULL){

        new_leaf = leaf->right;
        switch_local_roots(root, leaf, leaf->right);

    }
    else if (leaf->right == NULL){

        new_leaf = leaf->left;
        switch_local_roots(root, leaf, leaf->left);

    }
    else{

        curr = find_min_leaf(leaf->right);
        curr_leaf_color = curr->color;
        new_leaf = curr->right;

        node_t* tmp_node = leaf->node;
        leaf->node = curr->node;
        curr->node = tmp_node;

        if (curr->parent == leaf){

            if (new_leaf != NULL){

                new_leaf->parent = curr;

            }

        }
        else{

            switch_local_roots(root, curr, curr->right);
            curr->right = leaf->right;
            
            if (curr->right != NULL){

                curr->right->parent = curr;

            }

        }

        switch_local_roots(root, leaf, curr);
        curr->left = leaf->left;

        if (curr->left != NULL){

            curr->left->parent = curr;

        }

        curr->color = leaf->color;
    }

    if (curr_leaf_color == 'B'){

        balancing_tree_for_del(root, new_leaf);
        
    }

    free(leaf);

}

void clean_tree(leaf_t *leaf){

    if (leaf != NULL){

        clean_tree(leaf->left);
        clean_tree(leaf->right);

    }

    free(leaf);

}

int pr(leaf_t **root){

    leaf_t *curr = *root;

    if (curr != NULL){

        pr(&(curr->left));
        printf("%s %s %s %s %s\n", curr->user.first_name, curr->user.second_name, curr->user.third_name, curr->user.telephone_number, curr->user.another_info);
        pr(&(curr->right));

    }

    return 0;
}