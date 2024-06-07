ipmi_sdr_print_sensor_eventonly(struct ipmi_intf *intf,
				struct sdr_record_eventonly_sensor *sensor)
{
	char desc[17];

	if (!sensor)
		return -1;

	memset(desc, 0, sizeof (desc));
	snprintf(desc, (sensor->id_code & 0x1f) + 1, "STR", sensor->id_string);

	if (verbose) {
		printf("STR",
		       sensor->id_code ? desc : "", sensor->keys.sensor_num);
		printf("STR",
		       sensor->entity.id, sensor->entity.instance,
		       val2str(sensor->entity.id, entity_id_vals));
		printf("STR",
			ipmi_get_sensor_type(intf, sensor->sensor_type),
			sensor->sensor_type);
		lprintf(LOG_DEBUG, "STR",
			sensor->event_type);
		printf("STR");
	} else {
		if (csv_output)
			printf("STR",
			       sensor->id_code ? desc : "",
			       sensor->keys.sensor_num,
			       sensor->entity.id, sensor->entity.instance);
		else if (sdr_extended)
			printf("STR",
			       sensor->id_code ? desc : "",
			       sensor->keys.sensor_num,
			       sensor->entity.id, sensor->entity.instance);
		else
			printf("STR",
			       sensor->id_code ? desc : "");
	}

	return 0;
}