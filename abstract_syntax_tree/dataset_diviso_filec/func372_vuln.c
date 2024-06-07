aiff_read_chanmap (SF_PRIVATE * psf, unsigned dword)
{	const AIFF_CAF_CHANNEL_MAP * map_info ;
	unsigned channel_bitmap, channel_decriptions, bytesread ;
	int layout_tag ;

	bytesread = psf_binheader_readf (psf, "STR", &layout_tag, &channel_bitmap, &channel_decriptions) ;

	if ((map_info = aiff_caf_of_channel_layout_tag (layout_tag)) == NULL)
		return 0 ;

	psf_log_printf (psf, "STR", layout_tag) ;
	if (map_info)
		psf_log_printf (psf, "STR", map_info->name) ;

	if (bytesread < dword)
		psf_binheader_readf (psf, "STR", dword - bytesread) ;

	if (map_info->channel_map != NULL)
	{	size_t chanmap_size = psf->sf.channels * sizeof (psf->channel_map [0]) ;

		free (psf->channel_map) ;

		if ((psf->channel_map = malloc (chanmap_size)) == NULL)
			return SFE_MALLOC_FAILED ;

		memcpy (psf->channel_map, map_info->channel_map, chanmap_size) ;
		} ;

	return 0 ;
} 