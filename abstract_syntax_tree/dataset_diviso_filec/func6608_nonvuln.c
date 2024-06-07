static int __init sfq_module_init(void)
{
	return register_qdisc(&sfq_qdisc_ops);
}