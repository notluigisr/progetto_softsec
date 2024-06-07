void uwbd_start(struct uwb_rc *rc)
{
	rc->uwbd.task = kthread_run(uwbd, rc, "STR");
	if (rc->uwbd.task == NULL)
		printk(KERN_ERR "STR"
		       "STR");
	else
		rc->uwbd.pid = rc->uwbd.task->pid;
}