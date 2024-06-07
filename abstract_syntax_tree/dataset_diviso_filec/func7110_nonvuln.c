static int hw_rule_channels(struct snd_pcm_hw_params *params,
			    struct snd_pcm_hw_rule *rule)
{
	struct snd_usb_substream *subs = rule->private;
	struct audioformat *fp;
	struct snd_interval *it = hw_param_interval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	unsigned int rmin, rmax;
	int changed;

	hwc_debug("STR", it->min, it->max);
	changed = 0;
	rmin = rmax = 0;
	list_for_each_entry(fp, &subs->fmt_list, list) {
		if (!hw_check_valid_format(subs, params, fp))
			continue;
		if (changed++) {
			if (rmin > fp->channels)
				rmin = fp->channels;
			if (rmax < fp->channels)
				rmax = fp->channels;
		} else {
			rmin = fp->channels;
			rmax = fp->channels;
		}
	}

	if (!changed) {
		hwc_debug("STR");
		it->empty = 1;
		return -EINVAL;
	}

	changed = 0;
	if (it->min < rmin) {
		it->min = rmin;
		it->openmin = 0;
		changed = 1;
	}
	if (it->max > rmax) {
		it->max = rmax;
		it->openmax = 0;
		changed = 1;
	}
	if (snd_interval_checkempty(it)) {
		it->empty = 1;
		return -EINVAL;
	}
	hwc_debug("STR", it->min, it->max, changed);
	return changed;
}