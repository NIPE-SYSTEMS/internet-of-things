/**
 * Copyright (C) 2015 NIPE-SYSTEMS
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node-mqtt-subset.h"

/**
 * Writes a CONNECT message to the buffer at the given offset.
 * @param buffer The function writes to this buffer.
 * @param offset The function skips the amount of bytes in offset.
 * @param keep_alive The Keep Alive field. (4.3.1.2 in specification)
 * @param client_id The Client Id field. (4.3.1.3 in specification)
 */
void mqtt_output_connect(char *buffer, unsigned char *offset, unsigned int keep_alive, char *client_id)
{
	unsigned char message_header_address = 0;
	unsigned char message_header_length = 0;
	unsigned char client_id_iterator = 0;
	
	if(buffer == NULL)
	{
		return;
	}
	
	message_header_address = MQTT_SUBSET_ADDRESS;
	message_header_length = 3 + 2 + strlen(client_id);
	
	// Message Header
	buffer[(*offset)++] = message_header_address; // Address
	buffer[(*offset)++] = message_header_length; // Length
	buffer[(*offset)++] = 0; // Message Type
	
	// Message Body
	buffer[(*offset)++] = (keep_alive >> 8) & 0xFF; // Keep Alive
	buffer[(*offset)++] = keep_alive; // Keep Alive
	
	for(client_id_iterator = 0; client_id_iterator < strlen(client_id); client_id_iterator++)
	{
		buffer[(*offset)++] = client_id[client_id_iterator]; // ClientId
	}
}

/**
 * Writes a PUBLISH message to the buffer at the given offset.
 * @param buffer The function writes to this buffer.
 * @param offset The function skips the amount of bytes in offset.
 * @param retain The Retain flag of the Flags field. (4.3.3.2 in specification)
 * @param topic_id The Topic Id field. (4.3.3.3 in specification)
 * @param message_data The Message Data field. (4.3.3.4 in specification)
 */
void mqtt_output_publish(char *buffer, unsigned char *offset, char retain, unsigned int topic_id, char *message_data)
{
	unsigned char message_header_address = 0;
	unsigned char message_header_length = 0;
	unsigned char message_data_iterator = 0;
	
	if(buffer == NULL)
	{
		return;
	}
	
	message_header_address = MQTT_SUBSET_ADDRESS;
	message_header_length = 3 + 3 + strlen(message_data);
	
	// Message Header
	buffer[(*offset)++] = message_header_address; // Address
	buffer[(*offset)++] = message_header_length; // Length
	buffer[(*offset)++] = 2; // Message Type
	
	// Message Body
	if(retain == 1)
	{
		buffer[(*offset)++] = 1; // Flags
	}
	else
	{
		buffer[(*offset)++] = 0; // Flags
	}
	
	buffer[(*offset)++] = (topic_id >> 8) & 0xFF; // Topic Id
	buffer[(*offset)++] = topic_id; // Topic Id
	
	for(message_data_iterator = 0; message_data_iterator < strlen(message_data); message_data_iterator++)
	{
		buffer[(*offset)++] = message_data[message_data_iterator]; // Message Data
	}
}

/**
 * Writes a SUBSCRIBE message to the buffer at the given offset.
 * @param buffer The function writes to this buffer.
 * @param offset The function skips the amount of bytes in offset.
 * @param sub_topics The topics to be subscribed.
 * @param sub_topics_length The length of the sub_topics array.
 */
void mqtt_output_subscribe(char *buffer, unsigned char *offset, mqtt_sub_topics_t *sub_topics, unsigned char sub_topics_length)
{
	unsigned char message_header_address = 0;
	unsigned int message_header_length = 0;
	unsigned int sub_topics_iterator = 0;
	unsigned int sub_topics_topic_name_iterator = 0;
	
	if(buffer == NULL)
	{
		return;
	}
	
	message_header_address = MQTT_SUBSET_ADDRESS;
	
	message_header_length = 3;
	for(sub_topics_iterator = 0; sub_topics_iterator < sub_topics_length; sub_topics_iterator++)
	{
		message_header_length += 1 + strlen(sub_topics[sub_topics_iterator].topic_name);
	}
	
	if(message_header_length > 255)
	{
		return;
	}
	
	// Message Header
	buffer[(*offset)++] = message_header_address; // Address
	buffer[(*offset)++] = (unsigned char)message_header_length; // Length
	buffer[(*offset)++] = 3; // Message Type
	
	// Message Body
	for(sub_topics_iterator = 0; sub_topics_iterator < sub_topics_length; sub_topics_iterator++)
	{
		buffer[(*offset)++] = strlen(sub_topics[sub_topics_iterator].topic_name);
		for(sub_topics_topic_name_iterator = 0; sub_topics_topic_name_iterator < strlen(sub_topics[sub_topics_iterator].topic_name); sub_topics_topic_name_iterator++)
		{
			buffer[(*offset)++] = sub_topics[sub_topics_iterator].topic_name[sub_topics_topic_name_iterator];
		}
	}
}

/**
 * Writes a PINGREQ message to the buffer at the given offset.
 * @param buffer The function writes to this buffer.
 * @param offset The function skips the amount of bytes in offset.
 */
void mqtt_output_pingreq(char *buffer, unsigned char *offset)
{
	if(buffer == NULL)
	{
		return;
	}
	
	// Message Header
	buffer[(*offset)++] = MQTT_SUBSET_ADDRESS; // Address
	buffer[(*offset)++] = 3; // Length
	buffer[(*offset)++] = 5; // Message Type
	
	// Message Body
	// The PINGREQ message has no message body.
}

/**
 * Writes a PINGRESP message to the buffer at the given offset.
 * @param buffer The function writes to this buffer.
 * @param offset The function skips the amount of bytes in offset.
 */

void mqtt_output_pingresp(char *buffer, unsigned char *offset)
{
	if(buffer == NULL)
	{
		return;
	}
	
	// Message Header
	buffer[(*offset)++] = MQTT_SUBSET_ADDRESS; // Address
	buffer[(*offset)++] = 3; // Length
	buffer[(*offset)++] = 6; // Message Type
	
	// Message Body
	// The PINGRESP message has no message body.
}