/*! @file main.c
 *  @brief  Main of bytebreacher
 *  @note no note
 *  @bug no bugs known
 *  @version 0.0.1
 *  @date 06/02/2024 12:32:37
 *  @author Unam3dd (sam0verfl0w)
 *  @copyright Copyright (C) 2024 Sam0verfl0w
 */

#include <stdio.h>
#include "buffer.h"

int main(void)
{
    BUFFER_CREATE(unsigned char, buf, 0x100);

    BUFFER_COPY(buf, "hello", 5);

    printf("%s\n", buf.buf);

    return (0);
}
