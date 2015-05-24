# Specification of a MQTT subset for a multinode network

## 1 Introduction

This specification defines a protocol which can be used to communicate between nodes in a multinode network. It uses a subset of the MQTT-protocol (specification: [http://docs.oasis-open.org/mqtt/mqtt/v3.1.1/os/mqtt-v3.1.1-os.html](http://docs.oasis-open.org/mqtt/mqtt/v3.1.1/os/mqtt-v3.1.1-os.html), date of link: 15-05-24) and the MQTT-SN-protocol (specification: [http://mqtt.org/new/wp-content/uploads/2009/06/MQTT-SN_spec_v1.2.pdf](http://mqtt.org/new/wp-content/uploads/2009/06/MQTT-SN_spec_v1.2.pdf), date of link: 15-05-24). The protocol aims to the target of MQTT which is a pushing-, not a polling network. The nodes can subscribe to topics and will then get all messages of this topic.

## 2 Network Topology

The network topology is a Star Network ([Wikipedia: Star Network](https://en.wikipedia.org/wiki/Star_network)). The gateway is the center of the network.

                [ Node 1 ]  [ Node 2]
                     \         /
                       \     /
    MQTT network <-> [ Gateway ] ----- [ Node 3 ]
                       /     \
                     /         \
                [ Node 5 ]  [ Node 4 ]

The gateway is also connected with a real MQTT network. Every message received by the gateway will be modified that the message can be sent to a real MQTT-Broker. In other words it is translated from this protocol to the MQTT protocol and also the other way round. From the MQTT network the nodes are talking to one node, the gateway. The gateway opens only one TCP/UDP connection to the MQTT-Broker.

## 3 General Remarks

* In the specification sometimes *UTF-8 encoded string* is said. This means not the *UTF-8 encoded string* as described in the MQTT-specification. It means only that it is an array of byte data without any further informations. The length is often limited by the length of the whole message.

## 4 Message Formats

### 4.1 General Message Format

| Message Header | Message Body |
|----------------|--------------|
| 3 bytes        | n bytes      |

### 4.2 Message Header

| Address | Length | Message Type |
|---------|--------|--------------|
| 1 byte  | 1 byte | 1 byte       |

The *Message Header* has a fixed size of 3 bytes.

#### 4.2.1 Address

The *Address* field is a 1 byte long field and specifies either the transceive address or the receive address. This depends on the sending direction. Messages sent from or to one of the nodes contains the **node address**. This ensures that the node can receive a control message from the gateway.

The gateway must read every message on the bus whereas the nodes should not read the whole message. A node reads the address and the message length in the header. If the address matches with its own address the message will be processed. Otherwise the message will be ignored.

##### 4.2.1.1 Example

The node sends a CONNECT message to the gateway which contains the address of the node. The gateway responds after the real connect to the central broker with a CONNACK message which contains also the node address. This message is received by the node because of the address.

#### 4.2.2 Length

The *Length* field is 1 byte long field. It defines the length of the whole message, including the *Length* itself. As a result the length of the whole message can be up to 255 bytes.

#### 4.2.3 Message Type

The *Message Type* field is a 1 byte long field which contains the type of the message.

| Message Type | Message Type value |
|--------------|--------------------|
| CONNECT      | 0x00               |
| CONNACK      | 0x01               |
| PUBLISH      | 0x02               |
| SUBSCRIBE    | 0x03               |
| SUBACK       | 0x04               |
| PINGREQ      | 0x05               |
| PINGRESP     | 0x06               |

### 4.3 Message Body

The *Message Body* part of a message depends on the type of the message.

#### 4.3.1 CONNECT

The *CONNECT* message is sent by a node to setup a connection. The message is used to register the node in the node network. The *CONNECT* message is not forwarded to the real MQTT-Broker.

##### 4.3.1.1 CONNECT Format

* Message Header
    * Address (node address)
    * Length
    * Message Type = `0x00`
* Message Body
    * Keep Alive
    * Client Id

##### 4.3.1.2 Keep Alive

The *Keep Alive* field is a 2 byte long field which describes the keep alive interval of the node. The node must send every `Keep Alive` seconds a *PINGREQ* message to ensure that the node is alive.

##### 4.3.1.3 Client Id

The *Client Id* is a UTF-8 encoded string. Its length is described by the length of the message. It must be a minimum of 1 character at a maximum of 23 characters. The *Client Id* must be a unique identifier of the node in the MQTT network.

#### 4.3.2 CONNACK

The *CONNACK* message is sent by a gateway to notify the client that the *CONNECT* message was successful or not.

##### 4.3.2.1 CONNACK Format

* Message Header
    * Address (node address)
    * Length = `4`
    * Message Type = `0x01`
* Message Body
    * Return Code

##### 4.3.2.2 Return Code

The *Return Code* field is a 1 byte long field. Its number represents a meaning of the transceiver.

| Return Code Value | Meaning                           |
|-------------------|-----------------------------------|
| 0x00              | Accepted                          |
| 0x01              | Rejected: invalid CONNECT message |

More specific *Return Code* values may be added in the future.

#### 4.3.3 PUBLISH

The *PUBLISH* message is sent by both a node and a gateway. The node can publish a message which will be transported to the MQTT-Broker. If the MQTT-Broker has a message for a subscribed topic of the node the gateway forwards this message to the node. A *PUBLISH* message coming from a node has the node address in the *Address* field. The message coming from the gateway has also the node address in the *Address* field.

##### 4.3.3.1 PUBLISH Format

* Message Header
    * Address (node address)
    * Length
    * Message Type = `0x02`
* Message Body
    * Flags
    * Topic Id
    * Message Data

##### 4.3.3.2 Flags

| Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0  |
|-------|-------|-------|-------|-------|-------|-------|--------|
| 0     | 0     | 0     | 0     | 0     | 0     | 0     | Retain |

The *Retain* flag matches with the meaning of the *RETAIN* flag of the MQTT-standard. If a message is flagged with the *Retain* flag the MQTT-Broker will store the message as last state of the topic. If a new client subscribes to the topic it will get the last message flagged with the *RETAIN* flag.

##### 4.3.3.3 Topic Id

The *Topic Id* field is a 2 byte long number which represents a unique topic ID. (See *SUBSCRIBE*-messages to see how they are generated.) The MSB is in the first sent byte and the LSB is in the second byte. As a result 65536 topics are supported.

##### 4.3.3.4 Message Data

The *Message Data* field represents the real data of the published message as UTF-8 encoded string. Its length is described by the length of the message.

#### 4.3.4 SUBSCRIBE

The *SUBSCRIBE* message is sent by a node to subsribe to specified topics. It is possible to subscribe to multiple topics with one *SUBSCRIBE* message. The sent topics are translated by the gateway in topic IDs. The gateway subscribes then to the topics of the real MQTT-Broker und waits for the response. If the gateway receives a response it will send a *SUBACK* message into the bus. This *SUBACK* message is addressed to the node which had sent the original message. The gateway creates for every new topic a topic ID which should be stored at the gateway as a kind of translation dictionary to translate topic ID back into topic names or the other way round.

##### 4.3.4.1 SUBSCRIBE Format

* Message Header
    * Address (node address)
    * Length
    * Message Type = `0x03`
* Message Body
    * Topic Name
        * Length
        * UTF-8 encoded string
    * ... (maybe another *Topic Name*)

##### 4.3.4.2 Topic Name

The *Topic Name* field is a UTF-8 encoded string. The length of the string is stored in 1 byte leading the string. The *Topic Name* field can be repeated. Make sure that the message length limit of 255 bytes is not exceeded. If multiple subscribtions do not fit in the message use multiple messages and split the subscribed topics. **Make also sure that the node sends only one *SUBSCRIBE* message at a time.** Otherwise the *SUBACK* responses cannot be assigned correctly.

A message ID may be added in the future to allow multiple *SUBSCRIBE* message operations at a time.

#### 4.3.5 SUBACK

The *SUBACK* message is sent by the gateway to respond to a *SUBSCRIBE* message of a node. The response contains of the generated topic IDs which can then be used for e.g. *PUBLISH* messages.

##### 4.3.5.1 SUBACK Format

* Message Header
    * Address (node address)
    * Length
    * Message Type = `0x04`
* Message Body
    * Topic Id
    * ... (maybe another *Topic Id*)

##### 4.3.5.2 Topic Id

The *Topic Id* field is a 2 byte long field. The field can be repeated. The topic IDs match with the sent topic names of a *SUBSCRIBE* message. It stores the generated topic IDs which can be used for e.g. *PUBLISH* messages.

#### 4.3.6 PINGREQ

The *PINGREQ* message is sent by a node to check if the connection is alive. The node must send every `Keep Alive` seconds (specified at *CONNECT*) a *PINGREQ* message to ensure that the node is alive. If the node does not send a *PINGREQ* the gateway informs other clients in the MQTT network that the node is lost.

Currently no tolerance is given with the *Keep Alive* feature. This means that the node must send the *PINGREQ* message before the *Keep Alive* timeout exceeds. This may be changed in the future.

##### 4.3.6.1 PINGREQ Format

* Message Header
    * Address (node address)
    * Length
    * Message Type = `0x05`
* Message Body
    * *The PINGREQ message has no message body.*

#### 4.3.7 PINGRESP

The *PINGREQP* message is sent by the gateway. With this message the gateway confirms the node that the network is up and that the node is also up.

##### 4.3.7.1 PINGRESP Format

* Message Header
    * Address (node address)
    * Length
    * Message Type = `0x06`
* Message Body
    * *The PINGRESP message has no message body.*
