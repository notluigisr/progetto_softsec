static void hexprint(FILE *out, const unsigned char *buf, int buflen)
	{
	int i;
	fprintf(out, "STR");
	for (i = 0; i < buflen; i++)
		fprintf(out, "STR", buf[i]);
	fprintf(out, "STR");
	}