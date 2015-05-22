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

/**
 * Encodes a string and prepends leading size information. All data is stored in
 * the buffer at offset.
 * @param buffer The buffer to which the string will be copied. The buffer must
 * be allocated (array with fixed size is recommended).
 * @param offset Skip this amount of bytes from the start of buffer.
 * @param string The string which should be inserted.
 */
void mqtt_encode_string(char *buffer, unsigned int *offset, char *string, unsigned int string_length)
{
	unsigned int i = 0;
	
	if(string == NULL)
	{
		return;
	}
	
	// retrieve size information
	char string_length_msb = (string_length >> 8) & 0xFF;
	char string_length_lsb = string_length & 0xFF;
	
	// append size information to buffer
	buffer[(*offset)++] = string_length_msb;
	buffer[(*offset)++] = string_length_lsb;
	
	// append real data
	for(i = 0; i < string_length; i++)
	{
		buffer[(*offset)++] = string[i];
	}
}
