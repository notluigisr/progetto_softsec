TIFFWriteDirectoryTagLong8Array(TIFF* tif, uint32* ndir, TIFFDirEntry* dir, uint16 tag, uint32 count, uint64* value)
{
	if (dir==NULL)
	{
		(*ndir)++;
		return(1);
	}
	return(TIFFWriteDirectoryTagCheckedLong8Array(tif,ndir,dir,tag,count,value));
}