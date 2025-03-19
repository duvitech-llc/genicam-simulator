#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "gige_server.h"
#include "gige_register_memory.h"
#include "network_config.h"
#include "util.h"

#define CONTROL_PORT 3956 // GigE Vision control protocol port

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    uint8_t buffer[1024];

    // Determine camera.xml path
    const char *camera_xml_path = (argc > 1) ? argv[1] : NULL;

    // Initialize socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket to address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(CONTROL_PORT);

    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Update system network config
    update_global_config_with_system_ip();

    // Initialize registers
    CameraDevice sc_device;
    camera_device_init(&sc_device, camera_xml_path);

    printf("Server running on port %d\n", CONTROL_PORT);

    while (1) {
        ssize_t len = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &client_len);
        if (len < 0) {
            perror("Receive failed");
            continue;
        }

        printf("Received Message Length: %ld\r\n", len);
        print_hex(buffer, len);

        BufferReader msg = { .buffer = buffer, .size = len, .index = 0 };
        handle_message(&msg, &client_addr, sock, &sc_device);
    }

    // No need to free static memory
    close(sock);
    return 0;
}
