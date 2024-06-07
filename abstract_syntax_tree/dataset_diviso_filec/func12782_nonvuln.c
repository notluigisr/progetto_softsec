static void hso_kick_transmit(struct hso_serial *serial)
{
	unsigned long flags;
	int res;

	spin_lock_irqsave(&serial->serial_lock, flags);
	if (!serial->tx_buffer_count)
		goto out;

	if (serial->tx_urb_used)
		goto out;

	
	if (hso_get_activity(serial->parent) == -EAGAIN)
		goto out;

	
	swap(serial->tx_buffer, serial->tx_data);
	serial->tx_data_count = serial->tx_buffer_count;
	serial->tx_buffer_count = 0;

	
	if (serial->tx_data && serial->write_data) {
		res = serial->write_data(serial);
		if (res >= 0)
			serial->tx_urb_used = 1;
	}
out:
	spin_unlock_irqrestore(&serial->serial_lock, flags);
}