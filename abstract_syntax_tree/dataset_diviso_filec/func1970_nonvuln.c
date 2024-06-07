char *format_flags(char *buf, char *end, unsigned long flags,
					const struct trace_print_flags *names)
{
	unsigned long mask;
	const struct printf_spec strspec = {
		.field_width = -1,
		.precision = -1,
	};
	const struct printf_spec numspec = {
		.flags = SPECIAL|SMALL,
		.field_width = -1,
		.precision = -1,
		.base = 16,
	};

	for ( ; flags && names->name; names++) {
		mask = names->mask;
		if ((flags & mask) != mask)
			continue;

		buf = string(buf, end, names->name, strspec);

		flags &= ~mask;
		if (flags) {
			if (buf < end)
				*buf = '|';
			buf++;
		}
	}

	if (flags)
		buf = number(buf, end, flags, numspec);

	return buf;
}