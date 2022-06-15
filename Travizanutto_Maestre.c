/* ----------------------------------------------
Cainan Travizanutto && Gabriel Maestre - 2022;
#ifndef data_structs_assignment_done
#define project_1_data_structures_lab
#endif
------------------ QUICK INFO -------------------
This is not meant to be used in production, only for study purpose
All static functions are meant to be used internally, thus the _prefix format
If user calls function with wrong parameters the function will either return and don't display any errors
    or behave improperly
Functions 
{
create list: takes a pointer to list pointer and data to be inserted
split: takes two pointers to list pointers, the original list and the one to be splited to, and the data of the new first node of the latter list
insert: takes a list pointer, a bool, witch if true inserts in order else after a specific node (last argument), and data to be inserted
remove: takes a list pointer and a bool, which if true removes all nodes, else a specific one
print: it prints ¯\_(ツ)_/¯
}
-------------------- SUMMARY --------------------
64  -> Structs
84  -> Prototypes of Functions
119 -> Implementation of Simple Linked List
    119-127 Create a Simply List
    129-149 Split Simply List
    151-196 Insert Simply List
    198-240 Remove Simply List
    242-250 Print Simply List
252 -> Implementation of Head Simply Linked List
    252-270 Create a Head Simply List
    272-295 Split Head Simply List
    297-309 Insert Head Simply List
    311-325 Remove Head Simply List
    327-332 Print Head Simply List
334 -> Implementation of Circular Linked List
    334-343 Create a Circular List
    345-373 Split Circular List
    375-423 Insert Circular List
    425-473 Remove Circular List
    475-485 Print Circular List
487 -> Implementation of Doubly Linked List
    487-496 Create a Doubly List
    498-519 Split Doubly List
    521-571 Insert Doubly List
    573-609 Remove Doubly List
    611-619 Print Doubly List
624 -> License
*/
#ifndef _PROJECT1_H
#define _PROJECT1_H

#ifndef _BOOL
typedef enum{ false, true } bool;
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// Holds a data data of int type and a struct pointer to the next element in the list
typedef struct simple_node {
        int data;
        struct simple_node *next;
} node;

// Holds list size and a struct pointer to first element of the list
typedef struct head_node {
        int size;
        struct simple_node *first;
} h_node;

// Holds a data data of int type and two struct pointers, one to the next element in the list and one to the prior
typedef struct doubly_node {
        int data;
        struct doubly_node *next;
        struct doubly_node *prev;
} d_node;

//------------------------------ SIMPLE LINKED LIST ------------------------------//

void node_create_list(int data, node** list);
void node_split_list(node** list_split_from, node** list_split_to, int node_pos_data);
void node_insert(node *list, int data, bool in_order, ...);
void node_remove(node **list, bool delete_all, ...);
void node_print_list(node *list);


//------------------------- SIMPLE LINKED LIST WITH HEAD -------------------------//

void h_node_create_list(int data, h_node **list);
void h_node_split_list(h_node** head_split_from, h_node** head_split_to, int node_pos_data);
void h_node_insert(h_node *head, int data, bool in_order, ...);
void h_node_remove(h_node **head, bool delete_all, ...);
void h_node_print_list(h_node *head);


//----------------------------- CIRCULAR LINKED LIST -----------------------------//

void c_node_create_list(node **list, int data);
void c_node_split_list(node** list_split_from, node** list_split_to, int node_pos_data);
void c_node_insert(node *list, int data, bool in_order, ...);
void c_node_remove(node **list, bool delete_all, ...);
void c_node_print_list(node* list);


//----------------------------- DOUBLY LINKED LIST --------------------------------//

void d_node_create_list(int data, d_node** list);
void d_node_split_list(d_node** list_split_from, d_node** list_split_to, int node_pos_data);
void d_node_insert(d_node *list, int data, bool in_order, ...);
void d_node_remove(d_node **list, bool delete_all, ...);
void d_node_print_list(d_node *list);

//------------------------------ IMPLEMENTATION ------------------------------//

void node_create_list(int data, node** list)
{
    if (*list != NULL) return;
    node* tmp = (node*) malloc(sizeof(node));
    if (tmp == NULL) exit(1);
    tmp->data = data;
    tmp->next = NULL;
    *list = tmp;
}

