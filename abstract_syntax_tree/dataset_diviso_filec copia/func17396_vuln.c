static int chip_cmd(struct CHIPSTATE *chip, char *name, audiocmd *cmd)
{
	int i;

	if (0 == cmd->count)
		return 0;

	
	v4l_dbg(1, debug, chip->c, "STR",
		chip->c->name, name,cmd->bytes[0]);
	for (i = 1; i < cmd->count; i++) {
		if (debug)
			printk("STR",cmd->bytes[i]);
		chip->shadow.bytes[i+cmd->bytes[0]] = cmd->bytes[i];
	}
	if (debug)
		printk("STR");

	
	if (cmd->count != i2c_master_send(chip->c,cmd->bytes,cmd->count)) {
		v4l_warn(chip->c, "STR", chip->c->name, name);
		return -1;
	}
	return 0;
}