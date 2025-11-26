#pragma once

#define FIRST_NAME_MAX_SIZE 100
#define SECOND_NAME_MAX_SIZE 100
#define THIRD_NAME_MAX_SIZE 100
#define TELEPHONE_NUMBER_MAX_SIZE 30
#define ANOTHER_INFO_MAX_SIZE 500

typedef struct User{
    
    char first_name[FIRST_NAME_MAX_SIZE];
    char second_name[SECOND_NAME_MAX_SIZE];
    char third_name[THIRD_NAME_MAX_SIZE];//patronimic
    char telephone_number[TELEPHONE_NUMBER_MAX_SIZE];//int 
    char another_info[ANOTHER_INFO_MAX_SIZE];
    
} user_t;

typedef struct Node{

    user_t user;
    struct Node *left;
    struct Node *right;

} node_t;

typedef struct Leaf{

    user_t user;
    char color;
    struct Leaf *left;
    struct Leaf *right;
    struct Leaf *parent;
    struct Node **node;

} leaf_t;