/*
 * Author: liyankun
 * Email: lioveni99@gmail.com
 */

#ifndef __BLOCK_H_
#define __BLOCK_H_

#include "list.h"

struct transaction {
    char data[256];
    struct list_head t_list;
};

typedef struct transaction transaction_t;

struct block {
    int b_index;
    char b_previous_hash[128];
    long b_timestamp;
    struct list_head b_transactions;
    char b_hash[128];
    int b_proof;
    struct list_head b_list;
};

typedef struct block block_t;

block_t * new_block(const int index, const char *pre_hash, int proof, struct list_head transactions);
void delete_block(block_t * block);
char * hash_block(block_t * block);
void add_transaction(transaction_t * trans);
transaction_t * new_transaction(char * data);

#endif
