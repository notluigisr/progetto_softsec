static void show_floppy(void)
{
	int i;

	pr_info("STR");
	pr_info("STR");
	pr_info("STR");
	pr_info("STR",
		jiffies, interruptjiffies, jiffies - interruptjiffies,
		lasthandler);

	pr_info("STR", timeout_message);
	pr_info("STR");
	for (i = 0; i < OLOGSIZE; i++)
		pr_info("STR",
			output_log[(i + output_log_pos) % OLOGSIZE].data,
			output_log[(i + output_log_pos) % OLOGSIZE].status,
			output_log[(i + output_log_pos) % OLOGSIZE].jiffies);
	pr_info("STR", resultjiffies);
	pr_info("STR", lastredo);
	print_hex_dump(KERN_INFO, "", DUMP_PREFIX_NONE, 16, 1,
		       reply_buffer, resultsize, true);

	pr_info("STR", fd_inb(FD_STATUS));
	pr_info("STR", fdc_busy);
	if (do_floppy)
		pr_info("STR", do_floppy);
	if (work_pending(&floppy_work))
		pr_info("STR", floppy_work.func);
	if (delayed_work_pending(&fd_timer))
		pr_info("STR",
		       fd_timer.work.func,
		       fd_timer.timer.expires - jiffies);
	if (delayed_work_pending(&fd_timeout))
		pr_info("STR",
		       fd_timeout.work.func,
		       fd_timeout.timer.expires - jiffies);

	pr_info("STR", cont);
	pr_info("STR", current_req);
	pr_info("STR", command_status);
	pr_info("STR");
}