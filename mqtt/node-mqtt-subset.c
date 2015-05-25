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

static unsigned char mqtt_sub_topics_length = 3;

/**
 * Writes a CONNECT message to the buffer at the given offset.
 * @param buffer The function writes to this buffer.
 * @param offset The function skips the amount of bytes in offset.
 * @param keep_alive The Keep Alive field. (4.3.1.2 in specification)
 * @param client_id The Client Id field. (4.3.1.3 in specification)
 */
void mqtt_write_connect(char *buffer, unsigned char *offset, unsigned int keep_alive, char *client_id)
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
void mqtt_write_publish(char *buffer, unsigned char *offset, char retain, unsigned int topic_id, char *message_data)
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
void mqtt_write_subscribe(char *buffer, unsigned char *offset, mqtt_sub_topics_t *sub_topics, unsigned char sub_topics_length)
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
void mqtt_write_pingreq(char *buffer, unsigned char *offset)
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
void mqtt_write_pingresp(char *buffer, unsigned char *offset)
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

/**
 * Reads a set of bytes and parses them with the MQTT subset specification. This
 * function is not thread- or interrupt-save.
 * @param received_byte The received byte from the network.
 */
void mqtt_read(char received_byte)
{
	unsigned char i = 0;
	
	static unsigned char received_byte_index = 0;
	static unsigned char remaining_length = 2;
	
	static unsigned char message_address = 0;
	static unsigned char message_type = 0;
	
	static char message_connack_return_code = 0;
	static unsigned char message_publish_flags = 0;
	static unsigned int message_publish_topic_id = 0;
	static char message_publish_message_data[250]; // length = 256 - 3 - 3 (message length - message header - leading message body)
	static unsigned char message_publish_message_data_length = 0;
	static unsigned int message_suback_topic_ids[32];
	static unsigned char message_suback_topic_ids_length = 0;
	
	// printf("%i: %i\n", received_byte_index, received_byte);
	
	if(received_byte_index == 0) // Address
	{
		message_address = received_byte;
	}
	else if(received_byte_index == 1) // Length
	{
		remaining_length = received_byte;
	}
	else if(received_byte_index == 2) // Message Type
	{
		message_type = received_byte;
		
		printf("Received message header: address = %i, length = %i, type = %i\n", message_address, remaining_length, message_type);
		
		if(message_type == 5) // PINGREQ
		{
			printf("Received PINGREQ\n");
		}
		else if(message_type == 6)
		{
			printf("Received PINGRESP\n");
		}
	}
	else
	{
		switch(message_type)
		{
			case 1: // CONNACK
			{
				message_connack_return_code = received_byte; // Return Code
				
				printf("CONNACK: return code = %i\n", message_connack_return_code);
				
				break;
			}
			case 2: // PUBLISH
			{
				if(received_byte_index - 3 == 0)
				{
					// printf("FLAGS: %i\n", received_byte); // Flags
					
					message_publish_flags = received_byte;
				}
				else if(received_byte_index - 3 == 1)
				{
					message_publish_topic_id = received_byte << 8; // Topic Id
				}
				else if(received_byte_index - 3 == 2)
				{
					message_publish_topic_id += received_byte; // Topic Id
				}
				else
				{
					message_publish_message_data[message_publish_message_data_length++] = received_byte; // Message Data
					
					if(received_byte_index + 1 == remaining_length)
					{
						message_publish_message_data[message_publish_message_data_length++] = 0; // Message Data Terminator ('\0')
						
						printf("PUBLISH: flags = %i, topic id = %i, message data = '%s'\n", message_publish_flags, message_publish_topic_id, message_publish_message_data);
					}
				}
				
				break;
			}
			case 4: // SUBSCRIBE
			{
				if((received_byte_index - 3) % 2 == 0)
				{
					message_suback_topic_ids[(received_byte_index - 3) / 2] = received_byte << 8; // Topic Id MSB
				}
				else
				{
					message_suback_topic_ids[(received_byte_index - 3) / 2] += received_byte; // Topic Id LSB
					message_suback_topic_ids_length = (received_byte_index - 3) / 2 + 1;
					
					if(received_byte_index + 1 == remaining_length)
					{
						printf("SUBACK: topic ids = [ ");
						
						for(i = 0; i < message_suback_topic_ids_length; i++)
						{
							printf("%i ", message_suback_topic_ids[i]);
						}
						
						printf("]\n");
					}
				}
			}
		}
	}
	
	received_byte_index++;
	
	if(received_byte_index == remaining_length)
	{
		received_byte_index = 0;
		remaining_length = 2;
		
		message_address = 0;
		message_type = 0;
		
		message_connack_return_code = 0;
		message_publish_flags = 0;
		message_publish_topic_id = 0;
		message_publish_message_data_length = 0;
		message_suback_topic_ids_length = 0;
		
		printf("Resetted.\n");
	}
}