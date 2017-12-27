#ifndef __UTIL_RING_BUFFER_H__
#define __UTIL_RING_BUFFER_H__
// #include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*free_callback)(void *free_ptr);

// create ringbuffer with size = 2^n
// if create size is 0, default replace with 1024
// if free_cb is NULL, default replace with free


/* srsw_ring_buffer_t is single read single write, 
 * non-lock push and pop, 
 * < single thread push, single thread pop >
 * concurrent access srsw_ring_buffer_t cause data races !
 */
typedef struct srsw_ring_buffer_ srsw_ring_buffer_t;
srsw_ring_buffer_t *srsw_ring_buffer_create(int size);
srsw_ring_buffer_t *srsw_ring_buffer_create_default();
void *srsw_ring_buffer_pop(srsw_ring_buffer_t *rb);
int srsw_ring_buffer_push(srsw_ring_buffer_t *rb, void *ptr);
void srsw_ring_buffer_clear(srsw_ring_buffer_t *rb, free_callback free_cb);
void srsw_ring_buffer_destroy(srsw_ring_buffer_t *rb);
void srsw_ring_buffer_clear_destroy(srsw_ring_buffer_t *rb, free_callback free_cb);


#ifdef __linux__
/* mrmw_ring_buffer_t is multi read multi write, 
 * pthread_spin_lock push and pop, 
 * < multi thread push, multi thread pop >
 * concurrent access mrmw_ring_buffer_t safe.
 */
typedef struct mrmw_ring_buffer_ mrmw_ring_buffer_t;
mrmw_ring_buffer_t *mrmw_ring_buffer_create(int size);
mrmw_ring_buffer_t *mrmw_ring_buffer_create_default();
void *mrmw_ring_buffer_pop(mrmw_ring_buffer_t *rb);
int mrmw_ring_buffer_push(mrmw_ring_buffer_t *rb, void *ptr);
void mrmw_ring_buffer_clear(mrmw_ring_buffer_t *rb, free_callback free_cb);
void mrmw_ring_buffer_destroy(mrmw_ring_buffer_t *rb);
void mrmw_ring_buffer_clear_destroy(mrmw_ring_buffer_t *rb, free_callback free_cb);
#endif /*__linux__*/

#ifdef __cplusplus
}
#endif


#endif // __UTIL_RING_BUFFER_H__