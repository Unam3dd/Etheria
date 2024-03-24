/*! @file buffer.h
 *  @brief Modern buffer API used in bytebreacher
 *  @version 0.0.1 
 *  @date 07/02/2024 13:23:47
 *  @author Unam3dd (sam0verfl0w)
 *  @copyright Copyright (C) 2024 Sam0verfl0w
 */
 
#ifndef BUFFER_H
#define BUFFER_H

/*
 * @note Includes required by buffer.h
 */
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

/*
 * @def BUFFER_SIZE 0x100
 * @note if BUFFER_SIZE is not defined the value is 0x100
 */
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 0x100
#endif

// @typedef struct buffer_t buffer_t
typedef struct buffer_t buffer_t;

// @typedef struct buffer_heap_t buffer_heap_t;
typedef struct buffer_heap_t buffer_heap_t;

// @typedef struct buffer_t buf_t;
typedef struct buffer_t buf_t;

// @typedef enum buffer_mode_t buffer_mode_t;

typedef enum buffer_mode_t
{
    IS_STACK = 0,
    IS_HEAP
} buffer_mode_t;

// @typedef const char *    string_t;
typedef const char *    string_t;

/*
 * @struct buffer_t.
 */
struct buffer_t {
    // @var char    data[BUFFER_SIZE]
    char            data[BUFFER_SIZE];

    // @union anonymous union for diferent types of data variable.
    union {
        string_t    str;
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

    // @union two syntax for obtaining the size of data written to the "data" buffer.
    union {
        // @var         length get length of data written to the "data" buffer.
        size_t          length;
        // @var         same as above but is named size.
        size_t          size;
    };

    // @var capacity
    size_t          capacity;
    // @var mode of the buffer if is in the STACK or the HEAP
    buffer_mode_t   mode;
};

struct buffer_heap_t {
        void            *data;              \
        union {                             \
            string_t     str;               \
            char        *buf;               \
            void        *ptr;               \
            uint64_t    *u64;               \
            int64_t     *i64;               \
            uint32_t    *u32;               \
            int32_t     *i32;               \
            uint16_t    *u16;               \
            int16_t     *i16;               \
            uint8_t     *u8;                \
            int8_t      *i8;                \
        };                                  \
        union {                             \
            size_t size;                    \
            size_t length;                  \
        };                                  \
        size_t          capacity;           \
        buffer_mode_t   mode;               \
};

/*
 * @def BUFFER_STACK_INIT(NAME)
 * @brief point union to the data buffer address.
 * @note NAME is name for the buffer.
 */
#define BUFFER_STACK_INIT(NAME)                             \
    memset(&NAME, 0, sizeof(NAME));                         \
    NAME.ptr = NAME.data;                                   \
    NAME.capacity = sizeof(NAME.data)/sizeof(NAME.data[0]); \
    NAME.mode = IS_STACK

/*
 * @def BUFFER_HEAP_INIT(NAME)
 * @brief point union to the data buffer address.
 * @note NAME is name for the buffer.
 */
#define BUFFER_HEAP_INIT(NAME,SIZE) {\
    NAME.data = malloc(SIZE);                               \
    if (!NAME.data) return ;                                \
    NAME.ptr = NAME.data;                                   \
    NAME.capacity = SIZE;                                   \
    NAME.size = 0;                                          \
    memset(NAME.data, 0, SIZE);                             \
    NAME.mode = IS_HEAP;}

/*
 * @def BUFFER_COPY(DST, SRC, SIZE)
 * @brief copy the content of SRC to the DST buffer.
 * @note SIZE is the size of source in bytes will be copied to the buffer.
 * @result A pointer to the destination buffer or NULL if error was occured.
 */
#define BUFFER_COPY(DST, SRC, SIZE) {       \
    char *p = NULL;                         \
    p = memcpy(DST.data, SRC, SIZE);  \
    if (p) DST.size = ((unsigned long)(p+SIZE) - (unsigned long)DST.ptr);\
    }

/*
 * @def  BUFFER_SEARCH(DST, FIND, SIZE)
 * @brief Search occurence of FIND in DST buffer.
 * @note where SIZE is the length of FIND string.
 * @result A pointer to the occurence find in DST buffer or NULL if FIND string was not found.
 */
#define BUFFER_SEARCH(DST, FIND, SIZE) memmem(DST.ptr, DST.capacity, FIND, SIZE)

/*
 * @def BUFFER_STRCPY(DST, STR, SIZE)
 * @brief Copy string in destination buffer will null terminated string (null byte) at the end of the string.
 * @result a pointer to the destination buffer or NULL if an error was occured.
 */
#define BUFFER_STRCPY(DST, STR, SIZE) strncpy(DST.buf,STR,SIZE+1);DST.size=strlen(DST.str)

/*
 * @def BUFFER_ZERO(BUF)
 * @brief Zeroed a buffer BUF.
 * @result A pointer at the beginning of the buffer. or NULL if an error was occured.
 */
#define BUFFER_ZERO(BUF) memset(BUF.ptr, 0, BUF.capacity); BUF.size = 0

