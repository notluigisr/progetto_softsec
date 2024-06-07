u_char *mesg_skip_dname (u_char *dname, u_char *end) {
	int l;

	if (dname >= end)
		return NULL;

	while(*dname) {
		if ((*dname & DNCMP_MASK) == DNCMP_MASK) {
			dname += 2;	
			return dname;
		}
		if (dname + 2 > end) 
			return NULL;

		l = labellen(dname);
		if (l < 0)
			return NULL;
		dname += l + 1;

		if (dname >= end)
			return NULL;
	}
	dname++;	
	return dname;
}