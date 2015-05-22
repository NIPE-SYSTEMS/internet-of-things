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
#include "node-protocol.h"

/**
 * Encodes a string and prepends leading size information. All data is stored in
 * the buffer at offset.
 * @param buffer The buffer to which the string will be copied. The buffer must
 * be allocated (array with fixed size is recommended).
 * @param offset Skip this amount of bytes from the start of buffer.
 * @param string The string which should be inserted.
 */
void mqtt_string_encode(char *buffer, unsigned int *offset, char *string, unsigned int string_length)
{
	unsigned int i = 0;
	char string_length_msb = 0;
	char string_length_lsb = 0;
	
	if(buffer == NULL || string == NULL)
	{
		return;
	}
	
	// retrieve size information
	string_length_msb = (string_length >> 8) & 0xFF;
	string_length_lsb = string_length & 0xFF;
	
	// append size information to buffer
	buffer[(*offset)++] = string_length_msb;
	buffer[(*offset)++] = string_length_lsb;
	
	// append real data
	for(i = 0; i < string_length; i++)
	{
		buffer[(*offset)++] = string[i];
	}
}

/**
 * Measures the remaining length of the variable header and the payload. This is
 * used in the fixed header of the CONNECT control packet.
 * @param client_id The ClientId of the client.
 * @param will_topic The Will Topic. This variable can be NULL.
 * @param will_message The Will Topic. This variable can be NULL.
 * @param username The Will Topic. This variable can be NULL.
 * @param password The Will Topic. This variable can be NULL.
 * @return The calculated remaining length of the variable header and the
 * payload.
 */
static unsigned int mqtt_connect_measure_variable_and_payload(char *client_id, char *will_topic, char *will_message, char *username, char *password)
{
	unsigned int measured_size = 0;
	
	// measure variable header
	measured_size += 6; // Protocol Name
	measured_size += 1; // Protocol Level
	measured_size += 1; // Connect Flags
	measured_size += 2; // Keep Alive
	
	// measure payload
	measured_size += strlen(client_id) + 2; // Client Identifier
	if(will_topic != NULL) measured_size += strlen(will_topic) + 2; // Will Topic
	if(will_message != NULL) measured_size += strlen(will_message) + 2; // Will Message
	if(username != NULL) measured_size += strlen(username) + 2; // User Name
	if(password != NULL) measured_size += strlen(password) + 2; // Password
	
	return measured_size;
}

/**
 * Measures the remaining length of the variable header and the payload. This is
 * used in the fixed header of the SUBSCRIBE control packet.
 * @param topic_filter The Topic Filter to subscribe.
 * @return The calculated remaining length of the variable header and the
 * payload.
 */
static unsigned int mqtt_subscribe_measure_variable_and_payload(char *topic_filter)
{
	unsigned int measured_size = 0;
	
	// measure variable header
	measured_size += 2; // Packet Identifier
	
	// measure payload
	measured_size += strlen(topic_filter) + 2; // Topic filter
	measured_size += 1;
	
	return measured_size;
}

/**
 * Measures the remaining length of the variable header and the payload. This is
 * used in the fixed header of the UNSUBSCRIBE control packet.
 * @param topic_filter The Topic Filter to unsubscribe.
 * @return The calculated remaining length of the variable header and the
 * payload.
 */
static unsigned int mqtt_unsubscribe_measure_variable_and_payload(char *topic_filter)
{
	unsigned int measured_size = 0;
	
	// measure variable header
	measured_size += 2; // Packet Identifier
	
	// measure payload
	measured_size += strlen(topic_filter) + 2; // Topic filter
	measured_size += 1;
	
	return measured_size;
}

/**
 * Writes a CONNECT control packet to the buffer.
 * @param buffer The buffer to which the string will be copied. The buffer must
 * be allocated (array with fixed size is recommended).
 * @param offset Skip this amount of bytes from the start of buffer.
 * @param will_retain The Will Retain flag in the Connect Flags. 1 means TRUE.
 * @param will_qos The Will QoS in the Connect Flags.
 * @param clean_session The Clean Session flag in the Connect Flags. 1 means TRUE.
 * @param client_id The ClientId of the client.
 * @param will_topic The Will Topic. This variable can be NULL.
 * @param will_message The Will Topic. This variable can be NULL.
 * @param username The Will Topic. This variable can be NULL.
 * @param password The Will Topic. This variable can be NULL.
 * @param keep_alive The Keep Alive.
 */
void mqtt_message_connect(char *buffer, unsigned int *offset, char will_retain, char will_qos, char clean_session, char *client_id, char *will_topic, char *will_message, char *username, char *password, unsigned int keep_alive)
{
	unsigned int measured_size = 0;
	char remaining_length_encoded_byte = 0;
	char connect_flags_byte = 0;
	
	if(buffer == NULL || client_id == NULL)
	{
		return;
	}
	
	// measure size of variable header and payload
	measured_size = mqtt_connect_measure_variable_and_payload(client_id, will_topic, will_message, username, password);
	
	// fixed header
	buffer[(*offset)++] = 1 << 4;
	do
	{
		remaining_length_encoded_byte = measured_size % 128;
		measured_size /= 128;
		// if there is more data to encode, set the top bit of this byte
		if(measured_size > 0)
		{
			remaining_length_encoded_byte |= 128;
		}
		buffer[(*offset)++] = remaining_length_encoded_byte;
	}
	while(measured_size > 0);
	
	// variable header
	buffer[(*offset)++] = 0; // Protocol Name
	buffer[(*offset)++] = 4; // Protocol Name
	buffer[(*offset)++] = 'M'; // Protocol Name
	buffer[(*offset)++] = 'Q'; // Protocol Name
	buffer[(*offset)++] = 'T'; // Protocol Name
	buffer[(*offset)++] = 'T'; // Protocol Name
	buffer[(*offset)++] = 4; // Protocol Level
	
	if(username != NULL)
	{
		connect_flags_byte += 1 << 7;
	}
	
	if(password != NULL)
	{
		connect_flags_byte += 1 << 6;
	}
	
	if(will_retain == 1)
	{
		connect_flags_byte += 1 << 5;
	}
	
	if(will_qos == 0 || will_qos == 1 || will_qos == 2)
	{
		connect_flags_byte += will_qos << 3;
	}
	
	if(will_topic != NULL && will_message != NULL)
	{
		connect_flags_byte += 1 << 2;
	}
	
	if(clean_session == 1)
	{
		connect_flags_byte += 1 << 1;
	}
	
	buffer[(*offset)++] = connect_flags_byte; // Connect Flags
	buffer[(*offset)++] = (keep_alive >> 8) & 0xFF; // Keep Alive
	buffer[(*offset)++] = keep_alive & 0xFF; // Keep Alive
	
	mqtt_string_encode(buffer, offset, client_id, strlen(client_id));
	
	if(will_topic != NULL)
	{
		mqtt_string_encode(buffer, offset, will_topic, strlen(will_topic));
	}
	
	if(will_message != NULL)
	{
		mqtt_string_encode(buffer, offset, will_message, strlen(will_message));
	}
	
	if(username != NULL)
	{
		mqtt_string_encode(buffer, offset, username, strlen(username));
	}
	
	if(password != NULL)
	{
		mqtt_string_encode(buffer, offset, password, strlen(password));
	}
}
