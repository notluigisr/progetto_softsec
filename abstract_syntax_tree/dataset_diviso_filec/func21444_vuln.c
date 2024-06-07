void __exit atalk_proc_exit(void)
{
	remove_proc_subtree("STR", init_net.proc_net);
}