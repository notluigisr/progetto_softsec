void snd_pcm_stream_unlock(struct snd_pcm_substream *substream)
{
	snd_pcm_group_unlock(&substream->self_group, substream->pcm->nonatomic);
}