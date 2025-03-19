#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include "buffer_reader.h"
#include "gige_commands.h"
#include "gige_register_memory.h"
#include "network_config.h"
#include "util.h"

size_t sc_gvcp_packet_get_read_register_ack_size(void)
{
	return sizeof(ScGvcpHeader) + sizeof(uint32_t);
}

size_t sc_gvcp_packet_get_write_register_ack_size(void)
{
	return sizeof(ScGvcpHeader) + sizeof(uint32_t);
}

ScGvcpPacket *sc_gvcp_packet_new_discovery_ack(uint16_t packet_id, uint32_t *packet_size)
{
	ScGvcpPacket *packet;

	if (packet_size == NULL)
		return NULL;

	*packet_size = sizeof(ScGvcpHeader) + SC_GVBS_DISCOVERY_DATA_SIZE;

	packet = malloc(*packet_size);

	packet->header.packet_type = SC_GVCP_PACKET_TYPE_ACK;
	packet->header.packet_flags = 0;
	packet->header.command = g_htons(SC_GVCP_COMMAND_DISCOVERY_ACK);
	packet->header.size = g_htons(SC_GVBS_DISCOVERY_DATA_SIZE);
	packet->header.id = g_htons(packet_id);

	return packet;
}

ScGvcpPacket *sc_gvcp_packet_new_read_memory_ack(uint32_t address, uint32_t size, uint16_t packet_id, uint32_t *packet_size)
{
	ScGvcpPacket *packet;
	uint32_t n_address = g_ntohl(address);

	if (packet_size == NULL)
		return NULL;

	*packet_size = sizeof(ScGvcpHeader) + sizeof(uint32_t) + size;

	packet = malloc(*packet_size);

	packet->header.packet_type = SC_GVCP_PACKET_TYPE_ACK;
	packet->header.packet_flags = 0;
	packet->header.command = g_htons(SC_GVCP_COMMAND_READ_MEMORY_ACK);
	packet->header.size = g_htons(sizeof(uint32_t) + size);
	packet->header.id = g_htons(packet_id);

	memcpy(&packet->data, &n_address, sizeof(uint32_t));

	return packet;
}

ScGvcpPacket *sc_gvcp_packet_new_write_memory_ack(uint32_t address, uint16_t packet_id, uint32_t *packet_size)
{
	ScGvcpPacket *packet;
	uint32_t n_address = g_htonl(address);

	if (packet_size == NULL)
		return NULL;

	*packet_size = sizeof(ScGvcpHeader) + sizeof(uint32_t);

	packet = malloc(*packet_size);

	packet->header.packet_type = SC_GVCP_PACKET_TYPE_ACK;
	packet->header.packet_flags = 0;
	packet->header.command = g_htons(SC_GVCP_COMMAND_WRITE_MEMORY_ACK);
	packet->header.size = g_htons(sizeof(uint32_t));
	packet->header.id = g_htons(packet_id);

	memcpy(&packet->data, &n_address, sizeof(uint32_t));

	return packet;
}

ScGvcpPacket *sc_gvcp_packet_new_read_register_ack(uint32_t value, uint16_t packet_id, uint32_t *packet_size)
{
	ScGvcpPacket *packet;
	uint32_t n_value = g_htonl(value);

	if (packet_size == NULL)
		return NULL;

	*packet_size = sc_gvcp_packet_get_read_register_ack_size();

	packet = malloc(*packet_size);

	packet->header.packet_type = SC_GVCP_PACKET_TYPE_ACK;
	packet->header.packet_flags = 0;
	packet->header.command = g_htons(SC_GVCP_COMMAND_READ_REGISTER_ACK);
	packet->header.size = g_htons(sizeof(uint32_t));
	packet->header.id = g_htons(packet_id);

	memcpy(&packet->data, &n_value, sizeof(uint32_t));

	return packet;
}

