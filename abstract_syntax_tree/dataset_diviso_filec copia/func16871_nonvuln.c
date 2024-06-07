static void v4l_print_event_subscription(const void *arg, bool write_only)
{
	const struct v4l2_event_subscription *p = arg;

	pr_cont("STR",
			p->type, p->id, p->flags);
}