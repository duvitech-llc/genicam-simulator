#ifndef GIGE_SERVER_H
#define GIGE_SERVER_H

#include <stdint.h>
#include <arpa/inet.h>
#include "buffer_reader.h"
#include "gige_register_memory.h"

typedef struct
{
    uint32_t ip_address;
    uint32_t subnet_mask;
    uint32_t default_gateway;
    uint32_t ip_config_options;
    uint32_t ip_config_current;
    uint8_t mac_address[6];
} NetworkConfig;

bool handle_message(BufferReader *msg, struct sockaddr_in *client, int sock, CameraDevice *device);

#endif // GIGE_SERVER_H
