snd_seq_oss_reset(struct seq_oss_devinfo *dp)
{
	int i;

	
	for (i = 0; i < dp->max_synthdev; i++)
		snd_seq_oss_synth_reset(dp, i);

	
	if (dp->seq_mode != SNDRV_SEQ_OSS_MODE_MUSIC) {
		for (i = 0; i < dp->max_mididev; i++)
			snd_seq_oss_midi_reset(dp, i);
	}

	
	if (dp->readq)
		snd_seq_oss_readq_clear(dp->readq);
	if (dp->writeq)
		snd_seq_oss_writeq_clear(dp->writeq);

	
	snd_seq_oss_timer_stop(dp->timer);
}