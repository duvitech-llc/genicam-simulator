#include "buffer_reader.h"
#include <stdlib.h>
#include <stdio.h>

BufferReader *create_buffer(size_t size)
{
    BufferReader *buf = (BufferReader *)malloc(sizeof(BufferReader));
    if (!buf)
    {
        fprintf(stderr, "Failed to allocate BufferReader\n");
        return NULL;
    }

    buf->buffer = (uint8_t *)malloc(size);
    if (!buf->buffer)
    {
        fprintf(stderr, "Failed to allocate buffer memory\n");
        free(buf);
        return NULL;
    }

    buf->size = size;
    buf->index = 0;
    return buf;
}

void free_buffer(BufferReader *buf)
{
    if (buf)
    {
        free(buf->buffer);
        free(buf);
    }
}

int write_word_be(BufferReader *buf, uint32_t value)
{
    if (buf->index + 4 > buf->size)
    {
        fprintf(stderr, "Buffer overflow in write_word_be\n");
        return -1; // Error: buffer overflow
    }
    buf->buffer[buf->index++] = (value >> 24) & 0xFF;
    buf->buffer[buf->index++] = (value >> 16) & 0xFF;
    buf->buffer[buf->index++] = (value >> 8) & 0xFF;
    buf->buffer[buf->index++] = value & 0xFF;
    return 0; // Success
}

int write_word_le(BufferReader *buf, uint32_t value)
{
    if (buf->index + 4 > buf->size)
    {
        fprintf(stderr, "Buffer overflow in write_word_be\n");
        return -1; // Error: buffer overflow
    }
    buf->buffer[buf->index++] = value & 0xFF;
    buf->buffer[buf->index++] = (value >> 8) & 0xFF;
    buf->buffer[buf->index++] = (value >> 16) & 0xFF;
    buf->buffer[buf->index++] = (value >> 24) & 0xFF;
    return 0; // Success
}

int write_half_word_be(BufferReader *buf, uint16_t value)
{
    if (buf->index + 2 > buf->size)
    {
        fprintf(stderr, "Buffer overflow in write_half_word_be\n");
        return -1; // Error: buffer overflow
    }
    buf->buffer[buf->index++] = (value >> 8) & 0xFF;
    buf->buffer[buf->index++] = value & 0xFF;
    return 0; // Success
}

int write_byte(BufferReader *buf, uint8_t value)
{
    if (buf->index + 1 > buf->size)
    {
        fprintf(stderr, "Buffer overflow in write_byte\n");
        return -1;
    }
    buf->buffer[buf->index++] = value;
    return 0;
}

uint32_t read_word_be(BufferReader *buf)
{
    if (buf->index + 4 > buf->size)
    {
        fprintf(stderr, "Buffer underflow in read_word_be\n");
        return 0; // Error: buffer underflow
    }
    uint32_t value = 0;
    value |= buf->buffer[buf->index++] << 24;
    value |= buf->buffer[buf->index++] << 16;
    value |= buf->buffer[buf->index++] << 8;
    value |= buf->buffer[buf->index++];
    return value;
}

uint16_t read_half_word_be(BufferReader *buf)
{
    if (buf->index + 2 > buf->size)
    {
        fprintf(stderr, "Buffer underflow in read_half_word_be\n");
        return 0; // Error: buffer underflow
    }
    uint16_t value = 0;
    value |= buf->buffer[buf->index++] << 8;
    value |= buf->buffer[buf->index++];
    return value;
}

uint8_t read_byte(BufferReader *buf)
{
    if (buf->index + 1 > buf->size)
    {
        fprintf(stderr, "Buffer underflow in read_byte\n");
        return 0; // Error: buffer underflow
    }
    return buf->buffer[buf->index++];
}

void reset_buffer(BufferReader *buf)
{
    buf->index = 0;
}

void debug_buffer(BufferReader *buf)
{
    printf("Buffer Debug (size: %zu, index: %zu):\n", buf->size, buf->index);
    for (size_t i = 0; i < buf->size; ++i)
    {
        printf("%02X ", buf->buffer[i]);
        if ((i + 1) % 16 == 0)
        {
            printf("\n");
        }
    }
    printf("\n");
}
