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
#include "node-protocol.h"

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
	char buffer[128];
	unsigned int offset = 0;
	unsigned int i = 0;
	subscribed_topics_t subscribed_topics[] =
	{
		{ "a/b", NULL },
		{ "c/d", NULL }
	};
	
	// initialize buffer
	for(i = 0; i < 128; i++)
	{
		buffer[i] = 0;
	}
	
	mqtt_message_subscribe(buffer, &offset, subscribed_topics, sizeof(subscribed_topics) / sizeof(subscribed_topics[0]));
	
	// output buffer
	for(i = 0; i < offset; i++)
	{
		print_byte(buffer[i]);
	}
	
	return 0;
}