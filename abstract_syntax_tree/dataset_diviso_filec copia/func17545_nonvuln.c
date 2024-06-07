fm_mgr_get_resp_error_str
(
	IN		fm_msg_ret_code_t err
)
{
	switch(err){
		case FM_RET_BAD_RET_LEN:
			return "STR";
		case FM_RET_OK:
			return "STR";
		case FM_RET_DT_NOT_SUPPORTED:
			return "STR";
		case FM_RET_ACT_NOT_SUPPORTED:
			return "STR";
		case FM_RET_INVALID:
			return "STR";
		case FM_RET_BAD_LEN:
			return "STR";
		case FM_RET_BUSY:
			return "STR";
		case FM_RET_NOT_FOUND:
			return "STR";
		case FM_RET_NO_NEXT:
			return "STR";
		case FM_RET_NOT_MASTER:
			return "STR";
		case FM_RET_NOSUCHOBJECT:
			return "STR";
		case FM_RET_NOSUCHINSTANCE:
			return "STR";
		case FM_RET_ENDOFMIBVIEW:
			return "STR";
		case FM_RET_ERR_NOERROR:
			return "STR";
		case FM_RET_ERR_TOOBIG:
			return "STR";
		case FM_RET_ERR_NOSUCHNAME:
			return "STR";
		case FM_RET_ERR_BADVALUE:
			return "STR";
		case FM_RET_ERR_READONLY:
			return "STR";
		case FM_RET_ERR_GENERR:
			return "STR";
		case FM_RET_ERR_NOACCESS:
			return "STR";
		case FM_RET_ERR_WRONGTYPE:
			return "STR";
		case FM_RET_ERR_WRONGLENGTH:
			return "STR";
		case FM_RET_ERR_WRONGENCODING:
			return "STR";
		case FM_RET_ERR_WRONGVALUE:
			return "STR";
		case FM_RET_ERR_NOCREATION:
			return "STR";
		case FM_RET_ERR_INCONSISTENTVALUE:
			return "STR";
		case FM_RET_ERR_RESOURCEUNAVAILABLE:
			return "STR";
		case FM_RET_ERR_COMMITFAILED:
			return "STR";
		case FM_RET_ERR_UNDOFAILED:
			return "STR";
		case FM_RET_ERR_AUTHORIZATIONERROR:
			return "STR";
		case FM_RET_ERR_NOTWRITABLE:
			return "STR";
		case FM_RET_TIMEOUT:
			return "STR";
		case FM_RET_UNKNOWN_DT:
			return "STR";
		case FM_RET_END_OF_TABLE:
			return "STR";
		case FM_RET_INTERNAL_ERR:
			return "STR";
		case FM_RET_CONX_CLOSED:
			return "STR";

	}

	return "STR";
}