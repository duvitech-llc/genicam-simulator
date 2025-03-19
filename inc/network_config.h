#ifndef NETWORK_CONFIG_H
#define NETWORK_CONFIG_H

#include <stdint.h>

typedef struct
{
    uint32_t ip_address;
    uint32_t subnet_mask;
    uint32_t default_gateway;
    uint32_t ip_config_options;
    uint32_t ip_config_current;
    uint8_t mac_address[6];
} GlobalNetworkConfig;

// Declare the global network configuration structure
extern GlobalNetworkConfig global_network_config;
void update_network_config(GlobalNetworkConfig *config, uint32_t ip, uint32_t subnet, uint32_t gateway, uint32_t options, uint32_t current);
void update_global_config_with_system_ip();

#endif