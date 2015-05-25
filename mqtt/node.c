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
// #include <string.h>
#include "node-mqtt-subset.h"

/**
 * Prints a single byte as decimal and binary byte. Also the character is
 * printed.
 * @param byte The byte to print.
 */
void print_byte(char byte)
{
	printf("%3i '%c' %i%i%i%i%i%i%i%i\n", byte, byte, (byte&(1<<7))?(1):(0), (byte&(1<<6))?(1):(0), (byte&(1<<5))?(1):(0), (byte&(1<<4))?(1):(0), (byte&(1<<3))?(1):(0), (byte&(1<<2))?(1):(0), (byte&(1<<1))?(1):(0), (byte&(1<<0))?(1):(0));
}

/**
 * main without command line arguments.
 * @return Returns zero (success) all the time.
 */
int main(void)
{
	// char buffer[256];
	// unsigned char offset = 0;
	// unsigned int i = 0;
	// mqtt_sub_topics_t sub_topics[] =
	// {
	// 	{ "Topic 1", 0, NULL },
	// 	{ "Topic 2", 0, NULL }
	// };
	// unsigned char sub_topics_length = sizeof(sub_topics) / sizeof(sub_topics[0]);
	
	// // initialize buffer
	// for(i = 0; i < 256; i++)
	// {
	// 	buffer[i] = 0;
	// }
	
	// mqtt_write_pingreq(buffer, &offset);
	
	// // output buffer
	// for(i = 0; i < offset; i++)
	// {
	// 	print_byte(buffer[i]);
	// }
	
	// CONNACK parsing
	mqtt_read(16); // Address
	mqtt_read(4); // Length
	mqtt_read(0x01); // Message Type
	mqtt_read(0x01); // Return Code
	
	// PUBLISH parsing
	mqtt_read(16); // Address
	mqtt_read(9); // Length
	mqtt_read(0x02); // Message Type
	mqtt_read(0x01); // Flags
	mqtt_read(0x01); // Topic Id
	mqtt_read(0x00); // Topic Id
	mqtt_read('a'); // Message Data
	mqtt_read('b'); // Message Data
	mqtt_read('c'); // Message Data
	
	// SUBACK parsing
	mqtt_read(16); // Address
	mqtt_read(9); // Length
	mqtt_read(0x04); // Message Type
	mqtt_read(0x16); // Topic Id
	mqtt_read(0x00); // Topic Id
	mqtt_read(0x01); // Topic Id
	mqtt_read(0x00); // Topic Id
	mqtt_read(0x01); // Topic Id
	mqtt_read(0x03); // Topic Id
	
	// PINGREQ parsing
	mqtt_read(16); // Address
	mqtt_read(3); // Length
	mqtt_read(0x05); // Message Type
	
	// PINGRESP parsing
	mqtt_read(16); // Address
	mqtt_read(3); // Length
	mqtt_read(0x06); // Message Type
	
	return 0;
}