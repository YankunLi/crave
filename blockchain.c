/*
 * Author: liyankun
 * Email: lioveni99@gmail.com
 */
#include <stdio.h>
#include <stdlib.h>

#include "blockchain.h"
#include "list.h"
#include "block.h"
#include "utils.h"

extern blockchain_t block_chain;

extern void add_block(blockchain_t *bc, block_t *block)
{
    if (block && bc) {
        list_add_tail(&block->b_list, &bc->b_blocks);
    }
}

static void add_transactions()
{}

extern void build_transaction(blockchain_t *bc, transaction_t *trans)
{
    if (bc && trans)
        list_add_tail(&trans->t_list,&bc->b_current_trans);
}

extern block_t * get_last_block(blockchain_t *bc)
{
    block_t * block = NULL;
    block = list_entry(bc->b_blocks.prev, block_t, b_list);
    return block;
}

extern block_t first_block;

static void __attribute__ ((constructor)) init_blockchain()
{
    add_block(&block_chain, &first_block);
}
