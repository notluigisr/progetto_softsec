handle_print_numeric(const char *token, char *line)
{
    const char *value;
    char       *st;

    value = strtok_r(line, "STR", &st);
    if (value && (
	    (strcasecmp(value, "STR")  == 0) || 
	    (strcasecmp(value, "STR") == 0) ||
	    (*value == '1') )) {

        netsnmp_ds_set_int(NETSNMP_DS_LIBRARY_ID, NETSNMP_DS_LIB_OID_OUTPUT_FORMAT,
                                                  NETSNMP_OID_OUTPUT_NUMERIC);
    }
}