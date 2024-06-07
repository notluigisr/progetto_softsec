static void __exit fini_umd(void)
{
	bpf_preload_ops = NULL;
	
	kill_pid(umd_ops.info.tgid, SIGKILL, 1);
	umd_ops.info.tgid = NULL;
	umd_unload_blob(&umd_ops.info);
}