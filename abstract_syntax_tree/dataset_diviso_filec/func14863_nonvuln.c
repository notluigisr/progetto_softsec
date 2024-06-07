TIFFWriteDirectoryTagCheckedFloat(TIFF* tif, uint32* ndir, TIFFDirEntry* dir, uint16 tag, float value)
{
	float m;
	assert(sizeof(float)==4);
	m=value;
	TIFFCvtNativeToIEEEFloat(tif,1,&m);
	if (tif->tif_flags&TIFF_SWAB)
		TIFFSwabFloat(&m);
	return(TIFFWriteDirectoryTagData(tif,ndir,dir,tag,TIFF_FLOAT,1,4,&m));
}