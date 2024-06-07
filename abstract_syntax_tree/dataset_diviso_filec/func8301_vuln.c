midi_synth_load_patch(int dev, int format, const char __user *addr,
		      int offs, int count, int pmgr_flag)
{
	int             orig_dev = synth_devs[dev]->midi_dev;

	struct sysex_info sysex;
	int             i;
	unsigned long   left, src_offs, eox_seen = 0;
	int             first_byte = 1;
	int             hdr_size = (unsigned long) &sysex.data[0] - (unsigned long) &sysex;

	leave_sysex(dev);

	if (!prefix_cmd(orig_dev, 0xf0))
		return 0;

	if (format != SYSEX_PATCH)
	{

		  return -EINVAL;
	}
	if (count < hdr_size)
	{

		return -EINVAL;
	}
	count -= hdr_size;

	

	if(copy_from_user(&((char *) &sysex)[offs], &(addr)[offs], hdr_size - offs))
		return -EFAULT;
 
 	if (count < sysex.len)
	{

		sysex.len = count;
	}
  	left = sysex.len;
  	src_offs = 0;

	for (i = 0; i < left && !signal_pending(current); i++)
	{
		unsigned char   data;

		if (get_user(data,
		    (unsigned char __user *)(addr + hdr_size + i)))
			return -EFAULT;

		eox_seen = (i > 0 && data & 0x80);	

		if (eox_seen && data != 0xf7)
			data = 0xf7;

		if (i == 0)
		{
			if (data != 0xf0)
			{
				printk(KERN_WARNING "STR");
				return -EINVAL;
			}
		}
		while (!midi_devs[orig_dev]->outputc(orig_dev, (unsigned char) (data & 0xff)) &&
			!signal_pending(current))
			schedule();

		if (!first_byte && data & 0x80)
			return 0;
		first_byte = 0;
	}

	if (!eox_seen)
		midi_outc(orig_dev, 0xf7);
	return 0;
}