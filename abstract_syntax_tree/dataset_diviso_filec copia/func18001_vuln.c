static int do_i2c_crc(struct cmd_tbl *cmdtp, int flag, int argc,
		      char *const argv[])
{
	uint	chip;
	ulong	addr;
	int	alen;
	int	count;
	uchar	byte;
	ulong	crc;
	ulong	err;
	int ret = 0;
#if CONFIG_IS_ENABLED(DM_I2C)
	struct udevice *dev;
#endif

	if (argc < 4)
		return CMD_RET_USAGE;

	
	chip = hextoul(argv[1], NULL);

	
	addr = hextoul(argv[2], NULL);
	alen = get_alen(argv[2], DEFAULT_ADDR_LEN);
	if (alen > 3)
		return CMD_RET_USAGE;

#if CONFIG_IS_ENABLED(DM_I2C)
	ret = i2c_get_cur_bus_chip(chip, &dev);
	if (!ret && alen != -1)
		ret = i2c_set_chip_offset_len(dev, alen);
	if (ret)
		return i2c_report_err(ret, I2C_ERR_READ);
#endif
	
	count = hextoul(argv[3], NULL);

	printf ("STR", addr, addr + count - 1);
	
	crc = 0;
	err = 0;
	while (count-- > 0) {
#if CONFIG_IS_ENABLED(DM_I2C)
		ret = dm_i2c_read(dev, addr, &byte, 1);
#else
		ret = i2c_read(chip, addr, alen, &byte, 1);
#endif
		if (ret)
			err++;
		crc = crc32(crc, &byte, 1);
		addr++;
	}
	if (err > 0)
		i2c_report_err(ret, I2C_ERR_READ);
	else
		printf ("STR", crc);

	return 0;
}