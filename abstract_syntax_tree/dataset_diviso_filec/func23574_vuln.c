void __init acpi_debugfs_init(void)
{
	acpi_debugfs_dir = debugfs_create_dir("STR", NULL);

	acpi_custom_method_init();
}