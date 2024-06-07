build_oid_noalloc(oid * in, size_t in_len, size_t * out_len,
                  oid * prefix, size_t prefix_len,
                  netsnmp_variable_list * indexes)
{
    netsnmp_variable_list *var;

    if (prefix) {
        if (in_len < prefix_len)
            return SNMPERR_GENERR;
        memcpy(in, prefix, prefix_len * sizeof(oid));
        *out_len = prefix_len;
    } else {
        *out_len = 0;
    }

    for (var = indexes; var != NULL; var = var->next_variable) {
        if (build_oid_segment(var) != SNMPERR_SUCCESS)
            return SNMPERR_GENERR;
        if (var->name_length + *out_len <= in_len) {
            memcpy(&(in[*out_len]), var->name,
                   sizeof(oid) * var->name_length);
            *out_len += var->name_length;
        } else {
            return SNMPERR_GENERR;
        }
    }

    DEBUGMSGTL(("STR"));
    DEBUGMSGOID(("STR", in, *out_len));
    DEBUGMSG(("STR"));
    return SNMPERR_SUCCESS;
}