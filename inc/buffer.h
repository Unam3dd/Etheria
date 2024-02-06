#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 0x100
#endif

typedef struct buffer_t buffer_t;

struct buffer_t
{
    char            data[BUFFER_SIZE];

    union {
        const char  *str;
        char        *buf;
        void        *ptr;
        uint64_t    *u64;
        uint32_t    *u32;
        uint16_t    *u16;
        uint8_t     *u8;
        int64_t     *i64;
        int32_t     *i32;
        int16_t     *i16;
        int8_t      *i8;
    };

    union {
        size_t          length;
        size_t          size;
    };

    size_t          capacity;
};

#define BUFFER_INIT(NAME)\
    NAME.ptr = NAME.data

#define BUFFER_COPY(DST, SRC, SIZE) {\
    char *p = memcpy(DST.data, SRC, SIZE);\
    if (p) DST.size = ((unsigned long)(p+SIZE) - (unsigned long)DST.data);\
    }

#define BUFFER_SEARCH(DST, NEEDLE, SIZE) memmem(DST.data, NEEDLE, SIZE)

#define BUFFER_STRCPY(DST, STR, SIZE) strncpy(DST.data, STR, SIZE)

#define BUFFER_ZERO(BUF) memset(BUF.data, 0, sizeof(BUF.data))

#define BUFFER_CREATE(TYPE, NAME, SIZE) \
    struct buffer##NAME {               \
        TYPE    data[SIZE];             \
                                        \
        union {                         \
            const char  *str;           \
            char        *buf;           \
            void        *ptr;           \
            uint64_t    *u64;           \
            int64_t     *i64;           \
            uint32_t    *u32;           \
            int32_t     *i32;           \
            uint16_t    *u16;           \
            int16_t     *i16;           \
            uint8_t     *u8;            \
            int8_t      *i8;            \
        };                              \
                                        \
        union {                         \
            size_t      size;           \
            size_t      length;         \
        };                              \
                                        \
        size_t          capacity;       \
    } NAME = { { 0x0 },\
        .size = 0x0, .capacity = SIZE };\
    BUFFER_INIT(NAME); BUFFER_ZERO(NAME);

#endif
