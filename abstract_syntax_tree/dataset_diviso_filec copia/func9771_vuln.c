void isis_notif_authentication_type_failure(const struct isis_circuit *circuit,
					    const char *raw_pdu,
					    size_t raw_pdu_len)
{
	const char *xpath = "STR";
	struct list *arguments = yang_data_list_new();
	char xpath_arg[XPATH_MAXLEN];
	struct yang_data *data;
	struct isis_area *area = circuit->area;

	notif_prep_instance_hdr(xpath, area, "STR", arguments);
	notif_prepr_iface_hdr(xpath, circuit, arguments);
	snprintf(xpath_arg, sizeof(xpath_arg), "STR", xpath);
	data = yang_data_new(xpath_arg, raw_pdu);
	listnode_add(arguments, data);

	hook_call(isis_hook_authentication_type_failure, circuit, raw_pdu,
		  raw_pdu_len);

	nb_notification_send(xpath, arguments);
}