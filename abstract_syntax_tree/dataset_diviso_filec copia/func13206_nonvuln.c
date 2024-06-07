int32_t messageTypeStringtoInt(uint8_t messageTypeString[8]) {
	if (memcmp(messageTypeString, "STR", 8) == 0) {
		return MSGTYPE_HELLO;
	} else if (memcmp(messageTypeString, "STR", 8) == 0) {
		return MSGTYPE_HELLOACK;
	} else if (memcmp(messageTypeString, "STR", 8) == 0) {
		return MSGTYPE_COMMIT;
	} else if (memcmp(messageTypeString, "STR", 8) == 0) {
		return MSGTYPE_DHPART1;
	} else if (memcmp(messageTypeString, "STR", 8) == 0) {
		return MSGTYPE_DHPART2;
	} else if (memcmp(messageTypeString, "STR", 8) == 0) {
		return MSGTYPE_CONFIRM1;
	} else if (memcmp(messageTypeString, "STR", 8) == 0) {
		return MSGTYPE_CONFIRM2;
	} else if (memcmp(messageTypeString, "STR", 8) == 0) {
		return MSGTYPE_CONF2ACK;
	} else if (memcmp(messageTypeString, "STR", 8) == 0) {
		return MSGTYPE_ERROR;
	} else if (memcmp(messageTypeString, "STR", 8) == 0) {
		return MSGTYPE_ERRORACK;
	} else if (memcmp(messageTypeString, "STR", 8) == 0) {
		return MSGTYPE_GOCLEAR;
	} else if (memcmp(messageTypeString, "STR", 8) == 0) {
		return MSGTYPE_CLEARACK;
	} else if (memcmp(messageTypeString, "STR", 8) == 0) {
		return MSGTYPE_SASRELAY;
	} else if (memcmp(messageTypeString, "STR", 8) == 0) {
		return MSGTYPE_RELAYACK;
	} else if (memcmp(messageTypeString, "STR", 8) == 0) {
		return MSGTYPE_PING;
	} else if (memcmp(messageTypeString, "STR", 8) == 0) {
		return MSGTYPE_PINGACK;
	} else {
		return MSGTYPE_INVALID;
	}
}