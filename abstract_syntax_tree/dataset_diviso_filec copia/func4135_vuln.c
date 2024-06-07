void handle_usb_rx(const void *msg, size_t len)
{
    if (msg_tiny_flag) {
        uint8_t buf[64];
        memcpy(buf, msg, sizeof(buf));

        uint16_t msgId = buf[4] | ((uint16_t)buf[3]) << 8;
        uint32_t msgSize = buf[8]        |
                ((uint32_t)buf[7]) <<  8 |
                ((uint32_t)buf[6]) << 16 |
                ((uint32_t)buf[5]) << 24;

        if (msgSize > 64 - 9) {
            (*msg_failure)(FailureType_Failure_UnexpectedMessage, "STR");
            return;
        }

        
        const MessagesMap_t *entry = message_map_entry(NORMAL_MSG, msgId, IN_MSG);
        if (!entry) {
            (*msg_failure)(FailureType_Failure_UnexpectedMessage, "STR");
            return;
        }

        tiny_dispatch(entry, buf + 9, msgSize);
    } else {
        usb_rx_helper(msg, len, NORMAL_MSG);
    }
}