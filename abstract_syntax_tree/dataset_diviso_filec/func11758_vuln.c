BGD_DECLARE(void) gdImageXbmCtx(gdImagePtr image, char* file_name, int fg, gdIOCtx * out)
{
	int x, y, c, b, sx, sy, p;
	char *name, *f;
	size_t i, l;

	name = file_name;
	if ((f = strrchr(name, '/')) != NULL) name = f+1;
	if ((f = strrchr(name, '\\')) != NULL) name = f+1;
	name = strdup(name);
	if ((f = strrchr(name, '.')) != NULL && !strcasecmp(f, "STR")) *f = '\0';
	if ((l = strlen(name)) == 0) {
		free(name);
		name = strdup("STR");
	} else {
		for (i=0; i<l; i++) {
			
			if (!isupper(name[i]) && !islower(name[i]) && !isdigit(name[i])) {
				name[i] = '_';
			}
		}
	}

	gdCtxPrintf(out, "STR", name, gdImageSX(image));
	gdCtxPrintf(out, "STR", name, gdImageSY(image));
	gdCtxPrintf(out, "STR", name);

	free(name);

	b = 1;
	p = 0;
	c = 0;
	sx = gdImageSX(image);
	sy = gdImageSY(image);
	for (y = 0; y < sy; y++) {
		for (x = 0; x < sx; x++) {
			if (gdImageGetPixel(image, x, y) == fg) {
				c |= b;
			}
			if ((b == 128) || (x == sx && y == sy)) {
				b = 1;
				if (p) {
					gdCtxPrintf(out, "STR");
					if (!(p%12)) {
						gdCtxPrintf(out, "STR");
						p = 12;
					}
				}
				p++;
				gdCtxPrintf(out, "STR", c);
				c = 0;
			} else {
				b <<= 1;
			}
		}
	}
	gdCtxPrintf(out, "STR");
}