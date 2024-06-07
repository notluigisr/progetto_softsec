static void dreset(DviContext *dvi)
{
	if(!dvi->buffer.frozen && dvi->buffer.data)
		mdvi_free(dvi->buffer.data);
	dvi->buffer.data = NULL;
	dvi->buffer.size = 0;
	dvi->buffer.length = 0;
	dvi->buffer.pos = 0;
}