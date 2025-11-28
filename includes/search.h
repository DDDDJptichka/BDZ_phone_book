#pragma once

#include "structs.h"

int compare_strs_for_search(const char* keyword, leaf_t* current_leaf);

int search_user(leaf_t* root, const char *keyword, unsigned short int flag);