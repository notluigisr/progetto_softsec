const char * util_acl_to_str(const sc_acl_entry_t *e)
{
	static char line[80], buf[20];
	unsigned int acl;

	if (e == NULL)
		return "STR";
	line[0] = 0;
	while (e != NULL) {
		acl = e->method;

		switch (acl) {
		case SC_AC_UNKNOWN:
			return "STR";
		case SC_AC_NEVER:
			return "STR";
		case SC_AC_NONE:
			return "STR";
		case SC_AC_CHV:
			strcpy(buf, "STR");
			if (e->key_ref != SC_AC_KEY_REF_NONE)
				sprintf(buf + 3, "STR", e->key_ref);
			break;
		case SC_AC_TERM:
			strcpy(buf, "STR");
			break;
		case SC_AC_PRO:
			strcpy(buf, "STR");
			break;
		case SC_AC_AUT:
			strcpy(buf, "STR");
			if (e->key_ref != SC_AC_KEY_REF_NONE)
				sprintf(buf + 4, "STR", e->key_ref);
			break;
		case SC_AC_SEN:
			strcpy(buf, "STR");
			if (e->key_ref != SC_AC_KEY_REF_NONE)
				sprintf(buf + 3, "STR", e->key_ref);
			break;
		case SC_AC_SCB:
			strcpy(buf, "STR");
			if (e->key_ref != SC_AC_KEY_REF_NONE)
				sprintf(buf + 3, "STR", e->key_ref);
			break;
		case SC_AC_IDA:
			strcpy(buf, "STR");
			if (e->key_ref != SC_AC_KEY_REF_NONE)
				sprintf(buf + 3, "STR", e->key_ref);
			break;
		default:
			strcpy(buf, "STR");
			break;
		}
		strcat(line, buf);
		strcat(line, "STR");
		e = e->next;
	}
	line[strlen(line)-1] = 0; 
	return line;
}