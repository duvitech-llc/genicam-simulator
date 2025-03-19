#include "gige_register_memory.h"
#include "gige_commands.h"
#include "network_config.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

void camera_device_init(CameraDevice *device, const char *genicam_filename)
{
	// Clear the device memory
	device->genicam_xml = NULL;
	memset(device->memory, 0, SC_CAMERA_MEMORY_SIZE);
	memset(device->genicam_filename, 0, sizeof(device->genicam_filename));
	memset(device->genicam_xml_url, 0, sizeof(device->genicam_xml_url));

	// get genicam file
	if (genicam_filename != NULL)
		memcpy(device->genicam_filename, genicam_filename, strlen(genicam_filename));

	if (strlen(device->genicam_filename) >0)
	{
		device->genicam_xml = g_file_get_contents(device->genicam_filename, &device->genicam_xml_size);
		if (device->genicam_xml != NULL)
		{

			printf("Read XML Camera Definition: %s Length: %ld\r\n", device->genicam_filename, device->genicam_xml_size);

			// Generate the GenICam XML URL
			snprintf(device->genicam_xml_url, sizeof(device->genicam_xml_url),
					 "Local:///camera.xml;%x;%x",
					 SC_CAMERA_MEMORY_SIZE,
					 (unsigned int)device->genicam_xml_size);
		}
		else
		{
			printf("Failed to Read XML Camera Definition\r\n");
			device->genicam_xml_size = 0;
		}
	}

	//// MAC address
	// for (int i = 0; i < 6; i++) {
	//     write_byte(response, global_network_config.mac_address[i]);
	// }
	//
	//// IP configuration options and current
	// write_word_be(response, global_network_config.ip_config_options);
	// write_word_be(response, global_network_config.ip_config_current);
	//
	//// Reserved fields
	// write_reserved_to_resp(response, 3);
	//  camera_write_memory(device, SC_GVBS_DEVICE_MODE_OFFSET, 4, mode);

	// Current MAC
	camera_write_memory(device, SC_GVBS_DEVICE_MAC_ADDRESS_OFFSET, 6, global_network_config.mac_address);

	// Current IP
	camera_write_memory(device, SC_GVBS_CURRENT_IP_ADDRESS_OFFSET, sizeof(global_network_config.ip_address), (uint8_t *)&global_network_config.ip_address);

	strcpy(((char *)device->memory) + SC_GVBS_MANUFACTURER_NAME_OFFSET, GENICAM_CAMERA_MANUFACTURER_NAME);
	strcpy(((char *)device->memory) + SC_GVBS_MODEL_NAME_OFFSET, GENICAM_CAMERA_MANUFACTURER_MODEL);
	strcpy(((char *)device->memory) + SC_GVBS_MANUFACTURER_INFO_OFFSET, GENICAM_CAMERA_MANUFACTURER_INFO);
	strcpy(((char *)device->memory) + SC_GVBS_DEVICE_VERSION_OFFSET, GENICAM_CAMERA_VERSION);
	strcpy(((char *)device->memory) + SC_GVBS_SERIAL_NUMBER_OFFSET, GENICAM_CAMERA_SERIALNUM);

	strcpy(((char *)device->memory) + SC_GVBS_XML_URL_0_OFFSET, device->genicam_xml_url);

	// Optionally, write default values to memory-mapped registers
	camera_write_register(device, SC_CAMERA_REGISTER_SENSOR_WIDTH, SC_CAMERA_SENSOR_WIDTH);
	camera_write_register(device, SC_CAMERA_REGISTER_SENSOR_HEIGHT, SC_CAMERA_SENSOR_HEIGHT);
	camera_write_register(device, SC_CAMERA_REGISTER_WIDTH, SC_CAMERA_WIDTH_DEFAULT);
	camera_write_register(device, SC_CAMERA_REGISTER_HEIGHT, SC_CAMERA_HEIGHT_DEFAULT);
	camera_write_register(device, SC_CAMERA_REGISTER_PIXEL_FORMAT, PIXEL_FORMAT_MONO_8);
}

void camera_device_deinit(CameraDevice *device)
{
	if (device == NULL)
		return;

	if (device->genicam_xml != NULL)
	{
		free(device->genicam_xml);
	}
}

bool camera_read_memory(CameraDevice *camera, uint32_t address, uint32_t size, void *buffer)
{
	uint32_t read_size;
	if (buffer == NULL)
		return false;
	if (size == 0)
		return false;

	if (address < SC_CAMERA_MEMORY_SIZE)
	{
		read_size = MIN(address + size, SC_CAMERA_MEMORY_SIZE) - address;
		memcpy(buffer, ((char *)camera->memory) + address, read_size);
		if (read_size == size)
			return true;

		size = size - read_size;
		address = SC_CAMERA_MEMORY_SIZE;
		buffer = ((char *)buffer) + read_size;
	}

	address -= SC_CAMERA_MEMORY_SIZE;
	read_size = MIN(address + size, camera->genicam_xml_size) - address;

	memcpy(buffer, ((char *)camera->genicam_xml) + address, read_size);
	if (read_size < size)
		memset(((char *)buffer) + read_size, 0, size - read_size);

	return true;
}

bool camera_write_memory(CameraDevice *camera, uint32_t address, uint32_t size, void *buffer)
{
	if (address + size > SC_CAMERA_MEMORY_SIZE + camera->genicam_xml_size)
		return false;
	if (buffer == NULL)
		return false;
	if (size == 0)
		return false;

	/* genicam_data are read only */
	if (address + size > SC_CAMERA_MEMORY_SIZE)
		return false;

	memcpy(((char *)camera->memory) + address, buffer, size);

	return true;
}

bool camera_read_register(CameraDevice *camera, uint32_t address, uint32_t *value)
{
	bool success;
	uint32_t be_value = 0;

	if (value == NULL)
		return false;

	success = camera_read_memory(camera, address, sizeof(*value), &be_value);

	*value = GUINT32_FROM_BE(be_value);

	return success;
}

bool camera_write_register(CameraDevice *camera, uint32_t address, uint32_t value)
{
	uint32_t be_value = GUINT32_TO_BE(value);

	return camera_write_memory(camera, address, sizeof(value), &be_value);
}
