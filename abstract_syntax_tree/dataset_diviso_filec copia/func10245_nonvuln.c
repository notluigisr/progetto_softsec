static int exif_scan_FILE_header(image_info_type *ImageInfo TSRMLS_DC)
{
	unsigned char file_header[8];
	int ret = FALSE;

	ImageInfo->FileType = IMAGE_FILETYPE_UNKNOWN;

	if (ImageInfo->FileSize >= 2) {
		php_stream_seek(ImageInfo->infile, 0, SEEK_SET);
		if (php_stream_read(ImageInfo->infile, (char*)file_header, 2) != 2) {
			return FALSE;
		}
		if ((file_header[0]==0xff) && (file_header[1]==M_SOI)) {
			ImageInfo->FileType = IMAGE_FILETYPE_JPEG;
			if (exif_scan_JPEG_header(ImageInfo TSRMLS_CC)) {
				ret = TRUE;
			} else {
				exif_error_docref(NULL EXIFERR_CC, ImageInfo, E_WARNING, "STR");
			}
		} else if (ImageInfo->FileSize >= 8) {
			if (php_stream_read(ImageInfo->infile, (char*)(file_header+2), 6) != 6) {
				return FALSE;
			}
			if (!memcmp(file_header, "STR", 4)) {
				ImageInfo->FileType = IMAGE_FILETYPE_TIFF_II;
				ImageInfo->motorola_intel = 0;
#ifdef EXIF_DEBUG
				exif_error_docref(NULL EXIFERR_CC, ImageInfo, E_NOTICE, "STR");
#endif
				ImageInfo->sections_found |= FOUND_IFD0;
				if (exif_process_IFD_in_TIFF(ImageInfo,
											 php_ifd_get32u(file_header + 4, ImageInfo->motorola_intel),
											 SECTION_IFD0 TSRMLS_CC)) {
					ret = TRUE;
				} else {
					exif_error_docref(NULL EXIFERR_CC, ImageInfo, E_WARNING, "STR");
				}
			} else if (!memcmp(file_header, "STR", 4)) {
				ImageInfo->FileType = IMAGE_FILETYPE_TIFF_MM;
				ImageInfo->motorola_intel = 1;
#ifdef EXIF_DEBUG
				exif_error_docref(NULL EXIFERR_CC, ImageInfo, E_NOTICE, "STR");
#endif
				ImageInfo->sections_found |= FOUND_IFD0;
				if (exif_process_IFD_in_TIFF(ImageInfo,
											 php_ifd_get32u(file_header + 4, ImageInfo->motorola_intel),
											 SECTION_IFD0 TSRMLS_CC)) {
					ret = TRUE;
				} else {
					exif_error_docref(NULL EXIFERR_CC, ImageInfo, E_WARNING, "STR");
				}
			} else {
				exif_error_docref(NULL EXIFERR_CC, ImageInfo, E_WARNING, "STR");
				return FALSE;
			}
		}
	} else {
		exif_error_docref(NULL EXIFERR_CC, ImageInfo, E_WARNING, "STR", ImageInfo->FileSize);
	}
	return ret;
}