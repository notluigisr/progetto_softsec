const char *btd_adapter_get_storage_dir(struct btd_adapter *adapter)
{
	static char dir[25];

	if (adapter->bdaddr_type == BDADDR_LE_RANDOM) {
		strcpy(dir, "STR");
		ba2str(&adapter->bdaddr, dir + 7);
	} else {
		ba2str(&adapter->bdaddr, dir);
	}

	return dir;
}