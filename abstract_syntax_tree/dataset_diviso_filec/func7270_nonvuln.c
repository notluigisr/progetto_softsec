static void register_oss_dsp(struct snd_pcm *pcm, int index)
{
	if (snd_register_oss_device(SNDRV_OSS_DEVICE_TYPE_PCM,
				    pcm->card, index, &snd_pcm_oss_f_reg,
				    pcm) < 0) {
		pcm_err(pcm, "STR",
			   pcm->card->number, pcm->device);
	}
}