void security_task_getsecid(struct task_struct *p, u32 *secid)
{
	security_ops->task_getsecid(p, secid);
}