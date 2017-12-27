#include <stdlib.h>
#include <pthread.h>
#include "util-ringbuffer.h"

#define DEFAULT_BUFFER_CAPACITY 1024

static int up_to_ceiling(int n)
{
    int res;
    for(res=2; res>0; res*=2)
        if(res >= n)
            break;
    return res;
}

static int index_format(int idx, int mask)
{
    return idx&mask;
}

// -------------------------srsw_ring_buffer_------------------------------
struct srsw_ring_buffer_ {
    volatile int read_idx;
    volatile int write_idx;

    void **buffer;
    int size;
    int mask;
} ;

void srsw_ring_buffer_destroy(struct srsw_ring_buffer_ *rb)
{
    if(rb) {
        // pthread_spin_destroy(&rb->lock);
        if(rb->buffer)
            free(rb->buffer);
        free(rb);
    }
}

struct srsw_ring_buffer_ *srsw_ring_buffer_create(int size)
{
    struct srsw_ring_buffer_ *rb = (struct srsw_ring_buffer_ *)calloc(1, sizeof(struct srsw_ring_buffer_));
    if(!rb) return NULL;

    // pthread_spin_init(&rb->lock, PTHREAD_PROCESS_PRIVATE);

    rb->size = up_to_ceiling(size);
    rb->mask = rb->size - 1;
    rb->read_idx = rb->write_idx = 0;
    rb->buffer = (void **)calloc(rb->size, sizeof(void *));
    if(!rb->buffer) {
        srsw_ring_buffer_destroy(rb);
        return NULL;
    }
    return rb;
}

struct srsw_ring_buffer_ *srsw_ring_buffer_create_default()
{
    return srsw_ring_buffer_create(DEFAULT_BUFFER_CAPACITY);
}

void *srsw_ring_buffer_pop(struct srsw_ring_buffer_ *rb)
{
    if(!rb || !rb->buffer)  return NULL;

    void *res = NULL;

    // pthread_spin_lock(&rb->lock);
    if(rb->read_idx != rb->write_idx) {
        res = rb->buffer[rb->read_idx];
        rb->read_idx = index_format(rb->read_idx+1, rb->mask);
    }
    // pthread_spin_unlock(&rb->lock);

    return res;
}

int srsw_ring_buffer_push(struct srsw_ring_buffer_ *rb, void *ptr)
{
    if(!rb || !rb->buffer)  return -1;

    int ret = -1;

    // pthread_spin_lock(&rb->lock);
    if(index_format(rb->write_idx+1, rb->mask) != rb->read_idx) {
        rb->buffer[rb->write_idx] = ptr;
        rb->write_idx = index_format(rb->write_idx+1, rb->mask);
        ret = 0;
    }
    // pthread_spin_unlock(&rb->lock);

    return ret;
}

void srsw_ring_buffer_clear(struct srsw_ring_buffer_ *rb, free_callback free_cb)
{
    if(!rb || !rb->buffer)   return;

    if(!free_cb)
        free_cb = free;

    while(rb->read_idx != rb->write_idx) {
        free_cb(srsw_ring_buffer_pop(rb));
    }
}

void srsw_ring_buffer_clear_destroy(struct srsw_ring_buffer_ *rb, free_callback free_cb)
{
    srsw_ring_buffer_clear(rb, free_cb);
    srsw_ring_buffer_destroy(rb);
}

#ifdef __linux__
// -------------------------mrmw_ring_buffer_------------------------------
struct mrmw_ring_buffer_ {
    volatile int read_idx;
    volatile int write_idx;
    pthread_spinlock_t lock;

    void **buffer;
    int size;
    int mask;
} ;

void mrmw_ring_buffer_destroy(struct mrmw_ring_buffer_ *rb)
{
    if(rb) {
        pthread_spin_destroy(&rb->lock);
        if(rb->buffer)
            free(rb->buffer);
        free(rb);
    }
}

struct mrmw_ring_buffer_ *mrmw_ring_buffer_create(int size)
{
    struct mrmw_ring_buffer_ *rb = (struct mrmw_ring_buffer_ *)calloc(1, sizeof(struct mrmw_ring_buffer_));
    if(!rb) return NULL;

    pthread_spin_init(&rb->lock, PTHREAD_PROCESS_PRIVATE);

    rb->size = up_to_ceiling(size);
    rb->mask = rb->size - 1;
    rb->read_idx = rb->write_idx = 0;
    rb->buffer = (void **)calloc(rb->size, sizeof(void *));
    if(!rb->buffer) {
        mrmw_ring_buffer_destroy(rb);
        return NULL;
    }
    return rb;
}

struct mrmw_ring_buffer_ *mrmw_ring_buffer_create_default()
{
    return mrmw_ring_buffer_create(DEFAULT_BUFFER_CAPACITY);
}

void *mrmw_ring_buffer_pop(struct mrmw_ring_buffer_ *rb)
{
    if(!rb || !rb->buffer)  return NULL;

    void *res = NULL;

    pthread_spin_lock(&rb->lock);
    if(rb->read_idx != rb->write_idx) {
        res = rb->buffer[rb->read_idx];
        rb->read_idx = index_format(rb->read_idx+1, rb->mask);
    }
    pthread_spin_unlock(&rb->lock);

    return res;
}

int mrmw_ring_buffer_push(struct mrmw_ring_buffer_ *rb, void *ptr)
{
    if(!rb || !rb->buffer)  return -1;

    int ret = -1;

    pthread_spin_lock(&rb->lock);
    if(index_format(rb->write_idx+1, rb->mask) != rb->read_idx) {
        rb->buffer[rb->write_idx] = ptr;

        rb->write_idx = index_format(rb->write_idx+1, rb->mask);
        ret = 0;
    }
    pthread_spin_unlock(&rb->lock);

    return ret;
}

void mrmw_ring_buffer_clear(struct mrmw_ring_buffer_ *rb, free_callback free_cb)
{
    if(!rb || !rb->buffer)   return;

    if(!free_cb)
        free_cb = free;

    while(rb->read_idx != rb->write_idx) {
        free_cb(mrmw_ring_buffer_pop(rb));
    }
}

void mrmw_ring_buffer_clear_destroy(struct mrmw_ring_buffer_ *rb, free_callback free_cb)
{
    mrmw_ring_buffer_clear(rb, free_cb);
    mrmw_ring_buffer_destroy(rb);
}

#endif /*__linux__*/
