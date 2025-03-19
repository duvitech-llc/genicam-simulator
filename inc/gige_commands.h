#ifndef GIGE_COMMANDS_H
#define GIGE_COMMANDS_H

#include "util.h"

// Standard device listening port for GVCP packets

#define SC_GVCP_PORT 3956

#define SC_GVBS_VERSION_OFFSET 0x00000000
#define SC_GVBS_VERSION_MINOR_MASK 0x0000ffff
#define SC_GVBS_VERSION_MINOR_POS 0
#define SC_GVBS_VERSION_MAJOR_MASK 0xffff0000
#define SC_GVBS_VERSION_MAJOR_POS 16

#define SC_GVBS_DEVICE_MODE_OFFSET 0x00000004
#define SC_GVBS_DEVICE_MODE_BIG_ENDIAN 1 << 31
#define SC_GVBS_DEVICE_MODE_CHARACTER_SET_MASK 0x0000ffff
#define SC_GVBS_DEVICE_MODE_CHARACTER_SET_POS 0

#define SC_GVBS_DEVICE_MAC_ADDRESS_OFFSET 0x0000000A

#define SC_GVBS_SUPPORTED_IP_CONFIGURATION_OFFSET 0x00000010
#define SC_GVBS_CURRENT_IP_CONFIGURATION_OFFSET 0x00000014
#define SC_GVBS_IP_CONFIGURATION_PERSISTENT 1 << 0
#define SC_GVBS_IP_CONFIGURATION_DHCP 1 << 1
#define SC_GVBS_IP_CONFIGURATION_LLA 1 << 2

#define SC_GVBS_CURRENT_IP_ADDRESS_OFFSET 0x00000024
#define SC_GVBS_CURRENT_SUBNET_MASK_OFFSET 0x00000034
#define SC_GVBS_CURRENT_GATEWAY_OFFSET 0x00000044

#define SC_GVBS_MANUFACTURER_NAME_OFFSET 0x00000048
#define SC_GVBS_MANUFACTURER_NAME_SIZE 32

#define SC_GVBS_MODEL_NAME_OFFSET 0x00000068
#define SC_GVBS_MODEL_NAME_SIZE 32

#define SC_GVBS_DEVICE_VERSION_OFFSET 0x00000088
#define SC_GVBS_DEVICE_VERSION_SIZE 32

#define SC_GVBS_MANUFACTURER_INFO_OFFSET 0x000000a8
#define SC_GVBS_MANUFACTURER_INFO_SIZE 48

#define SC_GVBS_SERIAL_NUMBER_OFFSET 0x000000d8
#define SC_GVBS_SERIAL_NUMBER_SIZE 16

#define SC_GVBS_USER_DEFINED_NAME_OFFSET 0x000000e8
#define SC_GVBS_USER_DEFINED_NAME_SIZE 16

#define SC_GVBS_DISCOVERY_DATA_SIZE 0xf8

#define SC_GVBS_XML_URL_0_OFFSET 0x00000200
#define SC_GVBS_XML_URL_1_OFFSET 0x00000400
#define SC_GVBS_XML_URL_SIZE 512

#define SC_GVBS_N_NETWORK_INTERFACES_OFFSET 0x00000600

#define SC_GVBS_PERSISTENT_IP_ADDRESS_0_OFFSET 0x0000064c
#define SC_GVBS_PERSISTENT_SUBNET_MASK_0_OFFSET 0x0000065c
#define SC_GVBS_PERSISTENT_GATEWAY_0_OFFSET 0x0000066c

#define SC_GVBS_N_MESSAGE_CHANNELS_OFFSET 0x00000900
#define SC_GVBS_N_STREAM_CHANNELS_OFFSET 0x00000904

#define SC_GVBS_GVCP_CAPABILITY_OFFSET 0x00000934
#define SC_GVBS_GVCP_CAPABILITY_CONCATENATION 1 << 0
#define SC_GVBS_GVCP_CAPABILITY_WRITE_MEMORY 1 << 1
#define SC_GVBS_GVCP_CAPABILITY_PACKET_RESEND 1 << 2
#define SC_GVBS_GVCP_CAPABILITY_EVENT 1 << 3
#define SC_GVBS_GVCP_CAPABILITY_EVENT_DATA 1 << 4
#define SC_GVBS_GVCP_CAPABILITY_PENDING_ACK 1 << 5
#define SC_GVBS_GVCP_CAPABILITY_ACTION 1 << 6
#define SC_GVBS_GVCP_CAPABILITY_PRIMARY_APPLICATION_SWITCHOVER 1 << 21
#define SC_GVBS_GVCP_CAPABILITY_EXTENDED_STATUS_CODES 1 << 22
#define SC_GVBS_GVCP_CAPABILITY_DISCOVERY_ACK_DELAY_WRITABLE 1 << 23
#define SC_GVBS_GVCP_CAPABILITY_DISCOVERY_ACK_DELAY 1 << 24
#define SC_GVBS_GVCP_CAPABILITY_TEST_DATA 1 << 25
#define SC_GVBS_GVCP_CAPABILITY_MANIFEST_TABLE 1 << 26
#define SC_GVBS_GVCP_CAPABILITY_CCP_APPLICATION_SOCKET 1 << 27
#define SC_GVBS_GVCP_CAPABILITY_LINK_SPEED 1 << 28
#define SC_GVBS_GVCP_CAPABILITY_HEARTBEAT_DISABLE 1 << 29
#define SC_GVBS_GVCP_CAPABILITY_SERIAL_NUMBER 1 << 30
#define SC_GVBS_GVCP_CAPABILITY_NAME_REGISTER 1 << 31

