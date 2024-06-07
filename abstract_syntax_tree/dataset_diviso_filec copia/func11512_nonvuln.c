static void pincode_reply_complete(uint8_t status, uint16_t length,
					const void *param, void *user_data)
{
	struct btd_device *device = user_data;

	
	device_bonding_restart_timer(device);
}