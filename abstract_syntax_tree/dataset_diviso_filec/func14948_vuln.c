static void exif_process_CME (image_info_type *image_info, char *value, size_t length)
{
	if (length>3) {
		switch(value[2]) {
			case 0:
				exif_iif_add_tag(image_info, SECTION_COMMENT, "STR", TAG_COMPUTED_VALUE, TAG_FMT_UNDEFINED, length, value);
				break;
			case 1:
				exif_iif_add_tag(image_info, SECTION_COMMENT, "STR", TAG_COMPUTED_VALUE, TAG_FMT_STRING, length, value);
				break;
			default:
				php_error_docref(NULL, E_NOTICE, "STR");
				break;
		}
	} else {
		exif_iif_add_tag(image_info, SECTION_COMMENT, "STR", TAG_COMPUTED_VALUE, TAG_FMT_UNDEFINED, 0, NULL);
		php_error_docref(NULL, E_NOTICE, "STR");
	}
}