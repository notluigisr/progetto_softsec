static bool hidp_send_intr_message(struct input_device *idev, uint8_t hdr,
					const uint8_t *data, size_t size)
{
	return hidp_send_message(idev->intr_io, hdr, data, size);
}