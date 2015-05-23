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
#include "node-mqtt-sn.h"

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
	printf("[start] ADVERTISE:\n");
	
	// ADVERTISE
	mqtt_parse_byte(0b00000101); // Message Length
	mqtt_parse_byte(0b00000000); // Message Type
	mqtt_parse_byte(0b00000010); // GwId
	mqtt_parse_byte(0b00000010); // Duration << 8
	mqtt_parse_byte(0b00000010); // Duration
	
	printf("[start] SEARCHGW:\n");
	
	// SEARCHGW
	mqtt_parse_byte(0b00000011); // Message Length
	mqtt_parse_byte(0b00000001); // Message Type
	mqtt_parse_byte(0b00001000); // Radius
	
	printf("[start] GWINFO:\n");
	
	// GWINFO
	mqtt_parse_byte(0b00001010); // Message Length
	mqtt_parse_byte(0b00000010); // Message Type
	mqtt_parse_byte(0b00001111); // GwId
	mqtt_parse_byte('A'); // GwAdd
	mqtt_parse_byte('d'); // GwAdd
	mqtt_parse_byte('d'); // GwAdd
	mqtt_parse_byte('r'); // GwAdd
	mqtt_parse_byte('e'); // GwAdd
	mqtt_parse_byte('s'); // GwAdd
	mqtt_parse_byte('s'); // GwAdd
	
	return 0;
}