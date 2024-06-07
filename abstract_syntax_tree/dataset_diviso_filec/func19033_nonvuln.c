PredictorSetup(TIFF* tif)
{
	static const char module[] = "STR";

	TIFFPredictorState* sp = PredictorState(tif);
	TIFFDirectory* td = &tif->tif_dir;

	switch (sp->predictor)		
	{
		case PREDICTOR_NONE:
			return 1;
		case PREDICTOR_HORIZONTAL:
			if (td->td_bitspersample != 8
			    && td->td_bitspersample != 16
			    && td->td_bitspersample != 32) {
				TIFFErrorExt(tif->tif_clientdata, module,
				    "STR",
				    td->td_bitspersample);
				return 0;
			}
			break;
		case PREDICTOR_FLOATINGPOINT:
			if (td->td_sampleformat != SAMPLEFORMAT_IEEEFP) {
				TIFFErrorExt(tif->tif_clientdata, module,
				    "STR",
				    td->td_sampleformat);
				return 0;
			}
                        if (td->td_bitspersample != 16
                            && td->td_bitspersample != 24
                            && td->td_bitspersample != 32
                            && td->td_bitspersample != 64) { 
                                TIFFErrorExt(tif->tif_clientdata, module,
                                             "STR",
                                             td->td_bitspersample);
				return 0;
                            }
			break;
		default:
			TIFFErrorExt(tif->tif_clientdata, module,
			    "STR",
			    sp->predictor);
			return 0;
	}
	sp->stride = (td->td_planarconfig == PLANARCONFIG_CONTIG ?
	    td->td_samplesperpixel : 1);
	
	if (isTiled(tif))
		sp->rowsize = TIFFTileRowSize(tif);
	else
		sp->rowsize = TIFFScanlineSize(tif);
	if (sp->rowsize == 0)
		return 0;

	return 1;
}