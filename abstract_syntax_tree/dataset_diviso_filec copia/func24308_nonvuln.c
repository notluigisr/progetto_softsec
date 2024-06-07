static void read_cb(struct bt_att_chan *chan, uint8_t opcode, const void *pdu,
					uint16_t length, void *user_data)
{
	struct bt_gatt_server *server = user_data;
	uint16_t handle;

	if (length != 2) {
		bt_att_chan_send_error_rsp(chan, opcode, 0,
						BT_ATT_ERROR_INVALID_PDU);
		return;
	}

	handle = get_le16(pdu);

	handle_read_req(chan, server, opcode, handle, 0);
}