#include "util-time.h"
#include "util-debug.h"
#include "util-system.h"
#include "util-bs.h"
#include "util-ringbuffer.h"
#include <iostream>
#include <stdint.h>

using namespace std;

#define RING_BUFFER_TEST_NUM 100
void ring_buffer_free_element(void *ptr)
{
    if(!ptr)
        return;
    int *elem = (int *)ptr;
    printf("free [=%8d]\n", *elem);
    delete elem;
}

void *pop_task(void *argu)
{
    srsw_ring_buffer_t *rb = (srsw_ring_buffer_t *)argu;
    while(1) {
        int *res = (int *)srsw_ring_buffer_pop(rb);
        if(!res) continue;
        printf("pop  [-%8d]\n", *res);
        int c = *res;
        ring_buffer_free_element(res);
        if(c > RING_BUFFER_TEST_NUM)
            break;
    }
    return NULL;
}

void *push_task(void *argu)
{
    srsw_ring_buffer_t *rb = (srsw_ring_buffer_t *)argu;
    for (int i = 0; i < RING_BUFFER_TEST_NUM+5; ++i) {
        int *elem = new int;
        *elem = i;
        while(srsw_ring_buffer_push(rb, elem))
            ;
        printf("push [+%8d]\n", *elem);
        // else {
        //     printf("ignr [=%8d]\n", *elem);
        //     ring_buffer_free_element(elem);
        // }
    }
    return NULL;
}

int main()
{
    cout << "----------------------util-time.h----------------------" << endl;
    string str("");
    cout << "time_2_str(str, t=0) " << utils::Time::time_2_str(str).c_str() << endl;
    cout << "time_2_str(t=0)      " << utils::Time::time_2_str().c_str() << endl;
    cout << "gettimeofday_s()     " << utils::Time::gettimeofday_s() << endl;
    cout << "gettimeofday_ms()    " << utils::Time::gettimeofday_ms() << endl;
    cout << "gettimeofday_us()    " << utils::Time::gettimeofday_us() << endl;

    cout << "----------------------util-debug.h----------------------" << endl;
    DEBUG_PRINT("hell%c %s %d\n", 'o', "world", 2323223);
    ERROR_PRINT("this is %d test %s\n", 9999, "ERROR_PRINT");

    cout << "----------------------util-basicsearch.h----------------------" << endl;
    uint8_t bs_arr[] = {0x24, 0x9e, 0xab, 0xa4, 0x60, 0x6b, 0x8c, 0xec, 0x4b, 0x40, 0x34, 0x01, 0x08, 0x00, 0x45, 0x00, 0x00, 0x3b, 0x16, 0x40, 0x00, 0x00, 0x80, 0x11, 0x00, 0x00, 0xc0, 0xa8, 0x0a, 0x68, 0xc0, 0xa8, 0x00, 0xc8, 0xd8, 0x00, 0x00, 0x35, 0x00, 0x27, 0x8c, 0xb9, 0x9a, 0x2c, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x77, 0x77, 0x77, 0x05, 0x69, 0x66, 0x65, 0x6e, 0x67, 0x03, 0x63, 0x6f, 0x6d, 0x00, 0x00, 0x01, 0x00, 0x01}; 
    printf("BasicSearch base :%p\n", bs_arr);

    uint8_t bs_needle_1[] = {0x60, 0x6b, 0x8c, 0xec, 0x4b};
    uint8_t *res1 = BasicSearch(bs_arr, sizeof(bs_arr)/sizeof(bs_arr[0]), 
                    bs_needle_1, sizeof(bs_needle_1)/sizeof(bs_needle_1[0]));
    if(res1)
        printf("BasicSearch result_1 is %p, offset:%d\n", res1, (int)(res1-bs_arr));
    else
        printf("BasicSearch result_1 is %p\n", res1);

    uint8_t bs_needle_2[] = {0x60, 0x6b, 0x8c, 0xec, 0x4c};
    uint8_t *res2 = BasicSearch(bs_arr, sizeof(bs_arr)/sizeof(bs_arr[0]), 
                    bs_needle_2, sizeof(bs_needle_2)/sizeof(bs_needle_2[0]));
    if(res2)
        printf("BasicSearch result_2 is %p, offset:%d\n", res2, (int)(res2-bs_arr));
    else
        printf("BasicSearch result_2 is %p\n", res2);

    cout << "----------------------util-ringbuffer.h----------------------" << endl;
    pthread_t pid_push, pid_pop;
    srsw_ring_buffer_t *rb = srsw_ring_buffer_create(10);
    pthread_create(&pid_pop,  NULL, pop_task,  rb);
    pthread_create(&pid_push, NULL, push_task, rb);
    pthread_join(pid_pop, NULL);
    pthread_join(pid_push, NULL);
    srsw_ring_buffer_clear_destroy(rb, ring_buffer_free_element);

    return 0;
}
