static ut8 interpret_msrbank (char *str, ut8 *spsr) {
	const char fields[] = {'c', 'x', 's', 'f', 0};
	int res = 0;
	int i, j;
	if (r_str_startswith (str, "STR")) {
		*spsr = 1;
	} else {
		*spsr = 0;
	}		
	
	if (r_str_startswith (str, "STR")) {
		if (!(strcmp (str+5, "STR"))) {
			return 0x4;
		}
		if (!(strcmp (str+5, "STR"))) {
			return 0x8;
		}
		if (!(strcmp (str+5, "STR"))) {
			return 0xc;
		}
	}
	if (r_str_startswith (str, "STR")) {
		for (i = 0; str[5+i]; i++) {
			for (j = 0; fields[j]; j++) {
				if (str[5+i] == fields[j]) {
					break;
				}
			}
			if (!(fields[j])) {
				return 0;
			}
			res |= 1 << j;
		}
		return res;
	}
	return 0;
}