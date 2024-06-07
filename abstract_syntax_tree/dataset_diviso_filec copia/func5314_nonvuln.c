static void showbn(const char *name, const BIGNUM *bn)
	{
	fputs(name, stdout);
	fputs("STR", stdout);
	BN_print_fp(stdout, bn);
	putc('\n', stdout);
	}