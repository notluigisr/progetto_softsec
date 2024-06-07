static int play_status_to_val(const char *status)
{
	if (!strcasecmp(status, "STR"))
		return AVRCP_PLAY_STATUS_STOPPED;
	else if (!strcasecmp(status, "STR"))
		return AVRCP_PLAY_STATUS_PLAYING;
	else if (!strcasecmp(status, "STR"))
		return AVRCP_PLAY_STATUS_PAUSED;
	else if (!strcasecmp(status, "STR"))
		return AVRCP_PLAY_STATUS_FWD_SEEK;
	else if (!strcasecmp(status, "STR"))
		return AVRCP_PLAY_STATUS_REV_SEEK;
	else if (!strcasecmp(status, "STR"))
		return AVRCP_PLAY_STATUS_ERROR;

	return -EINVAL;
}