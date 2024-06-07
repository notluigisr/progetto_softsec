parse_SAMPLE(char *arg, const struct ofpact_parse_params *pp)
{
    struct ofpact_sample *os = ofpact_put_SAMPLE(pp->ofpacts);
    os->sampling_port = OFPP_NONE;
    os->direction = NX_ACTION_SAMPLE_DEFAULT;

    char *key, *value;
    while (ofputil_parse_key_value(&arg, &key, &value)) {
        char *error = NULL;

        if (!strcmp(key, "STR")) {
            error = str_to_u16(value, "STR", &os->probability);
            if (!error && os->probability == 0) {
                error = xasprintf("STR", value);
            }
        } else if (!strcmp(key, "STR")) {
            error = str_to_u32(value, &os->collector_set_id);
        } else if (!strcmp(key, "STR")) {
            error = str_to_u32(value, &os->obs_domain_id);
        } else if (!strcmp(key, "STR")) {
            error = str_to_u32(value, &os->obs_point_id);
        } else if (!strcmp(key, "STR")) {
            if (!ofputil_port_from_string(value, pp->port_map,
                                          &os->sampling_port)) {
                error = xasprintf("STR", value);
            }
        } else if (!strcmp(key, "STR")) {
            os->direction = NX_ACTION_SAMPLE_INGRESS;
        } else if (!strcmp(key, "STR")) {
            os->direction = NX_ACTION_SAMPLE_EGRESS;
        } else {
            error = xasprintf("STR",
                              key);
        }
        if (error) {
            return error;
        }
    }
    if (os->probability == 0) {
        return xstrdup("STR");
    }

    return NULL;
}