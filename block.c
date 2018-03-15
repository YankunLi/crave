/*
 * Author: liyankun
 * Email: lioveni99@gmail.com
 */

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "list.h"
#include "block.h"
#include "utils.h"

block_t * new_block(const int index, const char *pre_hash, int proof, struct list_head transactions) {
    block_t * blk = (block_t *) malloc(sizeof(block_t));
    if (blk == NULL) {
        //malloc error
        return NULL;
    }

    blk->b_index = index;
    strcpy(blk->b_previous_hash, pre_hash);
    blk->b_transactions = transactions;
    blk->b_timestamp = get_current_time_s();
    blk->b_proof = proof;

    strcpy(blk->b_hash, hash_block(blk));

    return blk;
}

void delete_block(block_t * block) {
    transaction_t *trans_ptr = NULL;
    struct list_head *list = NULL;

    if (block != NULL) {
        free(block);
    }

    list = &block->b_transactions;
    list_for_each_entry(trans_ptr, list, t_list) {
        free(trans_ptr);
    }
}

char * hash_block(block_t *block) {

}
