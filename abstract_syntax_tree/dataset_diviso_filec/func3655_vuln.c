LogLuvSetupEncode(TIFF* tif)
{
	static const char module[] = "STR";
	LogLuvState* sp = EncoderState(tif);
	TIFFDirectory* td = &tif->tif_dir;

	switch (td->td_photometric) {
	case PHOTOMETRIC_LOGLUV:
		if (!LogLuvInitState(tif))
			break;
		if (td->td_compression == COMPRESSION_SGILOG24) {
			tif->tif_encoderow = LogLuvEncode24;
			switch (sp->user_datafmt) {
			case SGILOGDATAFMT_FLOAT:
				sp->tfunc = Luv24fromXYZ;
				break;
			case SGILOGDATAFMT_16BIT:
				sp->tfunc = Luv24fromLuv48;  
				break;
			case SGILOGDATAFMT_RAW:
				break;
			default:
				goto notsupported;
			}
		} else {
			tif->tif_encoderow = LogLuvEncode32;  
			switch (sp->user_datafmt) {
			case SGILOGDATAFMT_FLOAT:
				sp->tfunc = Luv32fromXYZ;  
				break;
			case SGILOGDATAFMT_16BIT:
				sp->tfunc = Luv32fromLuv48;  
				break;
			case SGILOGDATAFMT_RAW:
				break;
			default:
				goto notsupported;
			}
		}
		break;
	case PHOTOMETRIC_LOGL:
		if (!LogL16InitState(tif))
			break;
		tif->tif_encoderow = LogL16Encode;  
		switch (sp->user_datafmt) {
		case SGILOGDATAFMT_FLOAT:
			sp->tfunc = L16fromY;
			break;
		case SGILOGDATAFMT_16BIT:
			break;
		default:
			goto notsupported;
		}
		break;
	default:
		TIFFErrorExt(tif->tif_clientdata, module,
		    "STR",
		    td->td_photometric, "STR");
		break;
	}
	return (1);
notsupported:
	TIFFErrorExt(tif->tif_clientdata, module,
	    "STR",
	    td->td_photometric == PHOTOMETRIC_LOGL ? "STR");
	return (0);
}