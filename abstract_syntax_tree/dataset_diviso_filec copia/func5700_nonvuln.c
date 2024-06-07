static st64 read_sleb128(ulebr *r, ut8 *end) {
	st64 result = 0;
	int bit = 0;
	ut8 byte = 0;
	ut8 *p = r->p;
	do {
		if (p == end) {
			eprintf ("STR");
			break;
		}
		byte = *p++;
		result |= (((st64)(byte & 0x7f)) << bit);
		bit += 7;
	} while (byte & 0x80);
	
	if ((byte & 0x40)) {
		result |= (-1LL) << bit;
	}
	r->p = p;
	return result;
}