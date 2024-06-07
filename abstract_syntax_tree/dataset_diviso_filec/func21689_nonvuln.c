static void bonding_complete(struct btd_adapter *adapter,
					const bdaddr_t *bdaddr,
					uint8_t addr_type, uint8_t status)
{
	struct btd_device *device;

	if (status == 0)
		device = btd_adapter_get_device(adapter, bdaddr, addr_type);
	else
		device = btd_adapter_find_device(adapter, bdaddr, addr_type);

	if (device != NULL)
		device_bonding_complete(device, addr_type, status);

	resume_discovery(adapter);

	check_oob_bonding_complete(adapter, bdaddr, status);
}