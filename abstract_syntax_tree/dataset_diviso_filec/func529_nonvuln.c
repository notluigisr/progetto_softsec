static void __exit sfq_module_exit(void)
{
	unregister_qdisc(&sfq_qdisc_ops);
}