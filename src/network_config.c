#include "network_config.h"
#include <stdio.h>
#include <ifaddrs.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <string.h>
#include <stdlib.h>

// Define the global network configuration
GlobalNetworkConfig global_network_config = {
    .ip_address = 0xC0A80101,      // Default IP: 192.168.1.1
    .subnet_mask = 0xFFFFFF00,     // Default Subnet Mask: 255.255.255.0
    .default_gateway = 0xC0A801FE, // Default Gateway: 192.168.1.254
    .ip_config_options = 0x01,     // DHCP enabled
    .ip_config_current = 0x02,     // Static IP
    .mac_address = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55}};

void update_network_config(GlobalNetworkConfig *config, uint32_t ip, uint32_t subnet, uint32_t gateway, uint32_t options, uint32_t current)
{
    if (config == NULL)
    {
        fprintf(stderr, "Error: NetworkConfig pointer is NULL.\n");
        return;
    }

    config->ip_address = ip;
    config->subnet_mask = subnet;
    config->default_gateway = gateway;
    config->ip_config_options = options;
    config->ip_config_current = current;

    printf("Network configuration updated:\n");
    printf("  IP Address: %u.%u.%u.%u\n",
           (ip >> 24) & 0xFF, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
    printf("  Subnet Mask: %u.%u.%u.%u\n",
           (subnet >> 24) & 0xFF, (subnet >> 16) & 0xFF, (subnet >> 8) & 0xFF, subnet & 0xFF);
    printf("  Default Gateway: %u.%u.%u.%u\n",
           (gateway >> 24) & 0xFF, (gateway >> 16) & 0xFF, (gateway >> 8) & 0xFF, gateway & 0xFF);
    printf("  Config Options: 0x%08X\n", options);
    printf("  Config Current: 0x%08X\n", current);
}

void update_global_config_with_system_ip()
{
    struct ifaddrs *ifaddr, *ifa;
    char ip[INET_ADDRSTRLEN];      // For IPv4 addresses
    char subnet[INET_ADDRSTRLEN];  // Placeholder for subnet mask
    char gateway[INET_ADDRSTRLEN]; // For the default gateway

    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs failed");
        return;
    }

    // Retrieve IP, subnet mask, and MAC address
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr == NULL || ifa->ifa_addr->sa_family != AF_INET)
        {
            continue; // Skip non-IPv4 addresses
        }

        // Get the IP address
        struct sockaddr_in *addr = (struct sockaddr_in *)ifa->ifa_addr;
        if (inet_ntop(AF_INET, &addr->sin_addr, ip, sizeof(ip)) == NULL)
        {
            perror("inet_ntop failed for IP");
            continue;
        }

        // Get the subnet mask
        struct sockaddr_in *netmask = (struct sockaddr_in *)ifa->ifa_netmask;
        if (inet_ntop(AF_INET, &netmask->sin_addr, subnet, sizeof(subnet)) == NULL)
        {
            perror("inet_ntop failed for subnet");
            continue;
        }

        printf("Interface: %s\n", ifa->ifa_name);
        printf("  IP Address: %s\n", ip);
        printf("  Subnet Mask: %s\n", subnet);

        // Update the global configuration with the first non-loopback IPv4 address
        if (strncmp(ifa->ifa_name, "lo", 2) != 0)
        { // Skip loopback
            global_network_config.ip_address = addr->sin_addr.s_addr;
            global_network_config.subnet_mask = netmask->sin_addr.s_addr;

            // Retrieve the MAC address
            struct ifreq ifr;
            int fd = socket(AF_INET, SOCK_DGRAM, 0);
            if (fd == -1)
            {
                perror("socket failed");
                continue;
            }

            strncpy(ifr.ifr_name, ifa->ifa_name, IFNAMSIZ - 1);
            if (ioctl(fd, SIOCGIFHWADDR, &ifr) == -1)
            {
                perror("ioctl failed for MAC address");
                close(fd);
                continue;
            }

            close(fd);

            // Copy the MAC address to the global configuration
            memcpy(global_network_config.mac_address, ifr.ifr_hwaddr.sa_data, 6);

            printf("  MAC Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
                   global_network_config.mac_address[0],
                   global_network_config.mac_address[1],
                   global_network_config.mac_address[2],
                   global_network_config.mac_address[3],
                   global_network_config.mac_address[4],
                   global_network_config.mac_address[5]);

            break; // Stop after the first non-loopback interface
        }
    }

    freeifaddrs(ifaddr);

    // Retrieve the default gateway
    FILE *route_file = fopen("/proc/net/route", "r");
    if (!route_file)
    {
        perror("Failed to open /proc/net/route");
        return;
    }

    char iface[IFNAMSIZ];
    unsigned long dest, gw;
    while (fscanf(route_file, "%s %lx %lx", iface, &dest, &gw) == 3)
    {
        if (dest == 0)
        { // Default route (0.0.0.0)
            struct in_addr gw_addr = {.s_addr = gw};
            if (inet_ntop(AF_INET, &gw_addr, gateway, sizeof(gateway)) == NULL)
            {
                perror("inet_ntop failed for gateway");
                break;
            }

            printf("Default Gateway: %s (Interface: %s)\n", gateway, iface);
            global_network_config.default_gateway = gw_addr.s_addr;
            break;
        }
    }

    fclose(route_file);

    // Print the updated global network configuration
    printf("Global Network Configuration:\n");
    printf("  IP Address: %u.%u.%u.%u\n",
           global_network_config.ip_address & 0xFF,
           (global_network_config.ip_address >> 8) & 0xFF,
           (global_network_config.ip_address >> 16) & 0xFF,
           (global_network_config.ip_address >> 24) & 0xFF);
    printf("  Subnet Mask: %u.%u.%u.%u\n",
           global_network_config.subnet_mask & 0xFF,
           (global_network_config.subnet_mask >> 8) & 0xFF,
           (global_network_config.subnet_mask >> 16) & 0xFF,
           (global_network_config.subnet_mask >> 24) & 0xFF);
    printf("  Default Gateway: %u.%u.%u.%u\n",
           (global_network_config.default_gateway >> 24) & 0xFF,
           (global_network_config.default_gateway >> 16) & 0xFF,
           (global_network_config.default_gateway >> 8) & 0xFF,
           global_network_config.default_gateway & 0xFF);
    printf("  MAC Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
           global_network_config.mac_address[0],
           global_network_config.mac_address[1],
           global_network_config.mac_address[2],
           global_network_config.mac_address[3],
           global_network_config.mac_address[4],
           global_network_config.mac_address[5]);
}
