#pragma once

#include "structs.h"

int compare_strs(user_t user, leaf_t *leaf);

leaf_t* add_leaf(leaf_t **root, user_t user);

int left_rotate(leaf_t **root, leaf_t *leaf);

int right_rotate(leaf_t **root, leaf_t *leaf);

void balancing_of_tree(leaf_t **root, leaf_t *leaf);

leaf_t** convert_list_to_tree(node_t **node, unsigned short flag);