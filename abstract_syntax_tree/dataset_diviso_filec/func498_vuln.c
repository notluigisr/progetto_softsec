static void exif_thumbnail_extract(image_info_type *ImageInfo, char *offset, size_t length TSRMLS_DC) {
	if (ImageInfo->Thumbnail.data) {
		exif_error_docref("STR");
		return; 
	}
	if (!ImageInfo->read_thumbnail)	{
		return; 
	}
	
	if (ImageInfo->Thumbnail.size >= 65536
	 || ImageInfo->Thumbnail.size <= 0
	 || ImageInfo->Thumbnail.offset <= 0
	) {
		exif_error_docref(NULL EXIFERR_CC, ImageInfo, E_WARNING, "STR");
		return;
	}
	
	if ((ImageInfo->Thumbnail.offset + ImageInfo->Thumbnail.size) > length) {
		EXIF_ERRLOG_THUMBEOF(ImageInfo)
		return;
	}
	ImageInfo->Thumbnail.data = estrndup(offset + ImageInfo->Thumbnail.offset, ImageInfo->Thumbnail.size);
	exif_thumbnail_build(ImageInfo TSRMLS_CC);
}