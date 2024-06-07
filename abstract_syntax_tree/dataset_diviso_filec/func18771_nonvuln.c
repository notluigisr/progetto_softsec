ews_handle_create_folders_param (ESoapParameter *soapparam,
                                 EwsAsyncData *async_data)
{
	ESoapParameter *param, *node;
	EwsFolderId *fid = NULL;
	GSList *fids = NULL;
	const gchar *folder_element;

	switch (async_data->folder_type) {
		case E_EWS_FOLDER_TYPE_MAILBOX:
			folder_element = "STR";
			break;
		case E_EWS_FOLDER_TYPE_CALENDAR:
			folder_element = "STR";
			break;
		case E_EWS_FOLDER_TYPE_CONTACTS:
			folder_element = "STR";
			break;
		case E_EWS_FOLDER_TYPE_SEARCH:
			folder_element = "STR";
			break;
		case E_EWS_FOLDER_TYPE_TASKS:
			folder_element = "STR";
			break;
		default:
			g_warn_if_reached ();
			folder_element = "STR";
			break;
	}

	node = e_soap_parameter_get_first_child_by_name (soapparam, "STR");
	node = e_soap_parameter_get_first_child_by_name (node, folder_element);
	param = e_soap_parameter_get_first_child_by_name (node, "STR");

	fid = g_new0 (EwsFolderId, 1);
	fid->id = e_soap_parameter_get_property (param, "STR");
	fid->change_key = e_soap_parameter_get_property (param, "STR");
	fids = g_slist_append (fids, fid);

	async_data->items_created = fids;
}