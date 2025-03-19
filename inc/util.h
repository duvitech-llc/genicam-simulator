#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include <stdio.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

// Function to print an array of bytes in hex format
void print_hex(const unsigned char *data, size_t length);
uint16_t g_ntohs(uint16_t value);
uint16_t g_htons(uint16_t value);
uint32_t g_ntohl(uint32_t netlong);
uint32_t g_htonl(uint32_t hostlong);
uint32_t GUINT32_FROM_BE(uint32_t value);
uint32_t GUINT32_TO_BE(uint32_t value);
char *g_strdup(const char *str);
char *g_file_get_contents(const char *file_path, size_t *length);
int64_t g_get_real_time(void);

#endif // UTIL_H
