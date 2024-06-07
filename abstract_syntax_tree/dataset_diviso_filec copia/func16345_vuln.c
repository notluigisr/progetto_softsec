MYSOFA_EXPORT struct MYSOFA_HRTF* mysofa_load(const char *filename, int *err) {
	struct READER reader;
	struct MYSOFA_HRTF *hrtf = NULL;

	if (filename == NULL)
		filename = CMAKE_INSTALL_PREFIX "STR";

	if (strcmp(filename, "STR"))
		reader.fhd = fopen(filename, "STR");
	else
		reader.fhd = stdin;

	if (!reader.fhd) {
		log("STR", filename);
		*err = errno;
		return NULL;
	}
	reader.gcol = NULL;
	reader.all = NULL;

	*err = superblockRead(&reader, &reader.superblock);

	if (!*err) {
		hrtf = getHrtf(&reader, err);
	}

	superblockFree(&reader, &reader.superblock);
	gcolFree(reader.gcol);
	if (strcmp(filename, "STR"))
		fclose(reader.fhd);

	return hrtf;
}