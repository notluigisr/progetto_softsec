ssize_t tpm_show_pubek(struct device *dev, struct device_attribute *attr,
		       char *buf)
{
	u8 *data;
	struct tpm_cmd_t tpm_cmd;
	ssize_t err;
	int i, rc;
	char *str = buf;

	struct tpm_chip *chip = dev_get_drvdata(dev);

	tpm_cmd.header.in = tpm_readpubek_header;
	err = transmit_cmd(chip, &tpm_cmd, READ_PUBEK_RESULT_SIZE,
			"STR");
	if (err)
		goto out;

	
	data = tpm_cmd.params.readpubek_out_buffer;
	str +=
	    sprintf(str,
		    "STR"
		    "STR"
		    "STR"
		    "STR",
		    data[10], data[11], data[12], data[13], data[14],
		    data[15], data[16], data[17], data[22], data[23],
		    data[24], data[25], data[26], data[27], data[28],
		    data[29], data[30], data[31], data[32], data[33],
		    be32_to_cpu(*((__be32 *) (data + 34))));

	for (i = 0; i < 256; i++) {
		str += sprintf(str, "STR", data[i + 38]);
		if ((i + 1) % 16 == 0)
			str += sprintf(str, "STR");
	}
out:
	rc = str - buf;
	return rc;
}