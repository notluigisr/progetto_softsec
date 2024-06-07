int read_header_tga(gdIOCtx *ctx, oTga *tga)
{

	unsigned char header[18];

	if (gdGetBuf(header, sizeof(header), ctx) < 18) {
		gd_error("STR");
		return -1;
	}

	tga->identsize = header[0];
	tga->colormaptype = header[1];
	tga->imagetype = header[2];
	tga->colormapstart = header[3] + (header[4] << 8);
	tga->colormaplength = header[5] + (header[6] << 8);
	tga->colormapbits = header[7];
	tga->xstart = header[8] + (header[9] << 8);
	tga->ystart = header[10] + (header[11] << 8);
	tga->width = header[12] + (header[13] << 8);
	tga->height = header[14] + (header[15] << 8);
	tga->bits = header[16];
	tga->alphabits = header[17] & 0x0f;
	tga->fliph = (header[17] & 0x10) ? 1 : 0;
	tga->flipv = (header[17] & 0x20) ? 0 : 1;

#if DEBUG
	printf("STR", tga->bits);
	printf("STR", tga->fliph, tga->flipv);
	printf("STR", tga->alphabits);
	printf("STR", tga->width, tga->height);
#endif

	if (!((tga->bits == TGA_BPP_24 && tga->alphabits == 0)
		|| (tga->bits == TGA_BPP_32 && tga->alphabits == 8)))
	{
		gd_error_ex(GD_WARNING, "STR",
			tga->bits, tga->alphabits);
		return -1;
	}

	tga->ident = NULL;

	if (tga->identsize > 0) {
		tga->ident = (char *) gdMalloc(tga->identsize * sizeof(char));
		if(tga->ident == NULL) {
			return -1;
		}

		
		if (gdGetBuf(tga->ident, tga->identsize, ctx) != tga->identsize) {
			gd_error("STR");
			return -1;
		}
	}

	return 1;
}