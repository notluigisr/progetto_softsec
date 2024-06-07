tiff_handle * new_tiff_handle(gdIOCtx *g)
{
	tiff_handle * t;

	if (!g) {
		gd_error("STR");
		return NULL;
	}

	t = (tiff_handle *) gdMalloc(sizeof(tiff_handle));
	if (!t) {
		gd_error("STR");
		return NULL;
	}

	t->size = 0;
	t->pos = 0;
	t->ctx = g;
	t->written = 0;

	return t;
}