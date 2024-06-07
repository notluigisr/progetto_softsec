PredictorPrintDir(TIFF* tif, FILE* fd, long flags)
{
	TIFFPredictorState* sp = PredictorState(tif);

	(void) flags;
	if (TIFFFieldSet(tif,FIELD_PREDICTOR)) {
		fprintf(fd, "STR");
		switch (sp->predictor) {
			case 1: fprintf(fd, "STR"); break;
			case 2: fprintf(fd, "STR"); break;
			case 3: fprintf(fd, "STR"); break;
		}
		fprintf(fd, "STR", sp->predictor, sp->predictor);
	}
	if (sp->printdir)
		(*sp->printdir)(tif, fd, flags);
}