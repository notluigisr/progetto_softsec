TIFFReadRawTile1(TIFF* tif, uint32 tile, void* buf, tmsize_t size, const char* module)
{
	TIFFDirectory *td = &tif->tif_dir;

    if (!_TIFFFillStriles( tif ))
        return ((tmsize_t)(-1));

	assert((tif->tif_flags&TIFF_NOREADRAW)==0);
	if (!isMapped(tif)) {
		tmsize_t cc;

		if (!SeekOK(tif, td->td_stripoffset[tile])) {
			TIFFErrorExt(tif->tif_clientdata, module,
			    "STR",
			    (unsigned long) tif->tif_row,
			    (unsigned long) tif->tif_col,
			    (unsigned long) tile);
			return ((tmsize_t)(-1));
		}
		cc = TIFFReadFile(tif, buf, size);
		if (cc != size) {
#if defined(__WIN32__) && (defined(_MSC_VER) || defined(__MINGW32__))
			TIFFErrorExt(tif->tif_clientdata, module,
	"STR",
				     (unsigned long) tif->tif_row,
				     (unsigned long) tif->tif_col,
				     (unsigned __int64) cc,
				     (unsigned __int64) size);
#else
			TIFFErrorExt(tif->tif_clientdata, module,
	"STR",
				     (unsigned long) tif->tif_row,
				     (unsigned long) tif->tif_col,
				     (unsigned long long) cc,
				     (unsigned long long) size);
#endif
			return ((tmsize_t)(-1));
		}
	} else {
		tmsize_t ma,mb;
		tmsize_t n;
		ma=(tmsize_t)td->td_stripoffset[tile];
		mb=ma+size;
		if (((uint64)ma!=td->td_stripoffset[tile])||(ma>tif->tif_size))
			n=0;
		else if ((mb<ma)||(mb<size)||(mb>tif->tif_size))
			n=tif->tif_size-ma;
		else
			n=size;
		if (n!=size) {
#if defined(__WIN32__) && (defined(_MSC_VER) || defined(__MINGW32__))
			TIFFErrorExt(tif->tif_clientdata, module,
"STR",
				     (unsigned long) tif->tif_row,
				     (unsigned long) tif->tif_col,
				     (unsigned long) tile,
				     (unsigned __int64) n,
				     (unsigned __int64) size);
#else
			TIFFErrorExt(tif->tif_clientdata, module,
"STR",
				     (unsigned long) tif->tif_row,
				     (unsigned long) tif->tif_col,
				     (unsigned long) tile,
				     (unsigned long long) n,
				     (unsigned long long) size);
#endif
			return ((tmsize_t)(-1));
		}
		_TIFFmemcpy(buf, tif->tif_base + ma, size);
	}
	return (size);
}