ScGvcpPacket *sc_gvcp_packet_new_write_register_ack(uint32_t data_index, uint16_t packet_id, uint32_t *packet_size)
{
	ScGvcpPacket *packet;
	uint32_t n_data_index = g_htonl(data_index);

	if (packet_size == NULL)
		return NULL;

	*packet_size = sc_gvcp_packet_get_write_register_ack_size();

	packet = malloc(*packet_size);

	packet->header.packet_type = SC_GVCP_PACKET_TYPE_ACK;
	packet->header.packet_flags = 0;
	packet->header.command = g_htons(SC_GVCP_COMMAND_WRITE_REGISTER_ACK);
	packet->header.size = g_htons(sizeof(uint32_t));
	packet->header.id = g_htons(packet_id);

	memcpy(&packet->data, &n_data_index, sizeof(uint32_t));

	return packet;
}

void sc_gvcp_packet_get_read_memory_cmd_infos(const ScGvcpPacket *packet, size_t packet_size, uint32_t *address, uint32_t *size)
{

	if (packet == NULL || packet_size < sizeof(ScGvcpPacket) + 2 * sizeof(uint32_t))
	{
		if (address != NULL)
			*address = 0;
		if (size != NULL)
			*size = 0;
		return;
	}

	if (address != NULL)
		*address = g_ntohl(*((uint32_t *)((char *)packet + sizeof(ScGvcpPacket))));
	if (size != NULL)
		*size = (g_ntohl(*((uint32_t *)((char *)packet + sizeof(ScGvcpPacket) + sizeof(uint32_t))))) & 0xffff;
}

void sc_gvcp_packet_get_read_register_cmd_infos(const ScGvcpPacket *packet, size_t packet_size, uint32_t *address)
{
	if (packet == NULL || packet_size < sizeof(ScGvcpPacket) + sizeof(uint32_t))
	{
		if (address != NULL)
			*address = 0;
		return;
	}

	if (address != NULL)
		*address = g_ntohl(*((uint32_t *)((char *)packet + sizeof(ScGvcpPacket))));
}

void sc_gvcp_packet_get_write_memory_cmd_infos(const ScGvcpPacket *packet, size_t packet_size, uint32_t *address, uint32_t *size)
{
	if (packet == NULL || packet_size < sizeof(ScGvcpPacket) + sizeof(uint32_t))
	{
		if (address != NULL)
			*address = 0;
		if (size != NULL)
			*size = 0;
		return;
	}

	if (address != NULL)
		*address = g_ntohl(*((uint32_t *)((char *)packet + sizeof(ScGvcpPacket))));
	if (size != NULL)
		*size = g_ntohs(packet->header.size) - sizeof(uint32_t);
}

void sc_gvcp_packet_get_write_register_cmd_infos(const ScGvcpPacket *packet, size_t packet_size, uint32_t *address, uint32_t *value)
{
	if (packet == NULL || packet_size < sizeof(ScGvcpPacket) + 2 * sizeof(uint32_t))
	{
		if (address != NULL)
			*address = 0;
		if (value != NULL)
			*value = 0;
		return;
	}

	if (address != NULL)
		*address = g_ntohl(*((uint32_t *)((char *)packet + sizeof(ScGvcpPacket))));
	if (value != NULL)
		*value = g_ntohl(*((uint32_t *)((char *)packet + sizeof(ScGvcpPacket) + sizeof(uint32_t))));
}

void *sc_gvcp_packet_get_read_memory_ack_data(const ScGvcpPacket *packet)
{
	return (char *)packet + sizeof(ScGvcpHeader) + sizeof(uint32_t);
}

void *sc_gvcp_packet_get_write_memory_cmd_data(const ScGvcpPacket *packet)
{
	return (char *)packet + sizeof(ScGvcpPacket) + sizeof(uint32_t);
}

