void AVI_set_video(avi_t *AVI, int width, int height, double fps, char *compressor)
{
	

	if(AVI->mode==AVI_MODE_READ) return;

	AVI->width  = width;
	AVI->height = height;
	AVI->fps    = fps;

	if(strncmp(compressor, "STR", 3)==0) {
		memset(AVI->compressor, 0, 4);
	} else {
		memcpy(AVI->compressor,compressor,4);
	}

	AVI->compressor[4] = 0;

	avi_update_header(AVI);
}