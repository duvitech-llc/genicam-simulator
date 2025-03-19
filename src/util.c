#include "util.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

uint16_t g_ntohs(uint16_t value)
{
    return ((value >> 8) & 0xFF) | ((value << 8) & 0xFF00);
}

uint16_t g_htons(uint16_t value)
{
    return ((value >> 8) & 0xFF) | ((value << 8) & 0xFF00);
}

uint32_t g_ntohl(uint32_t netlong)
{
    uint32_t hostlong;
    unsigned char *p = (unsigned char *)&netlong;
    hostlong = ((uint32_t)p[0] << 24) | ((uint32_t)p[1] << 16) |
               ((uint32_t)p[2] << 8) | ((uint32_t)p[3]);
    return hostlong;
}

uint32_t g_htonl(uint32_t hostlong)
{
// Check if the host is little-endian
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    // Swap bytes for little-endian systems
    return ((hostlong & 0xFF000000) >> 24) |
           ((hostlong & 0x00FF0000) >> 8) |
           ((hostlong & 0x0000FF00) << 8) |
           ((hostlong & 0x000000FF) << 24);
#else
    // No conversion needed for big-endian systems
    return hostlong;
#endif
}

int64_t g_get_real_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL); // Get the current time

    // Convert seconds and microseconds to microseconds since the epoch
    return (int64_t)tv.tv_sec * 1000000 + (int64_t)tv.tv_usec;
}

char *g_strdup(const char *str)
{
    if (str == NULL)
    {
        return NULL;
    }

    size_t len = strlen(str) + 1;
    char *new_str = (char *)malloc(len);

    if (new_str != NULL)
    {
        strcpy(new_str, str);
    }

    return new_str;
}

uint32_t GUINT32_FROM_BE(uint32_t value)
{
// Check if the host is little-endian
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    // Swap bytes for little-endian systems
    return ((value & 0xFF000000) >> 24) |
           ((value & 0x00FF0000) >> 8) |
           ((value & 0x0000FF00) << 8) |
           ((value & 0x000000FF) << 24);
#else
    // No conversion needed for big-endian systems
    return value;
#endif
}

uint32_t GUINT32_TO_BE(uint32_t value)
{
// Check if the host is little-endian
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    // Swap bytes for little-endian systems
    return ((value & 0xFF000000) >> 24) |
           ((value & 0x00FF0000) >> 8) |
           ((value & 0x0000FF00) << 8) |
           ((value & 0x000000FF) << 24);
#else
    // No conversion needed for big-endian systems
    return value;
#endif
}

// Reads the entire contents of a file into a string (similar to g_file_get_contents)
char *g_file_get_contents(const char *file_path, size_t *length)
{
    FILE *file = fopen(file_path, "rb"); // Open the file in binary mode
    if (file == NULL)
    {
        return NULL; // Return NULL if the file cannot be opened
    }

    // Determine the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size < 0)
    {
        fclose(file);
        return NULL; // Return NULL if the file size cannot be determined
    }

    // Allocate memory for the file contents (+1 for the null terminator)
    char *buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL)
    {
        fclose(file);
        return NULL; // Return NULL if memory allocation fails
    }

    // Read the file contents into the buffer
    size_t bytes_read = fread(buffer, 1, file_size, file);
    fclose(file);

    if (bytes_read != (size_t)file_size)
    {
        free(buffer);
        return NULL; // Return NULL if the file cannot be fully read
    }

    // Null-terminate the buffer
    buffer[file_size] = '\0';

    // Optionally return the length of the file contents
    if (length != NULL)
    {
        *length = file_size;
    }

    return buffer; // Return the file contents as a string
}

void print_hex(const unsigned char *data, size_t length)
{
    if (data == NULL || length == 0)
    {
        printf("No data to display.\n");
        return;
    }

    for (size_t i = 0; i < length; i++)
    {
        printf("%02X ", data[i]);
        if ((i + 1) % 16 == 0)
        {
            printf("\n"); // Newline after every 16 bytes for readability
        }
    }
    printf("\n");
}