void node_split_list(node** list_split_from, node** list_split_to, int node_pos_data)
{
    if (*list_split_to != NULL) return;
    if (*list_split_from == NULL) return;
    node* tmp = *list_split_from;
    if (tmp->data == node_pos_data) { // case pos is the first element
        *list_split_to = *list_split_from;
        *list_split_from = NULL;
        return;
    }
    node *tmp_return = NULL;
    do {
        if (tmp->next == NULL) return;
        if (tmp->next->data == node_pos_data) {
            tmp_return = tmp->next;
            tmp->next = NULL;
        }
        tmp = tmp->next;
    } while (tmp != NULL);
    *list_split_to = tmp_return;
}

static void _node_insert_order(node* list, int data)
{
    node* tmp = (node*) malloc(sizeof(node));
    if (tmp == NULL) exit(1);

    while (list->data <= data && list->next != NULL)
        list = list->next;

    if (list->data >= data) {
        tmp->data = list->data;
        tmp->next = list->next;
        list->data = data;
        list->next = tmp;
        return;
    }
    tmp->data = data;
    tmp->next = list->next;
    list->next = tmp;
}

static void _node_insert_pos(node* list, int data, int node_pos_data)
{
    while (list->data != node_pos_data) {
        if (list->next == NULL) return;
        list = list->next;
    }
    node* tmp = (node*) malloc(sizeof(node));
    if (tmp == NULL) exit(1);
    tmp->data = data;
    tmp->next = list->next;
    list->next = tmp;
}

void node_insert(node* list, int data, bool in_order, ...)
{
    if (list == NULL) return;
    if (in_order) {
        _node_insert_order(list, data);
        return;
    }
    va_list arg;
    va_start(arg, in_order);
    int node_pos_data = va_arg(arg, int);
    _node_insert_pos(list, data, node_pos_data);
    va_end(arg);
}

static void _node_remove_all(node* list)
{
    if (list == NULL) return;

    _node_remove_all(list->next);
    list->next = NULL;
    free(list);
}

static void _node_remove_pos(node** list, int node_pos_data) 
{
    node* tmp = *list;
    if (tmp->data == node_pos_data) { // case the node to remove its the first on list
            *list = tmp->next;
            free(tmp);
            return;
    }

    while (tmp->next != NULL) {
        if (tmp->next->data == node_pos_data) {
            node* tmp_remove = tmp->next;
            tmp->next = tmp->next->next;
            free(tmp_remove);
            return;
        }
        tmp = tmp->next;
    } 
}

void node_remove(node** list, bool delete_all, ...)
{
    if (*list == NULL) return;
    if (delete_all) {
        _node_remove_all(*list);
        *list = NULL;
        return;
    }
    va_list arg;
    va_start(arg, delete_all);
    int node_pos_data = va_arg(arg, int);
    _node_remove_pos(list, node_pos_data);
    va_end(arg);
}

void node_print_list(node* list)
{
    if (list == NULL) return;
    while (list != NULL)
    {
        printf("%d\n", list->data);
        list = list->next;
    }
}

static int _h_node_list_size(h_node* head)
{
    int i = 0;
    node* list = head->first;
    while (list != NULL) {
        i++;
        list = list->next;
    }
    return i;
}

void h_node_create_list(int data, h_node** list) 
{
    if (*list != NULL) return;
    h_node* tmp = (h_node*) malloc(sizeof(h_node));
    if (tmp == NULL) exit(1);
    *list = tmp;
    node_create_list(data, &(tmp->first));
}

void h_node_split_list(h_node** head_split_from, h_node** head_split_to, int node_pos_data)
{
    if (*head_split_to != NULL) return;
    if (*head_split_from == NULL) return;
    
    node* tmp = (*head_split_from)->first;
    
    if(tmp->data == node_pos_data) {
        *head_split_to = *head_split_from;
        *head_split_from = NULL;
        return;
    }
    node* tmp_return = NULL;
    do {
        if (tmp->next == NULL) return;
        if (tmp->next->data == node_pos_data) {
            tmp_return = tmp->next;
            tmp->next = NULL;
        }
        tmp = tmp->next;
    } while (tmp != NULL);
    *head_split_to = (h_node*)malloc(sizeof(h_node));
    (*head_split_to)->first = tmp_return;
}

