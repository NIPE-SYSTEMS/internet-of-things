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

/** Control message type */
typedef enum { CONNECT = 1, CONNACK, PUBLISH, PUBACK, PUBREC, PUBREL, PUBCOMP, SUBSCRIBE, SUBACK, UNSUBSCRIBE, UNSUBACK, PINGREQ, PINGRESP, DISCONNECT } control_message_type_t;

void mqtt_string_encode(char *buffer, unsigned int *offset, char *string, unsigned int string_length);
void mqtt_control_packet_fixed_header(char *buffer, unsigned int *offset, control_message_type_t type, char duplicate, char qos, char retain);

#endif /* __NODE_PROTOCOL_H__ */
