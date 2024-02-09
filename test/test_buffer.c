#include "bytebreacher.h"
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/logging.h>
#include <mmintrin.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "buffer.h"


Test(test_buffer_basic, test_buffer_basic1)
{
    buffer_t    buf;

    cr_log_info("Check if data buffer is correct value of BUFFER_SIZE(%d)...", BUFFER_SIZE);
    
    cr_assert_eq(sizeof(buf.data), BUFFER_SIZE);

    cr_log_info("Check if data is at offset 0...");
    cr_assert_eq(offsetof(typeof(buf), data), 0);
}

Test(test_buffer_basic, test_buffer_basic2)
{
    buffer_t    buf;

    BUFFER_STACK_INIT(buf);

    memset(buf.data, 0, sizeof(buf.data));

    BUFFER_COPY(buf, "hello", 5);

    cr_assert_eq(strcmp(buf.data, "hello"), 0);
    cr_assert_eq(buf.size, 5);
}

Test(test_buffer_basic, test_buffer_basic3)
{
    buffer_t    buf;

    BUFFER_STACK_INIT(buf);

    cr_assert_eq(buf.capacity, BUFFER_SIZE);
}

Test(test_buffer_basic, test_buffer_basic4)
{
    buffer_t    bufa;
    buffer_t    bufb;

    BUFFER_STACK_INIT(bufa);
    BUFFER_STACK_INIT(bufb);

    memset(BUFFER_GET(bufa), 'a', sizeof(bufa.data)-1);
    memset(BUFFER_GET(bufb), 'b', sizeof(bufb.data)-1);

    BUFFER_COPY(bufb, BUFFER_GET(bufa), bufa.capacity);

    cr_assert_eq(strcmp(BUFFER_GET(bufa), BUFFER_GET(bufb)), 0);
}

Test(test_buffer_basic, test_buffer_basic5)
{
    buffer_t    buf;
    buffer_t    buf2;

    BUFFER_STACK_INIT(buf);
    BUFFER_STACK_INIT(buf2);

    memset(BUFFER_GET(buf), 'a', buf.capacity);

    cr_assert(memcmp(buf.data, buf2.data, BUFFER_SIZE) != 0);
    
    BUFFER_ZERO(buf);

    cr_assert(!memcmp(buf.data, buf2.data, BUFFER_SIZE));
}

Test(test_buffer_basic, test_buffer_basic6)
{
    buf_t   buf;

    BUFFER_STACK_INIT(buf);

    memset(buf.data, 'a', buf.capacity-1);

    cr_assert(strlen(buf.data) == buf.capacity-1);
}


Test(test_buffer_template_basic, test_buffer_template_basic1)
{
    BUFFER_CREATE(int, int_buffer, 0x4);

    cr_assert(sizeof(int_buffer.data) == 1 << 4);
}

Test(test_buffer_template_basic, test_buffer_template_basic2)
{
    BUFFER_CREATE(unsigned char, bufa, (BUFFER_SIZE >> 1));

    cr_assert(sizeof(bufa.data) == (BUFFER_SIZE >> 1));
    cr_assert(sizeof(bufa.data)*8 == ((BUFFER_SIZE >> 1) << 3));
}

Test(test_buffer_template_basic, test_buffer_template_basic3)
{
    BUFFER_CREATE(long, buf_long, (BUFFER_SIZE >> 4));

    cr_assert(sizeof(buf_long.data) == BUFFER_SIZE>>1);
}

Test(test_buffer_template_basic, test_buffer_template_basic4)
{
    BUFFER_CREATE(uint8_t, buf, 0x10);

    BUFFER_ZERO(buf);

    cr_assert(buf.capacity == 1 << 4);
}

Test(test_buffer_template_basic, test_buffer_template_basic5)
{
    BUFFER_DEF_STACK(uint8_t, bufio, 0x100);

    BUFFER_STACK(bufio, toto);
    BUFFER_STACK(bufio, tata);
    BUFFER_STACK(bufio, titi);

    BUFFER_STACK_INIT(toto);
    BUFFER_STACK_INIT(tata);
    BUFFER_STACK_INIT(titi);

    BUFFER_STRCPY(toto, "hello", 5);

    BUFFER_STRCPY(titi, BUFFER_GET(toto), strlen(BUFFER_GET(toto)));

    cr_assert_eq(strcmp(BUFFER_GET(toto), "hello"), 0);
    cr_assert_eq(strcmp(BUFFER_GET(titi), "hello"), 0);
}

Test(test_buffer_template_basic, test_buffer_heap_test1)
{
    buffer_heap_t   buf;

    BUFFER_HEAP_INIT(buf, 0x100);
    
    cr_assert(BUFFER_GET(buf) != NULL);

    BUFFER_FREE(buf);

    cr_assert(BUFFER_GET(buf) == NULL);
    cr_assert(BUFFER_GET_CAPACITY(buf) != 0x100);
    cr_assert(BUFFER_GET_MODE(buf) == IS_HEAP);
}

Test(test_buffer_template_basic, test_buffer_heap_test2)
{
    buffer_heap_t   buf;
    void            *save = NULL;

    BUFFER_HEAP_INIT(buf, 0x100);
    save = BUFFER_GET(buf);
    cr_assert(buf.capacity == 0x100);
    cr_assert(buf.size == 0);
    cr_assert(buf.data != NULL);
    cr_assert(buf.ptr != NULL);
    BUFFER_FREE(buf);

    cr_assert(buf.data == NULL);
    
    BUFFER_HEAP_INIT(buf, 0x200);
    cr_assert(buf.data != save);
    cr_assert(buf.capacity == 0x200);
    cr_assert(buf.ptr != NULL);
    cr_assert(buf.data != NULL);
    cr_assert(buf.data == buf.ptr);
    BUFFER_FREE(buf);
    
    cr_assert(buf.data == NULL);
}

Test(test_buffer_template_basic, test_buffer_heap_test3)
{
    buffer_heap_t   bufs[0x100];
    uint32_t        i = 0;

    memset(bufs, 0, sizeof(bufs));

    for (i = 0; i < (uint32_t)sizeof(bufs)/sizeof(buffer_heap_t); i++) {
        BUFFER_HEAP_INIT(bufs[i], 0x100);
        cr_assert(bufs[i].data != NULL);
        cr_assert(bufs[i].data == bufs[i].ptr);
        cr_assert(bufs[i].capacity == 0x100);
        cr_assert(!bufs[i].length);
        cr_assert(BUFFER_IS_HEAP(bufs[i]));
    }
    
    i = 0;

    for (i = 0; i < (uint32_t)sizeof(bufs)/sizeof(buffer_heap_t); i++) {
        BUFFER_FREE(bufs[i]);
        cr_assert(bufs[i].data == NULL);
        cr_assert(!bufs[i].length);
        cr_assert(!bufs[i].capacity);
    }
}
