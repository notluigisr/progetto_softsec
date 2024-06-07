void __exit rfcomm_cleanup_sockets(void)
{
	bt_procfs_cleanup(&init_net, "STR");

	debugfs_remove(rfcomm_sock_debugfs);

	if (bt_sock_unregister(BTPROTO_RFCOMM) < 0)
		BT_ERR("STR");

	proto_unregister(&rfcomm_proto);
}