// Handle incoming messages
bool handle_message(BufferReader *msg, struct sockaddr_in *client, int sock, CameraDevice *device)
{
	// Validate message length
	bool success = false;
	ScGvcpPacket *ack_packet = NULL;
	uint32_t ack_packet_size = 0;
	uint32_t block_address;
	uint32_t block_size;
	uint32_t register_address;
	uint32_t register_value;
	bool write_access = true;
	success = msg->size >= sizeof(ScGvcpHeader);
	if (success)
	{

		// Map the byte buffer to ScGvcpPacket
		ScGvcpPacket *packet = (ScGvcpPacket *)msg->buffer;

		ScGvcpPacketType packet_type;
		uint16_t packet_id;

		packet_id = sc_gvcp_packet_get_packet_id(packet, msg->size);
		packet_type = sc_gvcp_packet_get_packet_type(packet, msg->size);

		// Access the header fields
		printf("Packet Type: 0x%02X\n", packet_type);
		printf("Packet Flags: 0x%02X\n", packet->header.packet_flags);
		printf("Command: 0x%04X\n", g_ntohs(packet->header.command));
		printf("ID: 0x%04X\n", packet_id);

		if (packet_type != SC_GVCP_PACKET_TYPE_CMD)
		{
			printf("[GvFakeCamera::handle_control_packet] Unknown packet type");
			return false;
		}

		switch (g_ntohs(packet->header.command))
		{
		case SC_GVCP_COMMAND_DISCOVERY_CMD:
			ack_packet = sc_gvcp_packet_new_discovery_ack(packet_id, &ack_packet_size);
			printf("[ScCamera::handle_control_packet] Discovery command\r\n");
			camera_read_memory(device, 0, SC_GVBS_DISCOVERY_DATA_SIZE, ack_packet->data);
			break;
		case SC_GVCP_COMMAND_READ_MEMORY_CMD:
			sc_gvcp_packet_get_read_memory_cmd_infos(packet, msg->size, &block_address, &block_size);
			printf("[ScCamera::handle_control_packet] Read memory command %d (%d)\r\n", block_address, block_size);
			ack_packet = sc_gvcp_packet_new_read_memory_ack(block_address, block_size, packet_id, &ack_packet_size);
			camera_read_memory(device, block_address, block_size, sc_gvcp_packet_get_read_memory_ack_data(ack_packet));
			break;
		case SC_GVCP_COMMAND_WRITE_MEMORY_CMD:
			sc_gvcp_packet_get_write_memory_cmd_infos(packet, msg->size, &block_address, &block_size);
			if (!write_access)
			{
				printf("[ScCamera::handle_control_packet] Ignore Write memory command %d (%d) not controller\r\n", block_address, block_size);
				break;
			}
			printf("[ScCamera::handle_control_packet] Write memory command %d (%d)\r\n", block_address, block_size);
			camera_write_memory(device, block_address, block_size, sc_gvcp_packet_get_write_memory_cmd_data(packet));
			ack_packet = sc_gvcp_packet_new_write_memory_ack(block_address, packet_id, &ack_packet_size);
			break;
		case SC_GVCP_COMMAND_READ_REGISTER_CMD:
			sc_gvcp_packet_get_read_register_cmd_infos(packet, msg->size, &register_address);
			camera_read_register(device, register_address, &register_value);
			printf("[ScCamera::handle_control_packet] Read register command %d -> %d\r\n", register_address, register_value);
			ack_packet = sc_gvcp_packet_new_read_register_ack(register_value, packet_id, &ack_packet_size);
			if (register_address == SC_GVBS_CONTROL_CHANNEL_PRIVILEGE_OFFSET)
				device->controller_time = g_get_real_time();
			break;
		case SC_GVCP_COMMAND_WRITE_REGISTER_CMD:
			sc_gvcp_packet_get_write_register_cmd_infos(packet, msg->size, &register_address, &register_value);
			if (!write_access)
			{
				printf("[ScCamera::handle_control_packet] Ignore Write register command %d (%d) not controller\r\n", register_address, register_value);
				break;
			}
			camera_write_register(device, register_address, register_value);
			printf("[ScCamera::handle_control_packet] Write register command %d -> %d\r\n", register_address, register_value);
			ack_packet = sc_gvcp_packet_new_write_register_ack(1, packet_id, &ack_packet_size);
			break;
		default:
			printf("[ScCamera::handle_control_packet] Unknown command\r\n");
			break;
		}
	}

	if (ack_packet != NULL)
	{
		printf("ack_packet_size: %d\r\n", ack_packet_size);
		print_hex((uint8_t *)ack_packet, ack_packet_size);
		ssize_t sent_bytes = sendto(sock, (char *)ack_packet, ack_packet_size, 0, (struct sockaddr *)client, sizeof(*client));
		printf("Sent %ld bytes\r\n", sent_bytes);
		free(ack_packet);
	}

	return true;
}
