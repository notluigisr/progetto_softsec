BGD_DECLARE(void) gdImageGifAnimAdd(gdImagePtr im, FILE *outFile, int LocalCM,
                                    int LeftOfs, int TopOfs, int Delay,
                                    int Disposal, gdImagePtr previm)
{
	gdIOCtx *out = gdNewFileCtx(outFile);
	if (out == NULL) return;
	gdImageGifAnimAddCtx(im, out, LocalCM, LeftOfs, TopOfs, Delay, Disposal, previm);
	out->gd_free(out);
}