static int read_download_mem(struct usb_device *dev, int start_address,
				int length, __u8 address_type, __u8 *buffer)
{
	int status = 0;
	__u8 read_length;
	u16 be_start_address;

	dev_dbg(&dev->dev, "STR", __func__, start_address, length);

	
	while (length) {
		if (length > 64)
			read_length = 64;
		else
			read_length = (__u8)length;

		if (read_length > 1) {
			dev_dbg(&dev->dev, "STR", __func__, start_address, read_length);
		}
		
		be_start_address = swab16((u16)start_address);
		status = ti_vread_sync(dev, UMPC_MEMORY_READ,
					(__u16)address_type,
					be_start_address,
					buffer, read_length);

		if (status) {
			dev_dbg(&dev->dev, "STR", __func__, status);
			return status;
		}

		if (read_length > 1)
			usb_serial_debug_data(&dev->dev, __func__, read_length, buffer);

		
		start_address += read_length;
		buffer += read_length;
		length -= read_length;
	}

	return status;
}