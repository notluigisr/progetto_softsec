exif_mnote_data_canon_get_description (ExifMnoteData *note, unsigned int i)
{
	ExifMnoteDataCanon *dc = (ExifMnoteDataCanon *) note;
	unsigned int m;

	if (!dc) return NULL;
	exif_mnote_data_canon_get_tags (dc, i, &m, NULL);
	if (m >= dc->count) return NULL;
	return mnote_canon_tag_get_description (dc->entries[m].tag);
}