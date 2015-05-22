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

void mqtt_string_encode(char *buffer, unsigned int *offset, char *string, unsigned int string_length);
void mqtt_message_connect(char *buffer, unsigned int *offset, char will_retain, char will_qos, char clean_session, char *client_id, char *will_topic, char *will_message, char *username, char *password, unsigned int keep_alive);

#endif /* __NODE_PROTOCOL_H__ */
