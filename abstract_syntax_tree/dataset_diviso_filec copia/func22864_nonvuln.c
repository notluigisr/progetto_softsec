agoo_ws_calc_len(agooCon c, uint8_t *buf, size_t cnt) {
    uint8_t	*b = buf;
    bool	is_masked;
    uint64_t	plen;

    if (0 == (0x80 & *b)) {
	agoo_log_cat(&agoo_error_cat, "STR", (unsigned long long)c->id);
	return -1;
    }
    b++;
    is_masked = 0x80 & *b;
    plen = 0x7F & *b;
    if (cnt < 3) {
	return 0; 
    }
    b++;
    if (126 == plen) {
	if (cnt < 5) {
	    return 0; 
	}
	plen = *b++;
	plen = (plen << 8) | *b++;
    } else if (127 == plen) {
	if (c->bcnt < 11) {
	    return 0; 
	}
	plen = *b++;
	plen = (plen << 8) | *b++;
	plen = (plen << 8) | *b++;
	plen = (plen << 8) | *b++;
	plen = (plen << 8) | *b++;
	plen = (plen << 8) | *b++;
	plen = (plen << 8) | *b++;
	plen = (plen << 8) | *b++;
    }
    return (long)(b - buf) + (is_masked ? 4 : 0) + plen;
}