#define SC_GVBS_HEARTBEAT_TIMEOUT_OFFSET 0x00000938
#define SC_GVBS_TIMESTAMP_TICK_FREQUENCY_HIGH_OFFSET 0x0000093c
#define SC_GVBS_TIMESTAMP_TICK_FREQUENCY_LOW_OFFSET 0x00000940
#define SC_GVBS_TIMESTAMP_CONTROL_OFFSET 0x00000944
#define SC_GVBS_TIMESTAMP_LATCHED_VALUE_HIGH_OFFSET 0x00000948
#define SC_GVBS_TIMESTAMP_LATCHED_VALUE_LOW_OFFSET 0x0000094c

#define SC_GVBS_CONTROL_CHANNEL_PRIVILEGE_OFFSET 0x00000a00
#define SC_GVBS_CONTROL_CHANNEL_PRIVILEGE_CONTROL 1 << 1
#define SC_GVBS_CONTROL_CHANNEL_PRIVILEGE_EXCLUSIVE 1 << 0

#define SC_GVBS_STREAM_CHANNEL_0_PORT_OFFSET 0x00000d00

#define SC_GVBS_STREAM_CHANNEL_0_PACKET_SIZE_OFFSET 0x00000d04
#define SC_GVBS_STREAM_CHANNEL_0_PACKET_SIZE_MASK 0x0000ffff
#define SC_GVBS_STREAM_CHANNEL_0_PACKET_SIZE_POS 0
#define SC_GVBS_STREAM_CHANNEL_0_PACKET_BIG_ENDIAN 1 << 29
#define SC_GVBS_STREAM_CHANNEL_0_PACKET_DO_NOT_FRAGMENT 1 << 30
#define SC_GVBS_STREAM_CHANNEL_0_PACKET_SIZE_FIRE_TEST 1 << 31

#define SC_GVBS_STREAM_CHANNEL_0_PACKET_DELAY_OFFSET 0x00000d08

#define SC_GVBS_STREAM_CHANNEL_0_IP_ADDRESS_OFFSET 0x00000d18

#define SC_GVCP_DATA_SIZE_MAX 512

typedef enum
{
	SC_GVCP_PACKET_TYPE_ACK = 0x00,
	SC_GVCP_PACKET_TYPE_CMD = 0x42,
	SC_GVCP_PACKET_TYPE_ERROR = 0x80,
	SC_GVCP_PACKET_TYPE_UNKNOWN_ERROR = 0x8f
} ScGvcpPacketType;

typedef enum
{
	SC_GVCP_ERROR_NONE = 0x00,
	SC_GVCP_ERROR_NOT_IMPLEMENTED = 0x01,
	SC_GVCP_ERROR_INVALID_PARAMETER = 0x02,
	SC_GVCP_ERROR_INVALID_ACCESS = 0x03,
	SC_GVCP_ERROR_WRITE_PROTECT = 0x04,
	SC_GVCP_ERROR_BAD_ALIGNMENT = 0x05,
	SC_GVCP_ERROR_ACCESS_DENIED = 0x06,
	SC_GVCP_ERROR_BUSY = 0x07,
	SC_GVCP_ERROR_LOCAL_PROBLEM = 0x08,
	SC_GVCP_ERROR_MESSAGE_MISMATCH = 0x09,
	SC_GVCP_ERROR_INVALID_PROTOCOL = 0x0a,
	SC_GVCP_ERROR_NO_MESSAGE = 0x0b,
	SC_GVCP_ERROR_PACKET_UNAVAILABLE = 0x0c,
	SC_GVCP_ERROR_DATA_OVERRUN = 0x0d,
	SC_GVCP_ERROR_INVALID_HEADER = 0x0e,
	SC_GVCP_ERROR_WRONG_CONFIG = 0x0f,
	SC_GVCP_ERROR_PACKET_NOT_YET_AVAILABLE = 0x10,
	SC_GVCP_ERROR_PACKET_AND_PREVIOUS_REMOVED_FROM_MEMORY = 0x11,
	SC_GVCP_ERROR_PACKET_REMOVED_FROM_MEMORY = 0x12,
	SC_GVCP_ERROR_NO_REFERENCE_TIME = 0x13,
	SC_GVCP_ERROR_PACKET_TEMPORARILY_UNAVAILABLE = 0x14,
	SC_GVCP_ERROR_OVERFLOW = 0x15,
	SC_GVCP_ERROR_ACTION_LATE = 0x16,
	SC_GVCP_ERROR_LEADER_TRAILER_OVERFLOW = 0x17,
	SC_GVCP_ERROR_GENERIC = 0xff
} ScGvcpError;

