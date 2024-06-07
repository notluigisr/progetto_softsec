mbfl_strlen(mbfl_string *string)
{
	int len, n, m, k;
	unsigned char *p;
	const unsigned char *mbtab;
	const mbfl_encoding *encoding;

	encoding = mbfl_no2encoding(string->no_encoding);
	if (encoding == NULL || string == NULL) {
		return -1;
	}

	len = 0;
	if (encoding->flag & MBFL_ENCTYPE_SBCS) {
		len = string->len;
	} else if (encoding->flag & (MBFL_ENCTYPE_WCS2BE | MBFL_ENCTYPE_WCS2LE)) {
		len = string->len/2;
	} else if (encoding->flag & (MBFL_ENCTYPE_WCS4BE | MBFL_ENCTYPE_WCS4LE)) {
		len = string->len/4;
	} else if (encoding->mblen_table != NULL) {
		mbtab = encoding->mblen_table;
		n = 0;
		p = string->val;
		k = string->len;
		
		if (p != NULL) {
			while (n < k) {
				m = mbtab[*p];
				n += m;
				p += m;
				len++;
			};
		}
	} else {
		
		mbfl_convert_filter *filter = mbfl_convert_filter_new(
		  string->no_encoding, 
		  mbfl_no_encoding_wchar,
		  filter_count_output, 0, &len);
		if (filter == NULL) {
			return -1;
		}
		
		n = string->len;
		p = string->val;
		if (p != NULL) {
			while (n > 0) {
				(*filter->filter_function)(*p++, filter);
				n--;
			}
		}
		mbfl_convert_filter_delete(filter);
	}

	return len;
}