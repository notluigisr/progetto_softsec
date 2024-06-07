static void snd_pcm_undo_start(struct snd_pcm_substream *substream,
			       snd_pcm_state_t state)
{
	if (substream->runtime->trigger_master == substream)
		substream->ops->trigger(substream, SNDRV_PCM_TRIGGER_STOP);
}