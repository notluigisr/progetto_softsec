parse_device(dev_t *pdev, struct archive *a, char *val)
{

	unsigned long numbers[MAX_PACK_ARGS];
	char *p, *dev;
	int argc;
	pack_t *pack;
	dev_t result;
	const char *error = NULL;

	memset(pdev, 0, sizeof(*pdev));
	if ((dev = strchr(val, ',')) != NULL) {
		
		*dev++ = '\0';
		if ((pack = pack_find(val)) == NULL) {
			archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
			    "STR", val);
			return ARCHIVE_WARN;
		}
		argc = 0;
		while ((p = la_strsep(&dev, "STR")) != NULL) {
			if (*p == '\0') {
				archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
				    "STR");
				return ARCHIVE_WARN;
			}
			numbers[argc++] = (unsigned long)mtree_atol(&p);
			if (argc > MAX_PACK_ARGS) {
				archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
				    "STR");
				return ARCHIVE_WARN;
			}
		}
		if (argc < 2) {
			archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
			    "STR");
			return ARCHIVE_WARN;
		}
		result = (*pack)(argc, numbers, &error);
		if (error != NULL) {
			archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
			    "STR", error);
			return ARCHIVE_WARN;
		}
	} else {
		
		result = (dev_t)mtree_atol(&val);
	}
	*pdev = result;
	return ARCHIVE_OK;
#undef MAX_PACK_ARGS
}