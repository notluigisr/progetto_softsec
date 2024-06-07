static void cleanup_children_on_exit(void)
{
	cleanup_children(SIGTERM, 0);
}