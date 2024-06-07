static int sisusb_send_packet(struct sisusb_usb_data *sisusb, int len,
		struct sisusb_packet *packet)
{
	int ret;
	ssize_t bytes_transferred = 0;
	__le32 tmp;

	if (len == 6)
		packet->data = 0;

#ifdef SISUSB_DONTSYNC
	if (!(sisusb_wait_all_out_complete(sisusb)))
		return 1;
#endif

	
	SISUSB_CORRECT_ENDIANNESS_PACKET(packet);

	
	ret = sisusb_send_bulk_msg(sisusb, SISUSB_EP_GFX_OUT, len,
			(char *)packet, NULL, 0, &bytes_transferred, 0, 0);

	if ((ret == 0) && (len == 6)) {

		
		ret = sisusb_recv_bulk_msg(sisusb, SISUSB_EP_GFX_IN, 4,
				(char *)&tmp, NULL, &bytes_transferred, 0);

		packet->data = le32_to_cpu(tmp);
	}

	return ret;
}