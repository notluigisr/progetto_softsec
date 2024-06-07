int ring_buffer_print_page_header(struct trace_seq *s)
{
	struct buffer_data_page field;

	trace_seq_printf(s, "STR"
			 "STR",
			 (unsigned int)sizeof(field.time_stamp),
			 (unsigned int)is_signed_type(u64));

	trace_seq_printf(s, "STR"
			 "STR",
			 (unsigned int)offsetof(typeof(field), commit),
			 (unsigned int)sizeof(field.commit),
			 (unsigned int)is_signed_type(long));

	trace_seq_printf(s, "STR"
			 "STR",
			 (unsigned int)offsetof(typeof(field), commit),
			 1,
			 (unsigned int)is_signed_type(long));

	trace_seq_printf(s, "STR"
			 "STR",
			 (unsigned int)offsetof(typeof(field), data),
			 (unsigned int)BUF_PAGE_SIZE,
			 (unsigned int)is_signed_type(char));

	return !trace_seq_has_overflowed(s);
}