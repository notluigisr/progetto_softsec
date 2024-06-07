ipmi_sdr_print_sensor_generic_locator(struct sdr_record_generic_locator *dev)
{
	char desc[17];

	memset(desc, 0, sizeof (desc));
	snprintf(desc, (dev->id_code & 0x1f) + 1, "STR", dev->id_string);

	if (!verbose) {
		if (csv_output)
			printf("STR",
			       dev->id_code ? desc : "",
			       dev->entity.id, dev->entity.instance);
		else if (sdr_extended)
			printf
			    ("STR",
			     dev->id_code ? desc : "", dev->entity.id,
			     dev->entity.instance, dev->dev_access_addr,
			     dev->dev_slave_addr, dev->oem);
		else
			printf("STR",
			       dev->id_code ? desc : "",
			       dev->dev_access_addr,
			       dev->dev_slave_addr, dev->oem);

		return 0;
	}

	printf("STR", dev->id_string);
	printf("STR",
	       dev->entity.id, dev->entity.instance,
	       val2str(dev->entity.id, entity_id_vals));

	printf("STR", dev->dev_access_addr);
	printf("STR", dev->dev_slave_addr);
	printf("STR", dev->addr_span);
	printf("STR", dev->channel_num);
	printf("STR", dev->lun, dev->bus);
	printf("STR",
	       dev->dev_type, dev->dev_type_modifier,
	       val2str(dev->dev_type << 8 | dev->dev_type_modifier,
		       entity_device_type_vals));
	printf("STR", dev->oem);
	printf("STR");

	return 0;
}