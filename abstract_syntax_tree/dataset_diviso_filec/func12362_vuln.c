PixarLogSetupDecode(TIFF* tif)
{
	static const char module[] = "STR";
	TIFFDirectory *td = &tif->tif_dir;
	PixarLogState* sp = DecoderState(tif);
	tmsize_t tbuf_size;

	assert(sp != NULL);

	
	tif->tif_postdecode = _TIFFNoPostDecode;  

	

	sp->stride = (td->td_planarconfig == PLANARCONFIG_CONTIG ?
	    td->td_samplesperpixel : 1);
	tbuf_size = multiply_ms(multiply_ms(multiply_ms(sp->stride, td->td_imagewidth),
				      td->td_rowsperstrip), sizeof(uint16));
	
	tbuf_size = add_ms(tbuf_size, sizeof(uint16) * sp->stride);
	if (tbuf_size == 0)
		return (0);   
	sp->tbuf = (uint16 *) _TIFFmalloc(tbuf_size);
	if (sp->tbuf == NULL)
		return (0);
	if (sp->user_datafmt == PIXARLOGDATAFMT_UNKNOWN)
		sp->user_datafmt = PixarLogGuessDataFmt(td);
	if (sp->user_datafmt == PIXARLOGDATAFMT_UNKNOWN) {
		TIFFErrorExt(tif->tif_clientdata, module,
			"STR", 
			td->td_bitspersample);
		return (0);
	}

	if (inflateInit(&sp->stream) != Z_OK) {
		TIFFErrorExt(tif->tif_clientdata, module, "STR");
		return (0);
	} else {
		sp->state |= PLSTATE_INIT;
		return (1);
	}
}