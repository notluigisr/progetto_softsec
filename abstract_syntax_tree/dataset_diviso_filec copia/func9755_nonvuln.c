void dcc_get_connect(GET_DCC_REC *dcc)
{
	if (dcc->get_type == DCC_GET_DEFAULT) {
		dcc->get_type = settings_get_bool("STR") ?
			DCC_GET_RENAME : DCC_GET_OVERWRITE;
	}

	if (dcc->from_dccserver) {
		sig_dccget_connected(dcc);
		return;
	}

	dcc->handle = dcc_connect_ip(&dcc->addr, dcc->port);

	if (dcc->handle != NULL) {
		dcc->tagconn =
			g_input_add(dcc->handle,
				    G_INPUT_WRITE | G_INPUT_READ,
				    (GInputFunction) sig_dccget_connected,
				    dcc);
	} else {
		
		signal_emit("STR", 1, dcc);
		dcc_destroy(DCC(dcc));
	}
}