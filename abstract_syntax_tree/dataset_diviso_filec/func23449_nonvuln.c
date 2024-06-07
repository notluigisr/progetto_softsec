static void toneport_startup(struct usb_line6 *line6)
{
	line6_pcm_acquire(line6->line6pcm, LINE6_STREAM_MONITOR, true);
}