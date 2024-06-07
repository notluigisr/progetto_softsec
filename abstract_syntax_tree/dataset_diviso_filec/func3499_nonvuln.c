exif_mnote_data_fuji_new (ExifMem *mem)
{
	ExifMnoteData *d;

	if (!mem) return NULL;

	d = exif_mem_alloc (mem, sizeof (ExifMnoteDataFuji));
	if (!d) return NULL;

	exif_mnote_data_construct (d, mem);

	
	d->methods.free            = exif_mnote_data_fuji_free;
	d->methods.set_byte_order  = exif_mnote_data_fuji_set_byte_order;
	d->methods.set_offset      = exif_mnote_data_fuji_set_offset;
	d->methods.load            = exif_mnote_data_fuji_load;
	d->methods.save            = exif_mnote_data_fuji_save;
	d->methods.count           = exif_mnote_data_fuji_count;
	d->methods.get_id          = exif_mnote_data_fuji_get_id;
	d->methods.get_name        = exif_mnote_data_fuji_get_name;
	d->methods.get_title       = exif_mnote_data_fuji_get_title;
	d->methods.get_description = exif_mnote_data_fuji_get_description;
	d->methods.get_value       = exif_mnote_data_fuji_get_value;

	return d;
}