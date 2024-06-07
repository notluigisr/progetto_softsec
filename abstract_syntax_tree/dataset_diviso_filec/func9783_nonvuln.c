static void buf_start(uint16_t duration, int err, void *user_data)
{
	if (err) {
		buf_sent(err, user_data);
	}
}