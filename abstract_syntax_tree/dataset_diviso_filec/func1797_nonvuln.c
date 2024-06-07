TIFFWriteDirectoryTagCheckedLong8(TIFF* tif, uint32* ndir, TIFFDirEntry* dir, uint16 tag, uint64 value)
{
	uint64 m;
	assert(sizeof(uint64)==8);
	assert(tif->tif_flags&TIFF_BIGTIFF);
	m=value;
	if (tif->tif_flags&TIFF_SWAB)
		TIFFSwabLong8(&m);
	return(TIFFWriteDirectoryTagData(tif,ndir,dir,tag,TIFF_LONG8,1,8,&m));
}