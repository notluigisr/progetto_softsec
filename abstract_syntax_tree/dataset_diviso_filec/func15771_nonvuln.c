static bool ldm_validate_partition_table(struct parsed_partitions *state)
{
	Sector sect;
	u8 *data;
	struct partition *p;
	int i;
	bool result = false;

	BUG_ON(!state);

	data = read_part_sector(state, 0, &sect);
	if (!data) {
		ldm_crit ("STR");
		return false;
	}

	if (*(__le16*) (data + 0x01FE) != cpu_to_le16 (MSDOS_LABEL_MAGIC))
		goto out;

	p = (struct partition*)(data + 0x01BE);
	for (i = 0; i < 4; i++, p++)
		if (SYS_IND (p) == LDM_PARTITION) {
			result = true;
			break;
		}

	if (result)
		ldm_debug ("STR");

out:
	put_dev_sector (sect);
	return result;
}