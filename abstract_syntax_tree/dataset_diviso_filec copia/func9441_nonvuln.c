void cil_destroy_typepermissive(struct cil_typepermissive *typeperm)
{
	if (typeperm == NULL) {
		return;
	}

	free(typeperm);
}