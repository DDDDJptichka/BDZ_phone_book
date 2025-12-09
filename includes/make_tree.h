#pragma once

#include "structs.h"

int compare_strs(user_t user, leaf_t *leaf);

leaf_t* add_leaf(leaf_t **root, node_t* new_node);

int left_rotate(leaf_t **root, leaf_t *leaf);

int right_rotate(leaf_t **root, leaf_t *leaf);

void balancing_of_tree(leaf_t **root, leaf_t *leaf);

leaf_t** convert_list_to_tree(node_t **node, unsigned short flag);

leaf_t* find_min_leaf(leaf_t *leaf);

void switch_local_roots(leaf_t **root, leaf_t *local_root_1, leaf_t *local_root_2);

void balancing_tree_for_del(leaf_t **root, leaf_t *leaf);

void delete_leaf(leaf_t **root, leaf_t *leaf);

void clean_tree(leaf_t *leaf);

int print_tree(leaf_t **root, FILE *output);