static int snd_usb_playback_close(struct snd_pcm_substream *substream)
{
	return snd_usb_pcm_close(substream, SNDRV_PCM_STREAM_PLAYBACK);
}