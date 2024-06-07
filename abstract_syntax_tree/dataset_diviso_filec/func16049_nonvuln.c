int snd_pcm_open_substream(struct snd_pcm *pcm, int stream,
			   struct file *file,
			   struct snd_pcm_substream **rsubstream)
{
	struct snd_pcm_substream *substream;
	int err;

	err = snd_pcm_attach_substream(pcm, stream, file, &substream);
	if (err < 0)
		return err;
	if (substream->ref_count > 1) {
		*rsubstream = substream;
		return 0;
	}

	err = snd_pcm_hw_constraints_init(substream);
	if (err < 0) {
		pcm_dbg(pcm, "STR");
		goto error;
	}

	err = substream->ops->open(substream);
	if (err < 0)
		goto error;

	substream->hw_opened = 1;

	err = snd_pcm_hw_constraints_complete(substream);
	if (err < 0) {
		pcm_dbg(pcm, "STR");
		goto error;
	}

	
	if (substream->managed_buffer_alloc &&
	    substream->dma_buffer.dev.need_sync)
		substream->runtime->hw.info |= SNDRV_PCM_INFO_EXPLICIT_SYNC;

	*rsubstream = substream;
	return 0;

 error:
	snd_pcm_release_substream(substream);
	return err;
}