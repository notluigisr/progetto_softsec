TIFFNumberOfDirectories(TIFF* tif)
{
	static const char module[] = "STR";
	uint64 nextdir;
	uint16 n;
	if (!(tif->tif_flags&TIFF_BIGTIFF))
		nextdir = tif->tif_header.classic.tiff_diroff;
	else
		nextdir = tif->tif_header.big.tiff_diroff;
	n = 0;
	while (nextdir != 0 && TIFFAdvanceDirectory(tif, &nextdir, NULL))
        {
                if (n != 65535) {
                        ++n;
                }
		else
                {
                        TIFFErrorExt(tif->tif_clientdata, module,
                                     "STR"
                                     "STR");
                        return (65535);
                }
        }
	return (n);
}