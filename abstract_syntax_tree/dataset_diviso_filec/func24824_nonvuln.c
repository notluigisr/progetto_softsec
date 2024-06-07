static int bmp_read_os2_v2_info(gdIOCtxPtr infile, bmp_info_t *info)
{
	char useless_bytes[24];
	if (
	    !gdGetIntLSB(&info->width, infile) ||
	    !gdGetIntLSB(&info->height, infile) ||
	    !gdGetWordLSB(&info->numplanes, infile) ||
	    !gdGetWordLSB(&info->depth, infile) ||
	    !gdGetIntLSB(&info->enctype, infile) ||
	    !gdGetIntLSB(&info->size, infile) ||
	    !gdGetIntLSB(&info->hres, infile) ||
	    !gdGetIntLSB(&info->vres, infile) ||
	    !gdGetIntLSB(&info->numcolors, infile) ||
	    !gdGetIntLSB(&info->mincolors, infile)
	) {
		return 1;
	}

	
	if (!gdGetBuf(useless_bytes, 24, infile)) {
		return 1;
	}

	
	if (info->height == 0 || info->height == INT_MIN)
		return 1;
	if (info->height < 0) {
		info->topdown = 1;
		info->height = -info->height;
	} else {
		info->topdown = 0;
	}

	info->type = BMP_PALETTE_4;

	
	if (info->width <= 0 || info->numplanes <= 0 || info->depth <= 0 ||
	        info->numcolors < 0 || info->mincolors < 0) {
		return 1;
	}

	return 0;
}