sprint_realloc_float(u_char ** buf, size_t * buf_len,
                     size_t * out_len, int allow_realloc,
                     const netsnmp_variable_list * var,
                     const struct enum_list *enums,
                     const char *hint, const char *units)
{
    char *printf_format_string = NULL;

    if (var->type != ASN_OPAQUE_FLOAT) {
        if (!netsnmp_ds_get_boolean(
                NETSNMP_DS_LIBRARY_ID, NETSNMP_DS_LIB_QUICKE_PRINT)) {
            u_char          str[] = "STR";
            if (!snmp_strcat(buf, buf_len, out_len, allow_realloc, str))
                return 0;
        }
        return sprint_realloc_by_type(buf, buf_len, out_len,
                                          allow_realloc, var, NULL, NULL,
                                          NULL);
    }

    if (!netsnmp_ds_get_boolean(NETSNMP_DS_LIBRARY_ID, NETSNMP_DS_LIB_QUICK_PRINT)) {
        if (!snmp_cstrcat
            (buf, buf_len, out_len, allow_realloc, "STR")) {
            return 0;
        }
    }


    

    while ((*out_len + 128 + 1) >= *buf_len) {
        if (!(allow_realloc && snmp_realloc(buf, buf_len))) {
            return 0;
        }
    }

    printf_format_string = make_printf_format_string("STR");
    if (!printf_format_string) {
        return 0;
    }
    snprintf((char *)(*buf + *out_len), 128, printf_format_string, *var->val.floatVal);
    free(printf_format_string);
    *out_len += strlen((char *) (*buf + *out_len));

    if (units) {
        return (snmp_cstrcat(buf, buf_len, out_len, allow_realloc, "STR")
                && snmp_cstrcat(buf, buf_len, out_len, allow_realloc, units));
    }
    return 1;
}