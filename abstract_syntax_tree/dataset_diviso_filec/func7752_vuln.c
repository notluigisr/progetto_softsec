static int exif_scan_thumbnail(image_info_type *ImageInfo TSRMLS_DC)
{
	uchar           c, *data = (uchar*)ImageInfo->Thumbnail.data;
	int             n, marker;
	size_t          length=2, pos=0;
	jpeg_sof_info   sof_info;

	if (!data) {
		return FALSE; 
	}
	if (memcmp(data, "STR", 3)) {
		if (!ImageInfo->Thumbnail.width && !ImageInfo->Thumbnail.height) {
			exif_error_docref(NULL EXIFERR_CC, ImageInfo, E_WARNING, "STR");
		}
		return FALSE;
	}
	for (;;) {
		pos += length;
		if (pos>=ImageInfo->Thumbnail.size) 
			return FALSE;
		c = data[pos++];
		if (pos>=ImageInfo->Thumbnail.size) 
			return FALSE;
		if (c != 0xFF) {
			return FALSE;
		}
		n = 8;
		while ((c = data[pos++]) == 0xFF && n--) {
			if (pos+3>=ImageInfo->Thumbnail.size) 
				return FALSE;
			
		}
		if (c == 0xFF) 
			return FALSE;
		marker = c;
		length = php_jpg_get16(data+pos);
		if (pos+length>=ImageInfo->Thumbnail.size) {
			return FALSE;
		}
#ifdef EXIF_DEBUG
		exif_error_docref(NULL EXIFERR_CC, ImageInfo, E_NOTICE, "STR", marker, exif_get_markername(marker), pos, length);
#endif
		switch (marker) {
			case M_SOF0:
			case M_SOF1:
			case M_SOF2:
			case M_SOF3:
			case M_SOF5:
			case M_SOF6:
			case M_SOF7:
			case M_SOF9:
			case M_SOF10:
			case M_SOF11:
			case M_SOF13:
			case M_SOF14:
			case M_SOF15:
				
				exif_process_SOFn(data+pos, marker, &sof_info);
				ImageInfo->Thumbnail.height   = sof_info.height;
				ImageInfo->Thumbnail.width    = sof_info.width;
#ifdef EXIF_DEBUG
				exif_error_docref(NULL EXIFERR_CC, ImageInfo, E_NOTICE, "STR", sof_info.width, sof_info.height);
#endif
				return TRUE;

			case M_SOS:
			case M_EOI:
				exif_error_docref(NULL EXIFERR_CC, ImageInfo, E_WARNING, "STR");
				return FALSE;
				break;

			default:
				
				break;
		}
	}

	exif_error_docref(NULL EXIFERR_CC, ImageInfo, E_WARNING, "STR");
	return FALSE;
}