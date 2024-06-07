static void fwnet_receive_packet(struct fw_card *card, struct fw_request *r,
		int tcode, int destination, int source, int generation,
		unsigned long long offset, void *payload, size_t length,
		void *callback_data)
{
	struct fwnet_device *dev = callback_data;
	int rcode;

	if (destination == IEEE1394_ALL_NODES) {
		kfree(r);

		return;
	}

	if (offset != dev->handler.offset)
		rcode = RCODE_ADDRESS_ERROR;
	else if (tcode != TCODE_WRITE_BLOCK_REQUEST)
		rcode = RCODE_TYPE_ERROR;
	else if (fwnet_incoming_packet(dev, payload, length,
				       source, generation, false) != 0) {
		dev_err(&dev->netdev->dev, "STR");
		rcode = RCODE_CONFLICT_ERROR;
	} else
		rcode = RCODE_COMPLETE;

	fw_send_response(card, r, rcode);
}