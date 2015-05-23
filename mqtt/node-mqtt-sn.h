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

#define MQTT_SN_MSG_TYPE_ADVERTISE 0x00
#define MQTT_SN_MSG_TYPE_GWINFO 0x02
#define MQTT_SN_MSG_TYPE_CONNECT 0x04
#define MQTT_SN_MSG_TYPE_WILLTOPICREQ 0x06
#define MQTT_SN_MSG_TYPE_WILLMSGREQ 0x08
#define MQTT_SN_MSG_TYPE_REGISTER 0x0A
#define MQTT_SN_MSG_TYPE_PUBLISH 0x0C
#define MQTT_SN_MSG_TYPE_PUBCOMP 0x0E
#define MQTT_SN_MSG_TYPE_PUBREL 0x10
#define MQTT_SN_MSG_TYPE_SUBSCRIBE 0x12
#define MQTT_SN_MSG_TYPE_UNSUBSCRIBE 0x14
#define MQTT_SN_MSG_TYPE_PINGREQ 0x16
#define MQTT_SN_MSG_TYPE_DISCONNECT 0x18
#define MQTT_SN_MSG_TYPE_WILLTOPICUPD 0x1A
#define MQTT_SN_MSG_TYPE_WILLMSGUPD 0x1C
#define MQTT_SN_MSG_TYPE_SEARCHGW 0x01
#define MQTT_SN_MSG_TYPE_CONNACK 0x05
#define MQTT_SN_MSG_TYPE_WILLTOPIC 0x07
#define MQTT_SN_MSG_TYPE_WILLMSG 0x09
#define MQTT_SN_MSG_TYPE_REGACK 0x0B
#define MQTT_SN_MSG_TYPE_PUBACK 0x0D
#define MQTT_SN_MSG_TYPE_PUBREC 0x0F
#define MQTT_SN_MSG_TYPE_SUBACK 0x13
#define MQTT_SN_MSG_TYPE_UNSUBACK 0x15
#define MQTT_SN_MSG_TYPE_PINGRESP 0x17
#define MQTT_SN_MSG_TYPE_WILLTOPICRESP 0x1B
#define MQTT_SN_MSG_TYPE_WILLMSGRESP 0x1D

void mqtt_parse_byte(char byte);

#endif /* __NODE_MQTT_SN_H__ */
