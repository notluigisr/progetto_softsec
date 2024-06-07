ldbm_config_exclude_from_export_set(void *arg,
                                    void *value,
                                    char *errorbuf __attribute__((unused)),
                                    int phase __attribute__((unused)),
                                    int apply)
{
    struct ldbminfo *li = (struct ldbminfo *)arg;

    if (apply) {
        if (NULL != li->li_attrs_to_exclude_from_export) {
            charray_free(li->li_attrs_to_exclude_from_export);
            li->li_attrs_to_exclude_from_export = NULL;
        }

        if (NULL != value) {
            char *dupvalue = slapi_ch_strdup(value);
            li->li_attrs_to_exclude_from_export = slapi_str2charray(dupvalue, "STR");
            slapi_ch_free((void **)&dupvalue);
        }
    }

    return LDAP_SUCCESS;
}