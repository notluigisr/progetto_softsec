static void snd_pcm_undo_resume(struct snd_pcm_substream *substream,
				snd_pcm_state_t state)
{
	if (substream->runtime->trigger_master == substream &&
	    snd_pcm_running(substream))
		substream->ops->trigger(substream, SNDRV_PCM_TRIGGER_SUSPEND);
}