ldns_characters2buffer_str(ldns_buffer* output,
		size_t amount, const uint8_t* characters)
{
	uint8_t ch;
	while (amount > 0) {
		ch = *characters++;
		if (isprint((int)ch) || ch == '\t') {
			if (ch == '\"' || ch == '\\')
				ldns_buffer_printf(output, "STR", ch);
			else
				ldns_buffer_printf(output, "STR", ch);
		} else {
			ldns_buffer_printf(output, "STR",
                                (unsigned)(uint8_t) ch);
		}
		amount--;
	}
}