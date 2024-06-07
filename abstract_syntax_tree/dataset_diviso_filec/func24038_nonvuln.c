static void cleanup_urbs(struct line6_pcm_stream *pcms, int iso_buffers)
{
	int i;

	
	if (pcms->urbs == NULL)
		return;

	for (i = 0; i < iso_buffers; i++) {
		if (pcms->urbs[i]) {
			usb_kill_urb(pcms->urbs[i]);
			usb_free_urb(pcms->urbs[i]);
		}
	}
	kfree(pcms->urbs);
	pcms->urbs = NULL;
}