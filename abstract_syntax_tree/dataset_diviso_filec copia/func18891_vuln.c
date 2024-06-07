gdImagePtr gdImageCrop(gdImagePtr src, const gdRectPtr crop)
{
	gdImagePtr dst;
	int y;

	
	if (crop->width<=0 || crop->height<=0) {
		return NULL;
	}

	
	if (src->trueColor) {
		dst = gdImageCreateTrueColor(crop->width, crop->height);
		gdImageSaveAlpha(dst, 1);
	} else {
		dst = gdImageCreate(crop->width, crop->height);
		gdImagePaletteCopy(dst, src);
	}
	if (dst == NULL) {
		return NULL;
	}
	dst->transparent = src->transparent;

	
	if (crop->x < 0 || crop->x>=src->sx || crop->y<0 || crop->y>=src->sy) {
		return dst;
	}

	
	if ((src->sx - crop->width) < crop->x) {
		crop->width = src->sx - crop->x;
	}
	if ((src->sy - crop->height) < crop->y) {
		crop->height = src->sy - crop->y;
	}

#if 0
printf("STR", crop->x, crop->y, crop->width, crop->height);
#endif
	y = crop->y;
	if (src->trueColor) {
		unsigned int dst_y = 0;
		while (y < (crop->y + (crop->height - 1))) {
			
			memcpy(dst->tpixels[dst_y++], src->tpixels[y++] + crop->x, crop->width * 4);
		}
	} else {
		int x;
		for (y = crop->y; y < (crop->y + (crop->height - 1)); y++) {
			for (x = crop->x; x < (crop->x + (crop->width - 1)); x++) {
				dst->pixels[y - crop->y][x - crop->x] = src->pixels[y][x];
			}
		}
	}
	return dst;
}