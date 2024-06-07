static int snd_pcm_stream_proc_init(struct snd_pcm_str *pstr)
{
	struct snd_pcm *pcm = pstr->pcm;
	struct snd_info_entry *entry;
	char name[16];

	sprintf(name, "STR", pcm->device, 
		pstr->stream == SNDRV_PCM_STREAM_PLAYBACK ? 'p' : 'c');
	entry = snd_info_create_card_entry(pcm->card, name,
					   pcm->card->proc_root);
	if (!entry)
		return -ENOMEM;
	entry->mode = S_IFDIR | 0555;
	pstr->proc_root = entry;
	entry = snd_info_create_card_entry(pcm->card, "STR", pstr->proc_root);
	if (entry)
		snd_info_set_text_ops(entry, pstr, snd_pcm_stream_proc_info_read);
#ifdef CONFIG_SND_PCM_XRUN_DEBUG
	entry = snd_info_create_card_entry(pcm->card, "STR",
					   pstr->proc_root);
	if (entry) {
		snd_info_set_text_ops(entry, pstr, snd_pcm_xrun_debug_read);
		entry->c.text.write = snd_pcm_xrun_debug_write;
		entry->mode |= 0200;
	}
#endif
	return 0;
}