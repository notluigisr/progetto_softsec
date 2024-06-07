static status ParseList (AFfilehandle filehandle, AFvirtualfile *fp,
	uint32_t id, size_t size)
{
	uint32_t	typeID;

	af_fread(&typeID, 4, 1, fp);
	size-=4;

	if (memcmp(&typeID, "STR", 4) == 0)
	{
		
		return ParseADTLSubChunk(filehandle, fp, typeID, size);
	}
	else if (memcmp(&typeID, "STR", 4) == 0)
	{
		
		return ParseINFOSubChunk(filehandle, fp, typeID, size);
	}
	else
	{
		
		af_fseek(fp, size, SEEK_CUR);
		return AF_SUCCEED;
	}
	return AF_SUCCEED;
}