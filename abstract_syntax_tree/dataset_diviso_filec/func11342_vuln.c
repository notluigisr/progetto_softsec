int ipmi_si_port_setup(struct si_sm_io *io)
{
	unsigned int addr = io->addr_data;
	int          idx;

	if (!addr)
		return -ENODEV;

	io->io_cleanup = port_cleanup;

	
	switch (io->regsize) {
	case 1:
		io->inputb = port_inb;
		io->outputb = port_outb;
		break;
	case 2:
		io->inputb = port_inw;
		io->outputb = port_outw;
		break;
	case 4:
		io->inputb = port_inl;
		io->outputb = port_outl;
		break;
	default:
		dev_warn(io->dev, "STR",
			 io->regsize);
		return -EINVAL;
	}

	
	for (idx = 0; idx < io->io_size; idx++) {
		if (request_region(addr + idx * io->regspacing,
				   io->regsize, DEVICE_NAME) == NULL) {
			
			while (idx--)
				release_region(addr + idx * io->regspacing,
					       io->regsize);
			return -EIO;
		}
	}
	return 0;
}