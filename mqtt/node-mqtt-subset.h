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

#ifndef __NODE_MQTT_SN_H__
#define __NODE_MQTT_SN_H__

#define MQTT_SUBSET_ADDRESS 0x10

typedef struct
{
	char *topic_name;
	unsigned int topic_id;
	void *function_pointer;
} mqtt_sub_topics_t;

void mqtt_write_connect(char *buffer, unsigned char *offset, unsigned int keep_alive, char *clientId);
void mqtt_write_publish(char *buffer, unsigned char *offset, char retain, unsigned int topic_id, char *message_data);
void mqtt_write_subscribe(char *buffer, unsigned char *offset, mqtt_sub_topics_t *sub_topics, unsigned char sub_topics_length);
void mqtt_write_pingreq(char *buffer, unsigned char *offset);
void mqtt_write_pingresp(char *buffer, unsigned char *offset);
void mqtt_read(char received_byte);

#endif /* __NODE_MQTT_SN_H__ */
