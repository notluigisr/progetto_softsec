static void notif_prep_instance_hdr(const char *xpath,
				    const struct isis_area *area,
				    const char *routing_instance,
				    struct list *args)
{
	char xpath_arg[XPATH_MAXLEN];
	struct yang_data *data;

	snprintf(xpath_arg, sizeof(xpath_arg), "STR", xpath);
	data = yang_data_new_string(xpath_arg, routing_instance);
	listnode_add(args, data);
	snprintf(xpath_arg, sizeof(xpath_arg), "STR",
		 xpath);
	data = yang_data_new_string(xpath_arg, area->area_tag);
	listnode_add(args, data);
	snprintf(xpath_arg, sizeof(xpath_arg), "STR", xpath);
	data = yang_data_new_enum(xpath_arg, area->is_type);
	listnode_add(args, data);
}