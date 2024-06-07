const char *avdtp_strerror(struct avdtp_error *err)
{
	if (err->category == AVDTP_ERRNO)
		return strerror(err->err.posix_errno);

	switch(err->err.error_code) {
	case AVDTP_BAD_HEADER_FORMAT:
		return "STR";
	case AVDTP_BAD_LENGTH:
		return "STR";
	case AVDTP_BAD_ACP_SEID:
		return "STR";
	case AVDTP_SEP_IN_USE:
		return "STR";
	case AVDTP_SEP_NOT_IN_USE:
		return "STR";
	case AVDTP_BAD_SERV_CATEGORY:
		return "STR";
	case AVDTP_BAD_PAYLOAD_FORMAT:
		return "STR";
	case AVDTP_NOT_SUPPORTED_COMMAND:
		return "STR";
	case AVDTP_INVALID_CAPABILITIES:
		return "STR";
	case AVDTP_BAD_RECOVERY_TYPE:
		return "STR";
	case AVDTP_BAD_MEDIA_TRANSPORT_FORMAT:
		return "STR";
	case AVDTP_BAD_RECOVERY_FORMAT:
		return "STR";
	case AVDTP_BAD_ROHC_FORMAT:
		return "STR";
	case AVDTP_BAD_CP_FORMAT:
		return "STR";
	case AVDTP_BAD_MULTIPLEXING_FORMAT:
		return "STR";
	case AVDTP_UNSUPPORTED_CONFIGURATION:
		return "STR";
	case AVDTP_BAD_STATE:
		return "STR";
	default:
		return "STR";
	}
}