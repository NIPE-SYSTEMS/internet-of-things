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

#ifndef __NODE_PROTOCOL_H__
#define __NODE_PROTOCOL_H__

#define MQTT_CONTROL_PACKET_TYPE_CONNECT 1
#define MQTT_CONTROL_PACKET_TYPE_CONNACK 2
#define MQTT_CONTROL_PACKET_TYPE_PUBLISH 3
#define MQTT_CONTROL_PACKET_TYPE_PUBACK 4
#define MQTT_CONTROL_PACKET_TYPE_PUBREC 5
#define MQTT_CONTROL_PACKET_TYPE_PUBREL 6
#define MQTT_CONTROL_PACKET_TYPE_PUBCOMP 7
#define MQTT_CONTROL_PACKET_TYPE_SUBSCRIBE 8
#define MQTT_CONTROL_PACKET_TYPE_SUBACK 9
#define MQTT_CONTROL_PACKET_TYPE_UNSUBSCRIBE 10
#define MQTT_CONTROL_PACKET_TYPE_UNSUBACK 11
#define MQTT_CONTROL_PACKET_TYPE_PINGREQ 12
#define MQTT_CONTROL_PACKET_TYPE_PINGRESP 13
#define MQTT_CONTROL_PACKET_TYPE_DISCONNECT 14

typedef struct
{
	char *topic_name;
	void *function_ptr; // value will be changed soon
} subscribed_topics_t;

void mqtt_string_encode(char *buffer, unsigned int *offset, char *string, unsigned int string_length);
void mqtt_message_connect(char *buffer, unsigned int *offset, char will_retain, char clean_session, char *client_id, char *will_topic, char *will_message, char *username, char *password, unsigned int keep_alive);
void mqtt_message_publish(char *buffer, unsigned int *offset, char retain, char *topic_name, char *payload);
void mqtt_message_subscribe(char *buffer, unsigned int *offset, subscribed_topics_t *subscribed_topics, unsigned int subscribed_topics_length);
void mqtt_message_pingreq(char *buffer, unsigned int *offset);

#endif /* __NODE_PROTOCOL_H__ */
