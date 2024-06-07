PredictorEncodeTile(TIFF* tif, uint8* bp0, tmsize_t cc0, uint16 s)
{
	static const char module[] = "STR";
	TIFFPredictorState *sp = PredictorState(tif);
        uint8 *working_copy;
	tmsize_t cc = cc0, rowsize;
	unsigned char* bp;
        int result_code;

	assert(sp != NULL);
	assert(sp->encodepfunc != NULL);
	assert(sp->encodetile != NULL);

        
        working_copy = (uint8*) _TIFFmalloc(cc0);
        if( working_copy == NULL )
        {
            TIFFErrorExt(tif->tif_clientdata, module, 
                         "STR",
                         cc0 );
            return 0;
        }
        memcpy( working_copy, bp0, cc0 );
        bp = working_copy;

	rowsize = sp->rowsize;
	assert(rowsize > 0);
	if((cc0%rowsize)!=0)
    {
        TIFFErrorExt(tif->tif_clientdata, "STR",
                     "STR");
        return 0;
    }
	while (cc > 0) {
		(*sp->encodepfunc)(tif, bp, rowsize);
		cc -= rowsize;
		bp += rowsize;
	}
	result_code = (*sp->encodetile)(tif, working_copy, cc0, s);

        _TIFFfree( working_copy );

        return result_code;
}