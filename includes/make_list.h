#pragma once

#include "structs.h"

node_t** create_list(const char* input, int* row_num);

node_t* add_to_list(node_t** root, user_t new_user);

void del_from_list(node_t** list_root, node_t* del_node);

void clean_slist(snode_t* snode);