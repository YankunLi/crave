/*
 * Author: liyankun
 * Email: lioveni99@gmail.com
 */

#ifndef __BLOCK_CHAIN_H_
#define __BLOCK_CHAIN_H_

#include "block.h"
#include "utils.h"
#include "list.h"

struct blockchain {
    struct list_head b_blocks;
    struct list_head b_current_trans;
    //struct node TODO
};

struct blockchain block_chain = {
    LIST_SELF(block_chain.b_blocks),
    LIST_SELF(block_chain.b_current_trans)
};

typedef struct blockchain blockchain_t;

extern void add_block(blockchain_t * bc, block_t *block);
extern void build_transaction(blockchain_t *bc, transaction_t *trans);
extern block_t * get_last_block(blockchain_t *bc);

#endif
