# Implementation status of the MQTT-Protocol for a node

- [x] string encoding (UTF-8)
- [x] CONNECT (request)
- [ ] CONNACK (response)
- [x] PUBLISH (request)
- [ ] ~~PUBACK (response)~~ (because QoS is 0)
- [ ] ~~PUBREC (request)~~ (because QoS is 0)
- [ ] ~~PUBREL (request)~~ (because QoS is 0)
- [ ] ~~PUBCOMP (request)~~ (because QoS is 0)
- [x] SUBSCRIBE (request)
- [ ] SUBACK (response)
- [ ] ~~UNSUBSCRIBE (request)~~ (must not be implemented, because nodes are always online and subscribe topics once)
- [ ] ~~UNSUBACK (response)~~ (must not be implemented, because nodes are always online and subscribe topics once)
- [ ] PINGREQ (request)
- [ ] PINGRESP (response)
- [ ] ~~DISCONNECT (request)~~ (must not be implemented, because nodes are always online)
- [ ] Packet Identifiers
