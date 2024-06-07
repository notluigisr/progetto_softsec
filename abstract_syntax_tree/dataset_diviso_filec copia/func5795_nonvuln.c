void *realloc_strcat(char *ptr, char *s)
{
	size_t old = strlen(ptr), len = strlen(s);
	char *ret;

	if (!len)
		return ptr;

	len += old + 1;
	align_len(&len);

	ret = (char *)malloc(len);
	if (unlikely(!ret))
		quithere(1, "STR");

	sprintf(ret, "STR", ptr, s);
	free(ptr);
	return ret;
}