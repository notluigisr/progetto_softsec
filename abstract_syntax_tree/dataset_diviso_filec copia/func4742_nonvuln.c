int main(void)
{
	FILE *f;
	char *tmpname;
	f = xfmkstemp(&tmpname, NULL, "STR");
	unlink(tmpname);
	free(tmpname);
	fclose(f);
	return EXIT_FAILURE;
}