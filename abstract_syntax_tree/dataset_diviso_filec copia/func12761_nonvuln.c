static int jas_image_render(jas_image_t *image, float vtlx, float vtly,
  float vsx, float vsy, int vw, int vh, GLshort *vdata)
{
	int i;
	int j;
	int k;
	int x;
	int y;
	int v[3];
	GLshort *vdatap;
	int cmptlut[3];
	int width;
	int height;
	int hs;
	int vs;
	int tlx;
	int tly;

	if ((cmptlut[0] = jas_image_getcmptbytype(image,
	  JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_RGB_R))) < 0 ||
	  (cmptlut[1] = jas_image_getcmptbytype(image,
	  JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_RGB_G))) < 0 ||
	  (cmptlut[2] = jas_image_getcmptbytype(image,
	  JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_RGB_B))) < 0)
		goto error;
	width = jas_image_cmptwidth(image, cmptlut[0]);
	height = jas_image_cmptheight(image, cmptlut[0]);
	tlx = jas_image_cmpttlx(image, cmptlut[0]);
	tly = jas_image_cmpttly(image, cmptlut[0]);
	vs = jas_image_cmptvstep(image, cmptlut[0]);
	hs = jas_image_cmpthstep(image, cmptlut[0]);
	for (i = 1; i < 3; ++i) {
		if (jas_image_cmptwidth(image, cmptlut[i]) != width ||
		  jas_image_cmptheight(image, cmptlut[i]) != height)
			goto error;
	}
	for (i = 0; i < vh; ++i) {
		vdatap = &vdata[(vh - 1 - i) * (4 * vw)];
		for (j = 0; j < vw; ++j) {
			x = vctocc(j, tlx, hs, vtlx, vsx);
			y = vctocc(i, tly, vs, vtly, vsy);
			if (x >= 0 && x < width && y >= 0 && y < height) {
				for (k = 0; k < 3; ++k) {
					v[k] = jas_image_readcmptsample(image, cmptlut[k], x, y);
					v[k] <<= 16 - jas_image_cmptprec(image, cmptlut[k]);
					if (v[k] < 0) {
						v[k] = 0;
					} else if (v[k] > 65535) {
						v[k] = 65535;
					}
				}
			} else {
				v[0] = 0;
				v[1] = 0;
				v[2] = 0;
			}	
			*vdatap++ = v[0];
			*vdatap++ = v[1];
			*vdatap++ = v[2];
			*vdatap++ = 0;
		}
	}
	return 0;
error:
	return -1;
}