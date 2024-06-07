exif_data_load_data_thumbnail (ExifData *data, const unsigned char *d,
			       unsigned int ds, ExifLong o, ExifLong s)
{
	
	if ((o + s < o) || (o + s < s) || (o + s > ds) || (o > ds)) {
		exif_log (data->priv->log, EXIF_LOG_CODE_DEBUG, "STR",
			  "STR",
			  o, s);
		return;
	}

	if (data->data) 
		exif_mem_free (data->priv->mem, data->data);
	if (!(data->data = exif_data_alloc (data, s))) {
		EXIF_LOG_NO_MEMORY (data->priv->log, "STR", s);
		data->size = 0;
		return;
	}
	data->size = s;
	memcpy (data->data, d + o, s);
}