void h_node_insert(h_node* head, int data, bool in_order, ...)
{
    if (head == NULL) return;
    if (in_order) {
        _node_insert_order(head->first, data);
        return;
    }
    va_list arg;
    va_start(arg, in_order);
    int node_pos_data = va_arg(arg, int);
    _node_insert_pos(head->first, data, node_pos_data);
    va_end(arg);
}

void h_node_remove(h_node** head, bool delete_all, ...)
{
    if(*head == NULL) return;
    if (delete_all) {
        _node_remove_all((*head)->first);
        free(*head);
        *head = NULL;
        return;
    }
    va_list arg;
    va_start(arg, delete_all);
    int node_pos_data = va_arg(arg, int);
    _node_remove_pos(&(*head)->first, node_pos_data);
    va_end(arg);
}

void h_node_print_list(h_node* head)
{
    if (head == NULL) return;
    node_print_list(head->first);
    printf("List total size: %i\n", _h_node_list_size(head));
}

void c_node_create_list(node **list, int data)
{
    if (*list != NULL) return;
    node* tmp = (node*) malloc(sizeof(node));
    if (tmp == NULL) exit(1);
    
    tmp->data = data;
    *list = tmp;
    tmp->next = *list;
}

void c_node_split_list(node** list_split_from, node** list_split_to, int node_pos_data)
{
    node* tmp_list_from = *list_split_from;

    if (*list_split_to != NULL) return;
    if (*list_split_from == NULL) return;
    node* tmp = *list_split_from;
    if (tmp->data == node_pos_data) { // case pos is the first element
        *list_split_to = *list_split_from;
        *list_split_from = NULL;
        return;
    }
    node *tmp_return = NULL;
    do {
        if (tmp->next == tmp_list_from) return;
        if (tmp->next->data == node_pos_data) {
            tmp_return = tmp->next;
            tmp->next = tmp_list_from;
            break;
        }
        tmp = tmp->next;
    } while (tmp != NULL);
    tmp = tmp_return;
    while (tmp_return->next != tmp_list_from)
        tmp_return = tmp_return->next;
    
    tmp_return->next = tmp;
    *list_split_to = tmp;
}

static void _c_node_insert_order(node* list, int data)
{
    node* tmp = (node*) malloc(sizeof(node));
    if (tmp == NULL) exit(1);
    node* tmp2 = list;

    while (list->data <= data && list->next != tmp2)
        list = list->next;

    if (list->data >= data) {
        tmp->data = list->data;
        tmp->next = list->next;
        list->data = data;
        list->next = tmp;
        return;
    }
    tmp->data = data;
    tmp->next = list->next;
    list->next = tmp;
}

static void _c_node_insert_pos(node *list, int data, int node_pos_data)
{
    node *tmp2 = list;
    while (list->data != node_pos_data) {
        if (list->next == tmp2) return;
        list = list->next;
    }
    node* tmp = (node*) malloc(sizeof(node));
    if (tmp == NULL) exit(1);
    
    tmp->data = data;
    tmp->next = list->next;
    list->next = tmp;
}

void c_node_insert(node *list, int data, bool in_order, ...)
{
    if (list == NULL) return;
    if (in_order) {
        _c_node_insert_order(list, data);
        return;
    }
    va_list arg;
    va_start(arg, in_order);
    int node_pos_data = va_arg(arg, int);
    _c_node_insert_pos(list, data, node_pos_data);
    va_end(arg);
}

static void _c_node_remove_all(node* list)
{
    node *tmp = list;
    node *tmp_free = NULL;
    do{
        tmp_free = list;
        list = list->next;
        free(tmp_free);
    }while (list != tmp);
}

static void _c_node_remove_pos(node** list, int node_pos_data)
{
    node* tmp = *list;
    if (tmp->data == node_pos_data) { // case the node to remove its the first on list
            while(tmp->next != *list)
                tmp = tmp->next;
            tmp->next = (*list)->next;
            free(*list);
            *list = tmp->next;
            return;
    }

    while (tmp->next != *list) {
        if (tmp->next->data == node_pos_data) {
            node* tmp_remove = tmp->next;
            tmp->next = tmp->next->next;
            free(tmp_remove);
            return;
        }
        tmp = tmp->next;
    } 
}

