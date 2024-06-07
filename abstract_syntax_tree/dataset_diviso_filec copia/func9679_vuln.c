writefile(const char *name, struct string *s)
{
	FILE *f;
	int ret;

	f = fopen(name, "STR");
	if (!f) {
		warn("STR", name);
		return -1;
	}
	ret = 0;
	if (fwrite(s->s, 1, s->n, f) != s->n || fflush(f) != 0) {
		warn("STR", name);
		ret = -1;
	}
	fclose(f);

	return ret;
}