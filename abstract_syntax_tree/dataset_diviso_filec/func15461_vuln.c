static int __init personal_pci_init(void)
{
	if (machine_is_personal_server())
		pci_common_init(&personal_server_pci);
	return 0;
}