/*
 * @def BUFFER_CREATE(TYPE,NAME, SIZE)
 * @brief Create a buffer in the stack memory and initialize it to zero.
 * @note TYPE is type of your data like (char, short, int long)
 */
#define BUFFER_CREATE(TYPE, NAME, SIZE)  \
    struct buffer##NAME {                \
        /*                               \
        * @var TYPE data[SIZE]           \
        */                               \
        TYPE    data[SIZE];              \
                                         \
        union {                          \
            string_t     str;            \
            char        *buf;            \
            void        *ptr;            \
            uint64_t    *u64;            \
            int64_t     *i64;            \
            uint32_t    *u32;            \
            int32_t     *i32;            \
            uint16_t    *u16;            \
            int16_t     *i16;            \
            uint8_t     *u8;             \
            int8_t      *i8;             \
        };                               \
                                         \
        union {                          \
            size_t      size;            \
            size_t      length;          \
        };                               \
        size_t          capacity;        \
        buffer_mode_t   mode;            \
    } NAME; BUFFER_STACK_INIT(NAME);

/*
 * @def BUFFER_ALLOC(NAME,SIZE)
 * @brief Create buffer##NAME structure into the stack
 * alloacte memory from the heap.
 * @note The buffer must be freed at the end of usage.
 */
#define BUFFER_ALLOC(TYPE, NAME, SIZE)  \
    struct buffer_##NAME {               \
        TYPE            *data;          \
        union {                         \
            string_t     str;           \
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
        union {                         \
            size_t      length;         \
            size_t      size;           \
        };                              \
        size_t          capacity;       \
        buffer_mode_t   mode;           \
    } NAME; BUFFER_HEAP_INIT(NAME);

/*
 * @def BUFFER_DEF_STACK(NAME,TYPE,SIZE)
 * @brief Create buffer into the stack.
 * @param NAME is a name of the buffer type to create.
 * @param TYPE is a type of the buffer will be created.
 * @param SIZE is the size of the buffer.
 * @note The buffer must be freed at the end of usage.
 * where capacity is the max size of the buffer.
 */
#define BUFFER_DEF_STACK(TYPE, NAME, SIZE)  \
    typedef struct buffer_##NAME_t {        \
        TYPE            data[SIZE];         \
        union {                             \
            string_t     str;               \
            char        *buf;               \
            void        *ptr;               \
            uint64_t    *u64;               \
            int64_t     *i64;               \
            uint32_t    *u32;               \
            int32_t     *i32;               \
            uint16_t    *u16;               \
            int16_t     *i16;               \
            uint8_t     *u8;                \
            int8_t      *i8;                \
        };                                  \
        union {                             \
            size_t size;                    \
            size_t length;                  \
        };                                  \
        size_t          capacity;           \
        buffer_mode_t   mode;               \
    } buffer_##NAME_t;

// @def BUFFER_FREE(NAME) free the buffer in param and set the memory to zero.
#define BUFFER_FREE(NAME) free(NAME.data);  \
    memset(&NAME, 0, sizeof(NAME));         \
    NAME.mode=IS_HEAP;

// @def BUFFER_STACK(NAME) create buffer into the stack
#define BUFFER_STACK(BUFTYPE, NAME) buffer_##NAME_t NAME

// @def get the capacity of the buffer
#define BUFFER_GET_CAPACITY(NAME) NAME.capacity

// @def get the size of the buffer
#define BUFFER_GET_SIZE(NAME) NAME.size

// @def get the mode of the buffer
#define BUFFER_GET_MODE(NAME) NAME.mode

// @def BUFFER_IS_STACK(NAME)
// @result 1 if the buffer is on the stack
#define BUFFER_IS_STACK(NAME) NAME.mode == IS_STACK

// @def BUFFER_IS_HEAP(NAME)
// @result 1 if the buffer is on the heap
#define BUFFER_IS_HEAP(NAME) NAME.mode == IS_HEAP 

// @def get the buffer with char * type
#define BUFFER_GET(NAME) NAME.buf
// @def get the buffer with const char * type
#define BUFFER_STR(NAME) NAME.str
// @def get the buffer with void * type
#define BUFFER_PTR(NAME) NAME.ptr
// @def get the buffer with uint64_t * type
#define BUFFER_U64(NAME) NAME.u64
// @def get the buffer with int64_t * type
#define BUFFER_I64(NAME) NAME.i64
// @def get the buffer with uint32_t * type
#define BUFFER_U32(NAME) NAME.u32
// @def get the buffer with int32_t *type
#define BUFFER_I32(NAME) NAME.i32
// @def get the buffer with uint16_t *type;
#define BUFFER_U16(NAME) NAME.u16
// @def get the buffer with int16_t *type;
#define BUFFER_I16(NAME) NAME.i16
// @def get the buffer with int8_t  *type;
#define BUFFER_I8(NAME) NAME.i8
// @def get the buffer with uint8_t *type;
#define BUFFER_U8(NAME) NAME.u8

#endif
