static int snd_pcm_mmap_control(struct snd_pcm_substream *substream, struct file *file,
				struct vm_area_struct *area)
{
	return -ENXIO;
}