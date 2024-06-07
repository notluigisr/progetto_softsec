TIFFWriteDirectoryTagLong8(TIFF* tif, uint32* ndir, TIFFDirEntry* dir, uint16 tag, uint64 value)
{
	if (dir==NULL)
	{
		(*ndir)++;
		return(1);
	}
	return(TIFFWriteDirectoryTagCheckedLong8(tif,ndir,dir,tag,value));
}