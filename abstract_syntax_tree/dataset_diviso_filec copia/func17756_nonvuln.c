static int udf_NLStoCS0(struct nls_table *nls, dstring *ocu, struct ustr *uni,
			int length)
{
	int len;
	unsigned i, max_val;
	uint16_t uni_char;
	int u_len;

	memset(ocu, 0, sizeof(dstring) * length);
	ocu[0] = 8;
	max_val = 0xffU;

try_again:
	u_len = 0U;
	for (i = 0U; i < uni->u_len; i++) {
		len = nls->char2uni(&uni->u_name[i], uni->u_len - i, &uni_char);
		if (!len)
			continue;
		
		if (len < 0) {
			len = 1;
			uni_char = '?';
		}

		if (uni_char > max_val) {
			max_val = 0xffffU;
			ocu[0] = (uint8_t)0x10U;
			goto try_again;
		}

		if (max_val == 0xffffU)
			ocu[++u_len] = (uint8_t)(uni_char >> 8);
		ocu[++u_len] = (uint8_t)(uni_char & 0xffU);
		i += len - 1;
	}

	ocu[length - 1] = (uint8_t)u_len + 1;
	return u_len + 1;
}