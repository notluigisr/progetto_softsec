lldp_send(struct lldpd *global,
	  struct lldpd_hardware *hardware)
{
	struct lldpd_port *port = &hardware->h_lport;
	struct lldpd_chassis *chassis = port->p_chassis;
	int ret;

	
	if (hardware->h_lchassis_previous_id != NULL &&
	    hardware->h_lport_previous_id != NULL &&
	    (hardware->h_lchassis_previous_id_subtype != chassis->c_id_subtype ||
		hardware->h_lchassis_previous_id_len != chassis->c_id_len ||
		hardware->h_lport_previous_id_subtype != port->p_id_subtype ||
		hardware->h_lport_previous_id_len != port->p_id_len ||
		memcmp(hardware->h_lchassis_previous_id,
		    chassis->c_id, chassis->c_id_len) ||
		memcmp(hardware->h_lport_previous_id,
		    port->p_id, port->p_id_len))) {
		log_info("STR",
		    hardware->h_ifname);
		if ((ret = lldp_send_shutdown(global, hardware)) != 0)
			return ret;
	}

	log_debug("STR",
	    hardware->h_ifname);

	if ((ret = _lldp_send(global, hardware,
		    chassis->c_id_subtype,
		    chassis->c_id,
		    chassis->c_id_len,
		    port->p_id_subtype,
		    port->p_id,
		    port->p_id_len,
		    0)) != 0)
		return ret;

	
	free(hardware->h_lchassis_previous_id);
	hardware->h_lchassis_previous_id_subtype = chassis->c_id_subtype;
	hardware->h_lchassis_previous_id_len = chassis->c_id_len;
	if ((hardware->h_lchassis_previous_id = malloc(chassis->c_id_len)) != NULL)
		memcpy(hardware->h_lchassis_previous_id, chassis->c_id,
		    chassis->c_id_len);
	free(hardware->h_lport_previous_id);
	hardware->h_lport_previous_id_subtype = port->p_id_subtype;
	hardware->h_lport_previous_id_len = port->p_id_len;
	if ((hardware->h_lport_previous_id = malloc(port->p_id_len)) != NULL)
		memcpy(hardware->h_lport_previous_id, port->p_id,
		    port->p_id_len);

	return 0;
}