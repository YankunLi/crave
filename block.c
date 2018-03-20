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
#include "sha256.h"

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

buffer_t * allocate_buffer(buffer_t * buf) {
    void * temp_ptr;
    if (buf->b_total_size == 0) {
        temp_ptr = (char *) malloc(FILESYSTEM_PAGESIZE);
    } else {
        temp_ptr = realloc(buf->b_ptr, FILESYSTEM_PAGESIZE);
    }

    if (temp_ptr) {
        buf->b_ptr = (char *) temp_ptr;
        buf->b_total_size += FILESYSTEM_PAGESIZE;
    }

    return temp_ptr;
}

void * free_buffer(buffer_t * buf) {
    if (buf->b_total_size != 0) {
        free(buf->b_ptr);
        buf->b_ptr = NULL;
        buf->b_total_size = 0;
        buf->b_used_size = 0;
    }
}

static char * encode_transaction(const transaction_t *transaction)
{
    char * trans_buf;
    trans_buf = (char *) malloc(FILESYSTEM_PAGESIZE);
}

static int memory_copy(buffer_t *buf, char *src, uint32_t len)
{
    if (buf->b_avail_size < len)
        if (!allocate_buffer(buf)) {
            return -1;
        }

    memcpy(buf->b_ptr, src, len);
    buf->b_avail_size -= len;
    buf->b_used_size += len;

    return 0;
}

static void encode_block(buffer_t *buf, const block_t *block)
{
    transaction_t * trans_ptr = NULL;
    struct list_head * list = NULL;

    //encode chain head
    memory_copy(buf, (char *) &block->b_index, sizeof(int));
    memory_copy(buf, (char *) &block->b_previous_hash, 128);
    memory_copy(buf, (char *) &block->b_timestamp, sizeof(long));
    memory_copy(buf, (char *) &block->b_proof, sizeof(int));
    list = (struct list_head *) &block->b_transactions;

    //encode chain data

    list_for_each_entry(trans_ptr, list, t_list)
        memory_copy(buf, (char *) trans_ptr->data, 256);
}

char * hash_block(block_t *block)
{
    buffer_t buf;
    char hash_code[32];
    encode_block(&buf, block);
    mbedtls_sha256(buf.b_ptr, strlen(buf.b_ptr), hash_code, 0);
    memcpy(block->b_hash, hash_code, 32);
    free_buffer(&buf);
}

void add_transaction(block_t *block, transaction_t *trans)
{
    list_add_tail(&trans->t_list, &block->b_transactions);
}

transaction_t * new_transaction(const char * trans)
{
    transaction_t * trans_ptr = (transaction_t *) malloc(sizeof(transaction_t));
    if (trans_ptr) {
        memcpy(trans_ptr, trans, strlen(trans));
    }
    return trans_ptr;
}

extern transaction_t first_trans;
extern block_t first_block;

static void __attribute__ ((constructor)) init_block()
{
    add_transaction(&first_block, &first_trans);
}
