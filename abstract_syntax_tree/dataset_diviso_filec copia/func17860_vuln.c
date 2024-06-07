static void init_busid_table(void)
{
	
	memset(busid_table, 0, sizeof(busid_table));

	spin_lock_init(&busid_table_lock);
}