#pragma once

#include "structs.h"

int compare_strs_for_search(const char* keyword, leaf_t* current_leaf);

int search_user(leaf_t* root, snode_t* last_node, const char *keyword, unsigned short int flag);

void clean_num(unsigned short int zero);