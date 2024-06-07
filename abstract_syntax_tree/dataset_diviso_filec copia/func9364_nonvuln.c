static int input_handlers_seq_show(struct seq_file *seq, void *v)
{
	struct input_handler *handler = container_of(v, struct input_handler, node);
	union input_seq_state *state = (union input_seq_state *)&seq->private;

	seq_printf(seq, "STR", state->pos, handler->name);
	if (handler->filter)
		seq_puts(seq, "STR");
	if (handler->legacy_minors)
		seq_printf(seq, "STR", handler->minor);
	seq_putc(seq, '\n');

	return 0;
}