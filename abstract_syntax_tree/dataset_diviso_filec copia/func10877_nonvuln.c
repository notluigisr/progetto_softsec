static void ms_adpcm_decompress_describe (_AFmoduleinst *i)
{

	i->outc->f.compressionType = AF_COMPRESSION_NONE;
	i->outc->f.compressionParams = AU_NULL_PVLIST;
}