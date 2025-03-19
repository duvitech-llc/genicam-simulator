#ifndef GIGE_REGISTER_MEMORY_H
#define GIGE_REGISTER_MEMORY_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define SC_CAMERA_MEMORY_SIZE 0x2000

/* Grey pixel formats */

#define PIXEL_FORMAT_MONO_8 ((uint32_t)0x01080001u)
#define PIXEL_FORMAT_MONO_8_SIGNED ((uint32_t)0x01080002u)

#define PIXEL_FORMAT_MONO_10 ((uint32_t)0x01100003u)
#define PIXEL_FORMAT_MONO_10_PACKED ((uint32_t)0x010c0004u)

#define PIXEL_FORMAT_MONO_12 ((uint32_t)0x01100005u)
#define PIXEL_FORMAT_MONO_12_PACKED ((uint32_t)0x010c0006u)

#define PIXEL_FORMAT_MONO_14 ((uint32_t)0x01100025u)

#define PIXEL_FORMAT_MONO_16 ((uint32_t)0x01100007u)

/* Image format control */
#define SC_CAMERA_REGISTER_SENSOR_WIDTH 0x11c
#define SC_CAMERA_REGISTER_SENSOR_HEIGHT 0x118
#define SC_CAMERA_REGISTER_WIDTH 0x100
#define SC_CAMERA_REGISTER_HEIGHT 0x104
#define SC_CAMERA_REGISTER_PIXEL_FORMAT 0x128

#define SC_CAMERA_SENSOR_WIDTH 640
#define SC_CAMERA_SENSOR_HEIGHT 480
#define SC_CAMERA_WIDTH_DEFAULT 320
#define SC_CAMERA_HEIGHT_DEFAULT 240

#define SC_CAMERA_PIXEL_FORMAT_DEFAULT PIXEL_FORMAT_MONO_8
#define SC_CAMERA_TEST_REGISTER_DEFAULT 0x12345678

#define GENICAM_CAMERA_VERSION "0.1.0"
#define GENICAM_CAMERA_SERIALNUM "1234567890"
#define GENICAM_CAMERA_MANUFACTURER_NAME "GENICAM"
#define GENICAM_CAMERA_MANUFACTURER_MODEL "SC1002"
#define GENICAM_CAMERA_MANUFACTURER_INFO "Beta Camera"
#define GENICAM_CAMERA_MODEL "FPGA Camera"

// Device structure
typedef struct
{
	uint8_t memory[SC_CAMERA_MEMORY_SIZE]; // Device memory
	char genicam_filename[256];
	size_t genicam_xml_size;
	char genicam_xml_url[256];
	uint64_t controller_time;
	char *genicam_xml;

} CameraDevice;

// Function prototypes
void camera_device_init(CameraDevice *device, const char *genicam_filename);
bool camera_read_memory(CameraDevice *camera, uint32_t address, uint32_t size, void *buffer);
bool camera_write_memory(CameraDevice *camera, uint32_t address, uint32_t size, void *buffer);
bool camera_read_register(CameraDevice *camera, uint32_t address, uint32_t *value);
bool camera_write_register(CameraDevice *camera, uint32_t address, uint32_t value);

#endif // GIGE_REGISTER_MEMORY_H
