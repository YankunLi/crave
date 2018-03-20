/*
 * Author: liyankun
 * Email: lioveni99@gmail.com
 */

#ifndef __BLOCK_H_
#define __BLOCK_H_

#include <unistd.h>
#include <inttypes.h>
#include "list.h"

#define FILESYSTEM_PAGESIZE getpagesize()

struct buffer {
    uint32_t b_total_size;
    uint32_t b_used_size;
    uint32_t b_avail_size;
    char * b_ptr;
};

typedef struct buffer buffer_t;

struct transaction {
    char data[256];
    struct list_head t_list;
};

struct transaction first_trans = {"sender:983kdikfffsdf\
                                   receiver:lksdlkf345645\
                                   signature:ldimlmvoser24545",
                                   LIST_SELF(first_trans.t_list)};

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

struct block first_block = {
    0,
    "12jikolcb23j48dhs9fmc8uqwnc87zxc",
    1521462098,
    LIST_SELF(first_block.b_transactions),
    "askfjlsdksf03094llkw6lt67l3kl5qw",
    0,
    LIST_SELF(first_block.b_list),
};

typedef struct block block_t;

buffer_t * allocate_buffer(buffer_t * buf);
void * free_buffer(buffer_t * buf);

extern block_t * new_block(const int index, const char *pre_hash, int proof, struct list_head transactions);
extern void delete_block(block_t * block);
extern char * hash_block(block_t * block);
extern void add_transaction(block_t *block, transaction_t * trans);
extern transaction_t * new_transaction(const char * data);

#endif
