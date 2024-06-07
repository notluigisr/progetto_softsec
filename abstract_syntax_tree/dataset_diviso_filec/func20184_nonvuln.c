parse_DELETE_FIELD(char *arg, const struct ofpact_parse_params *pp)
{
    struct ofpact_delete_field *delete_field;

    delete_field = ofpact_put_DELETE_FIELD(pp->ofpacts);
    return mf_parse_field(&delete_field->field, arg);
}