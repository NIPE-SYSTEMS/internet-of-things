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
#include "node-mqtt-sn.h"

void mqtt_parse_byte(char byte)
{
	static unsigned int received_byte_index = 0;
	
	static char message_header_length_received = 0;
	static char message_header_msg_type_received = 0;
	static char message_header_received = 0;
	
	static unsigned int message_length = 0;
	static char message_header_msg_type = 0;
	static char message_header_length = 0;
	
	static char message_advertise_gwid = 0;
	static unsigned int message_advertise_duration = 0;
	static char message_gwinfo_gwid = 0;
	static char message_gwinfo_gwadd[32];
	static unsigned int message_gwinfo_gwadd_length = 0;
	
	if(message_header_received == 0) // parse message header
	{
		if(message_header_length_received == 0)
		{
			// parse length
			if(received_byte_index == 0)
			{
				if(byte != 0x01)
				{
					message_length = byte;
					message_header_length = 2;
					message_header_length_received = 1; // parsing finished
				}
			}
			else
			{
				if(received_byte_index == 1)
				{
					message_length = byte << 8;
				}
				
				if(received_byte_index == 2)
				{
					message_length += byte;
					message_header_length = 4;
					message_header_length_received = 1; // parsing finished
				}
			}
		}
		else if(message_header_msg_type_received == 0)
		{
			// parse type
			message_header_msg_type = byte;
			message_header_msg_type_received = 1;
			message_header_received = 1;
			
			printf("Message Length: %i\nMessage Type: %x\nMessage Header Length: %i\n", message_length, message_header_msg_type, message_header_length);
		}
	}
	else // parse message variable part
	{
		switch(message_header_msg_type)
		{
			case MQTT_SN_MSG_TYPE_ADVERTISE:
			{
				if(received_byte_index - message_header_length == 0)
				{
					message_advertise_gwid = byte;
				}
				else if(received_byte_index - message_header_length == 1)
				{
					message_advertise_duration = byte << 8;
				}
				else if(received_byte_index - message_header_length == 2)
				{
					message_advertise_duration += byte;
					
					printf("ADVERTISE GwId: %i\nADVERTISE Duration: %i\n", message_advertise_gwid, message_advertise_duration);
				}
				
				break;
			}
			case MQTT_SN_MSG_TYPE_GWINFO:
			{
				if(received_byte_index - message_header_length == 0)
				{
					message_gwinfo_gwid = byte;
				}
				else
				{
					message_gwinfo_gwadd[message_gwinfo_gwadd_length++] = byte;
					
					if(received_byte_index + 1 == message_length)
					{
						message_gwinfo_gwadd[message_gwinfo_gwadd_length] = 0;
						
						printf("GWINFO GwId: %i\nGWINFO GwAdd: %s\n", message_gwinfo_gwid, message_gwinfo_gwadd);
					}
				}
				
				break;
			}
			case MQTT_SN_MSG_TYPE_CONNECT:
			{
				printf("CONNECT is ignored.\n");
				
				break;
			}
			case MQTT_SN_MSG_TYPE_WILLTOPICREQ:
			{
				printf("WILLTOPICREQ not implemented.\n");
				
				break;
			}
			case MQTT_SN_MSG_TYPE_WILLMSGREQ:
			{
				printf("WILLMSGREQ not implemented.\n");
				
				break;
			}
			case MQTT_SN_MSG_TYPE_REGISTER:
			{
				printf("REGISTER not implemented.\n");
				
				break;
			}
			case MQTT_SN_MSG_TYPE_PUBLISH:
			{
				printf("PUBLISH not implemented.\n");
				
				break;
			}
			case MQTT_SN_MSG_TYPE_PUBCOMP:
			{
				printf("PUBCOMP not implemented.\n");
				
				break;
			}
			case MQTT_SN_MSG_TYPE_PUBREL:
			{
				printf("PUBREL not implemented.\n");
				
				break;
			}
			case MQTT_SN_MSG_TYPE_SUBSCRIBE:
			{
				printf("SUBSCRIBE not implemented.\n");
				
				break;
			}
			case MQTT_SN_MSG_TYPE_UNSUBSCRIBE:
			{
				printf("UNSUBSCRIBE not implemented.\n");
				
				break;
			}
			case MQTT_SN_MSG_TYPE_PINGREQ:
			{
				printf("PINGREQ not implemented.\n");
				
				break;
			}
			case MQTT_SN_MSG_TYPE_DISCONNECT:
			{
				printf("DISCONNECT not implemented.\n");
				
				break;
			}
			case MQTT_SN_MSG_TYPE_WILLTOPICUPD:
			{
				printf("WILLTOPICUPD not implemented.\n");
				
				break;
			}
			case MQTT_SN_MSG_TYPE_WILLMSGUPD:
			{
				printf("WILLMSGUPD not implemented.\n");
				
				break;
			}
			case MQTT_SN_MSG_TYPE_SEARCHGW:
			{
				printf("SEARCHGW is ignored.\n");
				
				break;
			}
			case MQTT_SN_MSG_TYPE_CONNACK:
			{
				printf("CONNACK not implemented.\n");
				
				break;
			}
			case MQTT_SN_MSG_TYPE_WILLTOPIC:
			{
				printf("WILLTOPIC not implemented.\n");
				
				break;
			}
			case MQTT_SN_MSG_TYPE_WILLMSG:
			{
				printf("WILLMSG not implemented.\n");
				
				break;
			}
			case MQTT_SN_MSG_TYPE_REGACK:
			{
				printf("REGACK not implemented.\n");
				
				break;
			}
			case MQTT_SN_MSG_TYPE_PUBACK:
			{
				printf("PUBACK not implemented.\n");
				
				break;
			}
			case MQTT_SN_MSG_TYPE_PUBREC:
			{
				printf("PUBREC not implemented.\n");
				
				break;
			}
			case MQTT_SN_MSG_TYPE_SUBACK:
			{
				printf("SUBACK not implemented.\n");
				
				break;
			}
			case MQTT_SN_MSG_TYPE_UNSUBACK:
			{
				printf("UNSUBACK not implemented.\n");
				
				break;
			}
			case MQTT_SN_MSG_TYPE_PINGRESP:
			{
				printf("PINGRESP not implemented.\n");
				
				break;
			}
			case MQTT_SN_MSG_TYPE_WILLTOPICRESP:
			{
				printf("WILLTOPICRESP not implemented.\n");
				
				break;
			}
			case MQTT_SN_MSG_TYPE_WILLMSGRESP:
			{
				printf("WILLMSGRESP not implemented.\n");
				
				break;
			}
		}
	}
	
	received_byte_index++;
	
	// if message is complete clean up and prepare for next message
	if(received_byte_index == message_length)
	{
		printf("[ end ] (parser reset)\n");
		
		received_byte_index = 0;
		
		message_header_length_received = 0;
		message_header_msg_type_received = 0;
		message_header_received = 0;
		
		message_length = 0;
		message_header_msg_type = 0;
		message_header_length = 0;
		
		message_advertise_gwid = 0;
		message_advertise_duration = 0;
		message_gwinfo_gwid = 0;
		message_gwinfo_gwadd_length = 0;
	}
}