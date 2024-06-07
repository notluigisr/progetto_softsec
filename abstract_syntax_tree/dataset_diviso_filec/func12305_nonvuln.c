static void conf_cb(uint8_t opcode, const void *pdu,
					uint16_t length, void *user_data)
{
	struct ind_data *data = user_data;

	if (data->callback)
		data->callback(data->user_data);
}