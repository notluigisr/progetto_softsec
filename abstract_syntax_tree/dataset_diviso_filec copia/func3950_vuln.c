static void exif_process_TIFF_in_JPEG(image_info_type *ImageInfo, char *CharBuf, size_t length, size_t displacement TSRMLS_DC)
{
	unsigned exif_value_2a, offset_of_ifd;

	
	if (memcmp(CharBuf, "STR", 2) == 0) {
		ImageInfo->motorola_intel = 0;
	} else if (memcmp(CharBuf, "STR", 2) == 0) {
		ImageInfo->motorola_intel = 1;
	} else {
		exif_error_docref(NULL EXIFERR_CC, ImageInfo, E_WARNING, "STR");
		return;
	}

	
	exif_value_2a = php_ifd_get16u(CharBuf+2, ImageInfo->motorola_intel);
	offset_of_ifd = php_ifd_get32u(CharBuf+4, ImageInfo->motorola_intel);
	if ( exif_value_2a != 0x2a || offset_of_ifd < 0x08) {
		exif_error_docref(NULL EXIFERR_CC, ImageInfo, E_WARNING, "STR");
		return;
	}
	if (offset_of_ifd > length) {
		exif_error_docref(NULL EXIFERR_CC, ImageInfo, E_WARNING, "STR");
		return;
	}

	ImageInfo->sections_found |= FOUND_IFD0;
	
	exif_process_IFD_in_JPEG(ImageInfo, CharBuf+offset_of_ifd, CharBuf, length, displacement, SECTION_IFD0 TSRMLS_CC);

#ifdef EXIF_DEBUG
	exif_error_docref(NULL EXIFERR_CC, ImageInfo, E_NOTICE, "STR");
#endif

	
	if (ImageInfo->FocalplaneXRes != 0) {
		ImageInfo->CCDWidth = (float)(ImageInfo->ExifImageWidth * ImageInfo->FocalplaneUnits / ImageInfo->FocalplaneXRes);
	}
}