static int snd_usb_pcm_prepare(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_usb_substream *subs = runtime->private_data;
	struct usb_host_interface *alts;
	struct usb_interface *iface;
	int ret;

	if (! subs->cur_audiofmt) {
		dev_err(&subs->dev->dev, "STR");
		return -ENXIO;
	}

	ret = snd_usb_lock_shutdown(subs->stream->chip);
	if (ret < 0)
		return ret;
	if (snd_BUG_ON(!subs->data_endpoint)) {
		ret = -EIO;
		goto unlock;
	}

	snd_usb_endpoint_sync_pending_stop(subs->sync_endpoint);
	snd_usb_endpoint_sync_pending_stop(subs->data_endpoint);

	ret = set_format(subs, subs->cur_audiofmt);
	if (ret < 0)
		goto unlock;

	iface = usb_ifnum_to_if(subs->dev, subs->cur_audiofmt->iface);
	alts = &iface->altsetting[subs->cur_audiofmt->altset_idx];
	ret = snd_usb_init_sample_rate(subs->stream->chip,
				       subs->cur_audiofmt->iface,
				       alts,
				       subs->cur_audiofmt,
				       subs->cur_rate);
	if (ret < 0)
		goto unlock;

	if (subs->need_setup_ep) {
		ret = configure_endpoint(subs);
		if (ret < 0)
			goto unlock;
		subs->need_setup_ep = false;
	}

	
	subs->data_endpoint->maxframesize =
		bytes_to_frames(runtime, subs->data_endpoint->maxpacksize);
	subs->data_endpoint->curframesize =
		bytes_to_frames(runtime, subs->data_endpoint->curpacksize);

	
	subs->hwptr_done = 0;
	subs->transfer_done = 0;
	subs->last_delay = 0;
	subs->last_frame_number = 0;
	runtime->delay = 0;

	
	if (subs->direction == SNDRV_PCM_STREAM_PLAYBACK)
		ret = start_endpoints(subs, true);

 unlock:
	snd_usb_unlock_shutdown(subs->stream->chip);
	return ret;
}