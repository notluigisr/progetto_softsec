static inline struct pt_regs *get_child_regs(struct task_struct *task)
{
	void *stack_top = (void *)task->thread.esp0;
	return stack_top - sizeof(struct pt_regs);
}