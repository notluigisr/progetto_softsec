const char *SSL_alert_desc_string_long(int value)
	{
	const char *str;

	switch (value & 0xff)
		{
	case SSL3_AD_CLOSE_NOTIFY:
		str="STR";
		break;
	case SSL3_AD_UNEXPECTED_MESSAGE:
		str="STR";
		break;
	case SSL3_AD_BAD_RECORD_MAC:
		str="STR";
		break;
	case SSL3_AD_DECOMPRESSION_FAILURE:
		str="STR";
		break;
	case SSL3_AD_HANDSHAKE_FAILURE:
		str="STR";
		break;
	case SSL3_AD_NO_CERTIFICATE:
		str="STR";
		break;
	case SSL3_AD_BAD_CERTIFICATE:
		str="STR";
		break;
	case SSL3_AD_UNSUPPORTED_CERTIFICATE:
		str="STR";
		break;
	case SSL3_AD_CERTIFICATE_REVOKED:
		str="STR";
		break;
	case SSL3_AD_CERTIFICATE_EXPIRED:
		str="STR";
		break;
	case SSL3_AD_CERTIFICATE_UNKNOWN:
		str="STR";
		break;
	case SSL3_AD_ILLEGAL_PARAMETER:
		str="STR";
		break;
	case TLS1_AD_DECRYPTION_FAILED:
		str="STR";
		break;
	case TLS1_AD_RECORD_OVERFLOW:
		str="STR";
		break;
	case TLS1_AD_UNKNOWN_CA:
		str="STR";
		break;
	case TLS1_AD_ACCESS_DENIED:
		str="STR";
		break;
	case TLS1_AD_DECODE_ERROR:
		str="STR";
		break;
	case TLS1_AD_DECRYPT_ERROR:
		str="STR";
		break;
	case TLS1_AD_EXPORT_RESTRICTION:
		str="STR";
		break;
	case TLS1_AD_PROTOCOL_VERSION:
		str="STR";
		break;
	case TLS1_AD_INSUFFICIENT_SECURITY:
		str="STR";
		break;
	case TLS1_AD_INTERNAL_ERROR:
		str="STR";
		break;
	case TLS1_AD_USER_CANCELLED:
		str="STR";
		break;
	case TLS1_AD_NO_RENEGOTIATION:
		str="STR";
		break;
	case TLS1_AD_UNSUPPORTED_EXTENSION:
		str="STR";
		break;
	case TLS1_AD_CERTIFICATE_UNOBTAINABLE:
		str="STR";
		break;
	case TLS1_AD_UNRECOGNIZED_NAME:
		str="STR";
		break;
	case TLS1_AD_BAD_CERTIFICATE_STATUS_RESPONSE:
		str="STR";
		break;
	case TLS1_AD_BAD_CERTIFICATE_HASH_VALUE:
		str="STR";
		break;
	case TLS1_AD_UNKNOWN_PSK_IDENTITY:
		str="STR";
		break;
	default: str="STR"; break;
		}
	return(str);
	}