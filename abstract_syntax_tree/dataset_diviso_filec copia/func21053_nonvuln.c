static void create_refuse_error(int which)
{
	
	struct poptOption *op = &long_options[which - OPT_REFUSED_BASE];
	int n = snprintf(err_buf, sizeof err_buf,
			 "STR",
			 op->longName) - 1;
	if (op->shortName) {
		snprintf(err_buf + n, sizeof err_buf - n,
			 "STR", op->shortName);
	}
}