void c_node_remove(node** list, bool delete_all, ...)
{
    if(*list == NULL) return;
    if (delete_all) {
        _c_node_remove_all(*list);
        //free(*list); this line is'n necessary in this function because the "free all" isn't recursive. 
        *list = NULL;
        return;
    }
    va_list arg;
    va_start(arg, delete_all);
    int node_pos_data = va_arg(arg, int);
    _c_node_remove_pos(&(*list), node_pos_data);
    va_end(arg);
}

void c_node_print_list(node* list)
{
    if (list == NULL) return;
    
    node *tmp = list;
    do
    {
        printf("%d\n", tmp->data);
        tmp = tmp->next;
    } while (tmp != list);
}

void d_node_create_list(int data, d_node** list)
{
    if (*list != NULL) return;
    d_node* tmp = (d_node*) malloc(sizeof(d_node));
    if (tmp == NULL) exit(1);
    tmp->data = data;
    tmp->next = NULL;
    tmp->prev = NULL;
    *list = tmp;
}

void d_node_split_list(d_node** list_split_from, d_node** list_split_to, int node_pos_data)
{
    if (*list_split_to != NULL) return;
    if (*list_split_from == NULL) return;
    d_node* tmp = *list_split_from;
    if (tmp->data == node_pos_data) { // case pos is the first element
        *list_split_to = *list_split_from;
        *list_split_from = NULL;
        return;
    }
    d_node *tmp_return = NULL;
    do {
        if (tmp->next == NULL) return;
        if (tmp->next->data == node_pos_data) {
            tmp_return = tmp->next;
            tmp->next = NULL;
        }
        tmp = tmp->next;
    } while (tmp != NULL);
    *list_split_to = tmp_return;
    (*list_split_to)->prev = NULL;
}

static void _d_node_insert_order(d_node* list, int data)
{
    d_node* tmp = (d_node*) malloc(sizeof(d_node));
    if (tmp == NULL) exit(1);

    while (list->data <= data && list->next != NULL)
        list = list->next;

    if (list->data >= data) {
        tmp->data = list->data;
        tmp->next = list->next;
        tmp->prev = list;
        list->data = data;
        list->next = tmp;
        return;
    }
    tmp->data = data;
    tmp->next = list->next;
    tmp->prev = list;
    list->next = tmp;
}

static void _d_node_insert_pos(d_node* list, int data, int node_pos_data)
{
    while (list->data != node_pos_data) {
        if (list->next == NULL) return;
        list = list->next;
    }
    d_node* tmp = (d_node*) malloc(sizeof(d_node));
    if (tmp == NULL) exit(1);
    tmp->data = data;
    tmp->next = list->next;
    tmp->prev = list;
    list->next = tmp;
    if(tmp->next != NULL) 
        tmp->next->prev = tmp;
}

void d_node_insert(d_node *list, int data, bool in_order, ...)
{
    if (list == NULL) return;
    if (in_order) {
        _d_node_insert_order(list, data);
        return;
    }
    va_list arg;
    va_start(arg, in_order);
    int node_pos_data = va_arg(arg, int);
    _d_node_insert_pos(list, data, node_pos_data);
    va_end(arg);
}

static void _d_node_remove_pos(d_node** list, int node_pos_data)
{
    d_node* tmp = *list;
    if (tmp->data == node_pos_data) { // case the node to remove its the first on list
            *list = tmp->next;
            (*list)->prev = NULL;
            free(tmp);
            return;
    }

    while (tmp->next != NULL) {
        if (tmp->next->data == node_pos_data) {
            d_node* tmp_remove = tmp->next;
            tmp->next = tmp->next->next;
            if (tmp->next != NULL)
                tmp->next->prev = tmp;
            free(tmp_remove);
            return;
        }
        tmp = tmp->next;
    } 
}

void d_node_remove(d_node **list, bool delete_all, ...)
{
    if(*list == NULL) return;
    if (delete_all) {
        _node_remove_all((node*) *list);
        *list = NULL;
        return;
    }
    va_list arg;
    va_start(arg, delete_all);
    int node_pos_data = va_arg(arg, int);
    _d_node_remove_pos(list, node_pos_data);
    va_end(arg);
}

void d_node_print_list(d_node *list)
{
    if (list == NULL) return;
    while (list != NULL)
    {
        printf("%d\n", list->data);
        list = list->next;
    }
}

#endif // _PROJECT1_H

/*
---------------------------- PUBLIC DOMAIN ----------------------------
This is free and unencumbered software released into the public domain.
-----------------------------------------------------------------------
Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.
In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/
