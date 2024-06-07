static int snd_pcm_hw_rule_sample_bits(struct snd_pcm_hw_params *params,
				       struct snd_pcm_hw_rule *rule)
{
	struct snd_interval t;
	snd_pcm_format_t k;

	t.min = UINT_MAX;
	t.max = 0;
	t.openmin = 0;
	t.openmax = 0;
	pcm_for_each_format(k) {
		int bits;
		if (!snd_mask_test_format(hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT), k))
			continue;
		bits = snd_pcm_format_physical_width(k);
		if (bits <= 0)
			continue; 
		if (t.min > (unsigned)bits)
			t.min = bits;
		if (t.max < (unsigned)bits)
			t.max = bits;
	}
	t.integer = 1;
	return snd_interval_refine(hw_param_interval(params, rule->var), &t);
}