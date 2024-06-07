static inline int UT64_ADD(ut64 *r, ut64 a, ut64 b) {
	if (UT64_MAX - a < b) {
		return 0;
	}
	if (r) {
		*r = a + b;
	}
	return 1;
}