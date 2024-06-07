static int bmp_read_8bit(gdImagePtr im, gdIOCtxPtr infile, bmp_info_t *info, bmp_hdr_t *header)
{
	int ypos = 0, xpos = 0, row = 0, index = 0;
	int padding = 0;

	if (info->enctype != BMP_BI_RGB && info->enctype != BMP_BI_RLE8) {
		return 1;
	}

	if (!info->numcolors) {
		info->numcolors = 256;
	} else if (info->numcolors < 0 || info->numcolors > 256) {
		return 1;
	}

	if (bmp_read_palette(im, infile, info->numcolors, (info->type == BMP_PALETTE_4))) {
		return 1;
	}

	im->colorsTotal = info->numcolors;

	
	if (gdTell(infile) != header->off) {
		
		if (!gdSeek(infile, header->off)) {
			return 1;
		}
	}

	
	padding = (1 * info->width) % 4;
	if (padding) {
		padding = 4 - padding;
	}

	switch (info->enctype) {
	case BMP_BI_RGB:
		for (ypos = 0; ypos < info->height; ++ypos) {
			if (info->topdown) {
				row = ypos;
			} else {
				row = info->height - ypos - 1;
			}

			for (xpos = 0; xpos < info->width; ++xpos) {
				if (!gdGetByte(&index, infile)) {
					return 1;
				}

				if (im->open[index]) {
					im->open[index] = 0;
				}
				gdImageSetPixel(im, xpos, row, index);
			}
			
			for (xpos = padding; xpos > 0; --xpos) {
				if (!gdGetByte(&index, infile)) {
					return 1;
				}
			}
		}
		break;

	case BMP_BI_RLE8:
		if (bmp_read_rle(im, infile, info)) {
			return 1;
		}
		break;

	default:
		return 1;
	}
	return 0;
}