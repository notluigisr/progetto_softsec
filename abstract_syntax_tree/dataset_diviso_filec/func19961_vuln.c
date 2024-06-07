static enum TIFFReadDirEntryErr TIFFReadDirEntryArrayWithLimit(
    TIFF* tif, TIFFDirEntry* direntry, uint32* count, uint32 desttypesize,
    void** value, uint64 maxcount)
{
	int typesize;
	uint32 datasize;
	void* data;
        uint64 target_count64;
	typesize=TIFFDataWidth(direntry->tdir_type);

        target_count64 = (direntry->tdir_count > maxcount) ?
                maxcount : direntry->tdir_count;

	if ((target_count64==0)||(typesize==0))
	{
		*value=0;
		return(TIFFReadDirEntryErrOk);
	}
        (void) desttypesize;

        
	if ((uint64)(2147483647/typesize)<target_count64)
		return(TIFFReadDirEntryErrSizesan);
	if ((uint64)(2147483647/desttypesize)<target_count64)
		return(TIFFReadDirEntryErrSizesan);

	*count=(uint32)target_count64;
	datasize=(*count)*typesize;
	assert((tmsize_t)datasize>0);
	data=_TIFFCheckMalloc(tif, *count, typesize, "STR");
	if (data==0)
		return(TIFFReadDirEntryErrAlloc);
	if (!(tif->tif_flags&TIFF_BIGTIFF))
	{
		if (datasize<=4)
			_TIFFmemcpy(data,&direntry->tdir_offset,datasize);
		else
		{
			enum TIFFReadDirEntryErr err;
			uint32 offset = direntry->tdir_offset.toff_long;
			if (tif->tif_flags&TIFF_SWAB)
				TIFFSwabLong(&offset);
			err=TIFFReadDirEntryData(tif,(uint64)offset,(tmsize_t)datasize,data);
			if (err!=TIFFReadDirEntryErrOk)
			{
				_TIFFfree(data);
				return(err);
			}
		}
	}
	else
	{
		if (datasize<=8)
			_TIFFmemcpy(data,&direntry->tdir_offset,datasize);
		else
		{
			enum TIFFReadDirEntryErr err;
			uint64 offset = direntry->tdir_offset.toff_long8;
			if (tif->tif_flags&TIFF_SWAB)
				TIFFSwabLong8(&offset);
			err=TIFFReadDirEntryData(tif,offset,(tmsize_t)datasize,data);
			if (err!=TIFFReadDirEntryErrOk)
			{
				_TIFFfree(data);
				return(err);
			}
		}
	}
	*value=data;
	return(TIFFReadDirEntryErrOk);
}