typedef enum
{
	SC_GVCP_CMD_PACKET_FLAGS_NONE = 0x00,
	SC_GVCP_CMD_PACKET_FLAGS_ACK_REQUIRED = 0x01,
	SC_GVCP_CMD_PACKET_FLAGS_EXTENDED_IDS = 0x10,
} ScGvcpCmdPacketFlags;

typedef enum
{
	SC_GVCP_EVENT_PACKET_FLAGS_NONE = 0x00,
	SC_GVCP_EVENT_PACKET_FLAGS_64BIT_ID = 0x10,
} ScGvcpEventPacketFlags;

typedef enum
{
	SC_GVCP_DISCOVERY_PACKET_FLAGS_NONE = 0x00,
	SC_GVCP_DISCOVERY_PACKET_FLAGS_ALLOW_BROADCAST_ACK = 0x10,
} ScGvcpDiscoveryPacketFlags;

typedef enum
{
	SC_GVCP_COMMAND_DISCOVERY_CMD = 0x0002,
	SC_GVCP_COMMAND_DISCOVERY_ACK = 0x0003,
	SC_GVCP_COMMAND_BYE_CMD = 0x0004,
	SC_GVCP_COMMAND_BYE_ACK = 0x0005,
	SC_GVCP_COMMAND_PACKET_RESEND_CMD = 0x0040,
	SC_GVCP_COMMAND_PACKET_RESEND_ACK = 0x0041,
	SC_GVCP_COMMAND_READ_REGISTER_CMD = 0x0080,
	SC_GVCP_COMMAND_READ_REGISTER_ACK = 0x0081,
	SC_GVCP_COMMAND_WRITE_REGISTER_CMD = 0x0082,
	SC_GVCP_COMMAND_WRITE_REGISTER_ACK = 0x0083,
	SC_GVCP_COMMAND_READ_MEMORY_CMD = 0x0084,
	SC_GVCP_COMMAND_READ_MEMORY_ACK = 0x0085,
	SC_GVCP_COMMAND_WRITE_MEMORY_CMD = 0x0086,
	SC_GVCP_COMMAND_WRITE_MEMORY_ACK = 0x0087,
	SC_GVCP_COMMAND_PENDING_ACK = 0x0089
} ScGvcpCommand;

typedef struct
{
	uint8_t packet_type;
	uint8_t packet_flags;
	uint16_t command;
	uint16_t size;
	uint16_t id;
} ScGvcpHeader;

typedef struct
{
	ScGvcpHeader header;
	unsigned char data[];
} ScGvcpPacket;

static inline ScGvcpPacketType
sc_gvcp_packet_get_packet_type(ScGvcpPacket *packet, size_t size)
{
	if (packet == NULL || size < sizeof(ScGvcpPacket))
		return SC_GVCP_PACKET_TYPE_ERROR;

	return (ScGvcpPacketType)packet->header.packet_type;
}

static inline uint8_t
sc_gvcp_packet_get_packet_flags(ScGvcpPacket *packet, size_t size)
{
	if (packet == NULL || size < sizeof(ScGvcpPacket))
		return 0;

	return (ScGvcpPacketType)packet->header.packet_flags;
}

static inline ScGvcpCommand
sc_gvcp_packet_get_command(ScGvcpPacket *packet, size_t size)
{
	if (packet == NULL || size < sizeof(ScGvcpPacket))
		return (ScGvcpCommand)0;

	return (ScGvcpCommand)g_ntohs(packet->header.command);
}

static inline void
sc_gvcp_packet_set_packet_id(ScGvcpPacket *packet, uint16_t id, size_t size)
{
	if (packet != NULL && size >= sizeof(ScGvcpPacket))
		packet->header.id = g_ntohs(id);
}

static inline uint16_t
sc_gvcp_packet_get_packet_id(ScGvcpPacket *packet, size_t size)
{
	if (packet == NULL || size < sizeof(ScGvcpPacket))
		return 0;

	return g_ntohs(packet->header.id);
}

#endif // GIGE_COMMANDS_H
