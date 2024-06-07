static void ima_adpcm_run_pull (_AFmoduleinst *module)
{
	ima_adpcm_data	*d = (ima_adpcm_data *) module->modspec;
	AFframecount	frames2read = module->outc->nframes;
	AFframecount	nframes = 0;
	int		i, framesPerBlock, blockCount;
	ssize_t		blocksRead, bytesDecoded;

	framesPerBlock = d->samplesPerBlock / d->track->f.channelCount;
	assert(module->outc->nframes % framesPerBlock == 0);
	blockCount = module->outc->nframes / framesPerBlock;

	
	blocksRead = af_fread(module->inc->buf, d->blockAlign, blockCount, d->fh);

	
	if (blocksRead < 0)
	{
		if (d->track->filemodhappy)
		{
			_af_error(AF_BAD_READ, "STR");
			d->track->filemodhappy = AF_FALSE;
		}
	}

	if (blocksRead < blockCount)
		blockCount = blocksRead;

	
	for (i=0; i<blockCount; i++)
	{
		bytesDecoded = ima_adpcm_decode_block(d,
			(uint8_t *) module->inc->buf + i * d->blockAlign,
			(int16_t *) module->outc->buf + i * d->samplesPerBlock);

		nframes += framesPerBlock;
	}

	d->track->nextfframe += nframes;

	if (blocksRead > 0)
		d->track->fpos_next_frame += blocksRead * d->blockAlign;

	assert(af_ftell(d->fh) == d->track->fpos_next_frame);

	

	if (d->track->totalfframes != -1 && nframes != frames2read)
	{
		
		if (d->track->filemodhappy)
		{
			_af_error(AF_BAD_READ,
				"STR",
				d->track->nextfframe,
				d->track->totalfframes);
			d->track->filemodhappy = AF_FALSE;
		}
	}

	module->outc->nframes = nframes;
}