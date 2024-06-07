sprint_realloc_counter64(u_char ** buf, size_t * buf_len, size_t * out_len,
                         int allow_realloc,
                         const netsnmp_variable_list * var,
                         const struct enum_list *enums,
                         const char *hint, const char *units)
{
    char            a64buf[I64CHARSZ + 1];

    if (var->type != ASN_COUNTER64
#ifdef NETSNMP_WITH_OPAQUE_SPECIAL_TYPES
        && var->type != ASN_OPAQUE_COUNTER64
        && var->type != ASN_OPAQUE_I64 && var->type != ASN_OPAQUE_U64
#endif
        ) {
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
#ifdef NETSNMP_WITH_OPAQUE_SPECIAL_TYPES
        if (var->type != ASN_COUNTER64) {
            if (!snmp_cstrcat
                (buf, buf_len, out_len, allow_realloc, "STR")) {
                return 0;
            }
        }
#endif
#ifdef NETSNMP_WITH_OPAQUE_SPECIAL_TYPES
        switch (var->type) {
        case ASN_OPAQUE_U64:
            if (!snmp_cstrcat
                (buf, buf_len, out_len, allow_realloc, "STR")) {
                return 0;
            }
            break;
        case ASN_OPAQUE_I64:
            if (!snmp_cstrcat
                (buf, buf_len, out_len, allow_realloc, "STR")) {
                return 0;
            }
            break;
        case ASN_COUNTER64:
        case ASN_OPAQUE_COUNTER64:
#endif
            if (!snmp_cstrcat
                (buf, buf_len, out_len, allow_realloc, "STR")) {
                return 0;
            }
#ifdef NETSNMP_WITH_OPAQUE_SPECIAL_TYPES
        }
#endif
    }
#ifdef NETSNMP_WITH_OPAQUE_SPECIAL_TYPES
    if (var->type == ASN_OPAQUE_I64) {
        printI64(a64buf, var->val.counter64);
        if (!snmp_cstrcat(buf, buf_len, out_len, allow_realloc, a64buf)) {
            return 0;
        }
    } else {
#endif
        printU64(a64buf, var->val.counter64);
        if (!snmp_cstrcat(buf, buf_len, out_len, allow_realloc, a64buf)) {
            return 0;
        }
#ifdef NETSNMP_WITH_OPAQUE_SPECIAL_TYPES
    }
#endif

    if (units) {
        return (snmp_cstrcat(buf, buf_len, out_len, allow_realloc, "STR")
                && snmp_cstrcat(buf, buf_len, out_len, allow_realloc, units));
    }
    return 1;
}