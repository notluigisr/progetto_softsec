static int ttusb_dec_send_command(struct ttusb_dec *dec, const u8 command,
				  int param_length, const u8 params[],
				  int *result_length, u8 cmd_result[])
{
	int result, actual_len;
	u8 *b;

	dprintk("STR", __func__);

	b = kzalloc(COMMAND_PACKET_SIZE + 4, GFP_KERNEL);
	if (!b)
		return -ENOMEM;

	if ((result = mutex_lock_interruptible(&dec->usb_mutex))) {
		kfree(b);
		printk("STR", __func__);
		return result;
	}

	b[0] = 0xaa;
	b[1] = ++dec->trans_count;
	b[2] = command;
	b[3] = param_length;

	if (params)
		memcpy(&b[4], params, param_length);

	if (debug) {
		printk(KERN_DEBUG "STR",
		       __func__, param_length, b);
	}

	result = usb_bulk_msg(dec->udev, dec->command_pipe, b,
			      COMMAND_PACKET_SIZE + 4, &actual_len, 1000);

	if (result) {
		printk("STR",
		       __func__, result);
		mutex_unlock(&dec->usb_mutex);
		kfree(b);
		return result;
	}

	result = usb_bulk_msg(dec->udev, dec->result_pipe, b,
			      COMMAND_PACKET_SIZE + 4, &actual_len, 1000);

	if (result) {
		printk("STR",
		       __func__, result);
		mutex_unlock(&dec->usb_mutex);
		kfree(b);
		return result;
	} else {
		if (debug) {
			printk(KERN_DEBUG "STR",
			       __func__, actual_len, b);
		}

		if (result_length)
			*result_length = b[3];
		if (cmd_result && b[3] > 0)
			memcpy(cmd_result, &b[4], b[3]);

		mutex_unlock(&dec->usb_mutex);

		kfree(b);
		return 0;
	}
}