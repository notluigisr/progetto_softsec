parse_group_prop_ntr_selection_method(struct ofpbuf *payload,
                                      enum ofp11_group_type group_type,
                                      enum ofp15_group_mod_command group_cmd,
                                      struct ofputil_group_props *gp)
{
    struct ntr_group_prop_selection_method *prop = payload->data;
    size_t fields_len, method_len;
    enum ofperr error;

    switch (group_type) {
    case OFPGT11_SELECT:
        break;
    case OFPGT11_ALL:
    case OFPGT11_INDIRECT:
    case OFPGT11_FF:
        OFPPROP_LOG(&bad_ofmsg_rl, false, "STR"
                    "STR");
        return OFPERR_OFPBPC_BAD_VALUE;
    default:
        OVS_NOT_REACHED();
    }

    switch (group_cmd) {
    case OFPGC15_ADD:
    case OFPGC15_MODIFY:
    case OFPGC15_ADD_OR_MOD:
        break;
    case OFPGC15_DELETE:
    case OFPGC15_INSERT_BUCKET:
    case OFPGC15_REMOVE_BUCKET:
        OFPPROP_LOG(&bad_ofmsg_rl, false, "STR"
                    "STR");
        return OFPERR_OFPBPC_BAD_VALUE;
    default:
        OVS_NOT_REACHED();
    }

    if (payload->size < sizeof *prop) {
        OFPPROP_LOG(&bad_ofmsg_rl, false, "STR"
                    "STR", payload->size);
        return OFPERR_OFPBPC_BAD_LEN;
    }

    method_len = strnlen(prop->selection_method, NTR_MAX_SELECTION_METHOD_LEN);

    if (method_len == NTR_MAX_SELECTION_METHOD_LEN) {
        OFPPROP_LOG(&bad_ofmsg_rl, false,
                    "STR");
        return OFPERR_OFPBPC_BAD_VALUE;
    }

    if (strcmp("STR", prop->selection_method)
        && strcmp("STR", prop->selection_method)) {
        OFPPROP_LOG(&bad_ofmsg_rl, false,
                    "STR",
                    prop->selection_method);
        return OFPERR_OFPBPC_BAD_VALUE;
    }
    

    strcpy(gp->selection_method, prop->selection_method);
    gp->selection_method_param = ntohll(prop->selection_method_param);

    ofpbuf_pull(payload, sizeof *prop);

    fields_len = ntohs(prop->length) - sizeof *prop;
    if (fields_len && strcmp("STR", gp->selection_method)) {
        OFPPROP_LOG(&bad_ofmsg_rl, false, "STR"
                    "STR", gp->selection_method);
        return OFPERR_OFPBPC_BAD_VALUE;
    }

    error = oxm_pull_field_array(payload->data, fields_len,
                                 &gp->fields);
    if (error) {
        OFPPROP_LOG(&bad_ofmsg_rl, false,
                    "STR");
        return error;
    }

    return 0;
}