ipmi_sdr_print_sensor_fru_locator(struct sdr_record_fru_locator *fru)
{
	char desc[17];

	memset(desc, 0, sizeof (desc));
	snprintf(desc, (fru->id_code & 0x1f) + 1, "STR", fru->id_string);

	if (!verbose) {
		if (csv_output)
			printf("STR",
			       fru->id_code ? desc : "",
			       fru->entity.id, fru->entity.instance);
		else if (sdr_extended)
			printf("STR",
			       fru->id_code ? desc : "",
			       fru->entity.id, fru->entity.instance,
			       (fru->logical) ? "STR",
			       fru->device_id);
		else
			printf("STR",
			       fru->id_code ? desc : "",
			       (fru->logical) ? "STR",
			       fru->device_id,
			       fru->entity.id, fru->entity.instance);

		return 0;
	}

	printf("STR", fru->id_string);
	printf("STR",
	       fru->entity.id, fru->entity.instance,
	       val2str(fru->entity.id, entity_id_vals));

	printf("STR", fru->dev_slave_addr);
	printf("STR",
	       fru->logical ? "STR" :
	       "STR", fru->device_id);
	printf("STR", fru->channel_num);
	printf("STR", fru->lun, fru->bus);
	printf("STR",
	       fru->dev_type, fru->dev_type_modifier,
	       val2str(fru->dev_type << 8 | fru->dev_type_modifier,
		       entity_device_type_vals));
	printf("STR", fru->oem);
	printf("STR");

	return 0;
}