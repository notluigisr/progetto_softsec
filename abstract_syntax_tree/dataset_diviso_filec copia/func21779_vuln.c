void atalk_register_sysctl(void)
{
	atalk_table_header = register_net_sysctl(&init_net, "STR", atalk_table);
}