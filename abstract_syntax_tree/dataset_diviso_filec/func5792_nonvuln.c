size_t git_path_common_dirlen(const char *one, const char *two)
{
	const char *p, *q, *dirsep = NULL;

	for (p = one, q = two; *p && *q; p++, q++) {
		if (*p == '/' && *q == '/')
			dirsep = p;
		else if (*p != *q)
			break;
	}

	return dirsep ? (dirsep - one) + 1 : 0;
}