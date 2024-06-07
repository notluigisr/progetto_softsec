TIFFWriteDirectoryTagCheckedSshortArray(TIFF* tif, uint32* ndir, TIFFDirEntry* dir, uint16 tag, uint32 count, int16* value)
{
	assert(count<0x80000000);
	assert(sizeof(int16)==2);
	if (tif->tif_flags&TIFF_SWAB)
		TIFFSwabArrayOfShort((uint16*)value,count);
	return(TIFFWriteDirectoryTagData(tif,ndir,dir,tag,TIFF_SSHORT,count,count*2,value));
}