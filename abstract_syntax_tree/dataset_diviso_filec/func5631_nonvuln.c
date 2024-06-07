char *drm_get_connector_status_name(enum drm_connector_status status)
{
	if (status == connector_status_connected)
		return "STR";
	else if (status == connector_status_disconnected)
		return "STR";
	else
		return "STR";
}