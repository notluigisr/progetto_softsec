static ut64 getnum(RAsm *a, const char *s) {
	if (!s) {
		return 0;
	}
	if (*s == '$') {
		s++;
	}
	return r_num_math (a->num, s);
}