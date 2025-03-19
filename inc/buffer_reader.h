#ifndef BUFFER_READER_H
#define BUFFER_READER_H

#include <stdint.h>
#include <stddef.h>

// Define a structure for buffer handling
typedef struct
{
    uint8_t *buffer; // Pointer to the data buffer
    size_t size;     // Total size of the buffer
    size_t index;    // Current read/write index
} BufferReader;

// Function prototypes
BufferReader *create_buffer(size_t size);
void free_buffer(BufferReader *buf);

// Writing functions
int write_word_be(BufferReader *buf, uint32_t value);
int write_word_le(BufferReader *buf, uint32_t value);
int write_half_word_be(BufferReader *buf, uint16_t value);
int write_byte(BufferReader *buf, uint8_t value);

// Reading functions
uint32_t read_word_be(BufferReader *buf);
uint16_t read_half_word_be(BufferReader *buf);
uint8_t read_byte(BufferReader *buf);

// Utility functions
void reset_buffer(BufferReader *buf);
void debug_buffer(BufferReader *buf);

#endif // BUFFER_READER_H
