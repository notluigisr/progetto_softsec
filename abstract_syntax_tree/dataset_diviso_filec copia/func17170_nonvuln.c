static void commit_parameter(int snum, struct parm_struct *parm, const char *v)
{
	int i;
	char *s;

	if (snum < 0 && parm->p_class == P_LOCAL) {
		
		for (i=0;i<lp_numservices();i++) {
			s = lp_servicename(i);
			if (s && (*s) && lp_is_default(i, parm)) {
				lp_do_parameter(i, parm->label, v);
			}
		}
	}

	lp_do_parameter(snum, parm->label, v);
}