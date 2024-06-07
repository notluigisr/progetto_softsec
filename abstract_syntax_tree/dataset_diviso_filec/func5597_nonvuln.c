void __init proc_root_init(void)
{
	int err;

	proc_init_inodecache();
	err = register_filesystem(&proc_fs_type);
	if (err)
		return;

	proc_self_init();
	proc_thread_self_init();
	proc_symlink("STR");

	proc_net_init();

#ifdef CONFIG_SYSVIPC
	proc_mkdir("STR", NULL);
#endif
	proc_mkdir("STR", NULL);
	proc_mkdir("STR", NULL);
	proc_create_mount_point("STR"); 
#if defined(CONFIG_SUN_OPENPROMFS) || defined(CONFIG_SUN_OPENPROMFS_MODULE)
	
	proc_create_mount_point("STR");
#endif
	proc_tty_init();
	proc_mkdir("STR", NULL);
	proc_sys_init();
}