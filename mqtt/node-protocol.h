#ifndef __NODE_PROTOCOL_H__
#define __NODE_PROTOCOL_H__

void mqtt_encode_string(char *buffer, unsigned int *offset, char *string, size_t string_length);

#endif /* __NODE_PROTOCOL_H__ */
