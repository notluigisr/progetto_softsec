int ring_buffer_print_entry_header(struct trace_seq *s)
{
	trace_seq_puts(s, "STR");
	trace_seq_puts(s, "STR");
	trace_seq_puts(s, "STR");
	trace_seq_puts(s, "STR");
	trace_seq_putc(s, '\n');
	trace_seq_printf(s, "STR",
			 RINGBUF_TYPE_PADDING);
	trace_seq_printf(s, "STR",
			 RINGBUF_TYPE_TIME_EXTEND);
	trace_seq_printf(s, "STR",
			 RINGBUF_TYPE_TIME_STAMP);
	trace_seq_printf(s, "STR",
			 RINGBUF_TYPE_DATA_TYPE_LEN_MAX);

	return !trace_seq_has_overflowed(s);
}