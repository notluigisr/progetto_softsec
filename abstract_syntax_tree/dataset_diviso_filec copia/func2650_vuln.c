mbfl_buffer_converter_new2(
	const mbfl_encoding *from,
	const mbfl_encoding *to, 
    int buf_initsz)
{
	mbfl_buffer_converter *convd;

	
	convd = (mbfl_buffer_converter*)mbfl_malloc(sizeof (mbfl_buffer_converter));
	if (convd == NULL) {
		return NULL;
	}

	
	convd->from = from;
	convd->to = to;

	
	convd->filter1 = NULL;
	convd->filter2 = NULL;
	if (mbfl_convert_filter_get_vtbl(convd->from->no_encoding, convd->to->no_encoding) != NULL) {
		convd->filter1 = mbfl_convert_filter_new(convd->from->no_encoding, convd->to->no_encoding, mbfl_memory_device_output, NULL, &convd->device);
	} else {
		convd->filter2 = mbfl_convert_filter_new(mbfl_no_encoding_wchar, convd->to->no_encoding, mbfl_memory_device_output, NULL, &convd->device);
		if (convd->filter2 != NULL) {
			convd->filter1 = mbfl_convert_filter_new(convd->from->no_encoding,
					mbfl_no_encoding_wchar,
					(int (*)(int, void*))convd->filter2->filter_function,
					(int (*)(void*))convd->filter2->filter_flush,
					convd->filter2);
			if (convd->filter1 == NULL) {
				mbfl_convert_filter_delete(convd->filter2);
			}
		}
	}
	if (convd->filter1 == NULL) {
		return NULL;
	}

	mbfl_memory_device_init(&convd->device, buf_initsz, buf_initsz/4);

	return convd;
}