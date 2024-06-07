static int pack_ber_group(enum response_types response_type,
                          const char *domain_name, const char *group_name,
                          gid_t gid, char **members, struct sss_nss_kv *kv_list,
                          struct berval **berval)
{
    BerElement *ber = NULL;
    int ret;
    size_t c;
    char *locat;
    char *short_group_name = NULL;

    short_group_name = strdup(group_name);
    if ((locat = strchr(short_group_name, SSSD_DOMAIN_SEPARATOR)) != NULL) {
        if (strcasecmp(locat+1, domain_name) == 0  ) {
            locat[0] = '\0';
        } else {
            ret = LDAP_NO_SUCH_OBJECT;
            goto done;
        }
    }

    ber = ber_alloc_t( LBER_USE_DER );
    if (ber == NULL) {
        ret = LDAP_OPERATIONS_ERROR;
        goto done;
    }

    ret = ber_printf(ber,"STR", response_type, domain_name, short_group_name,
                                   gid);
    if (ret == -1) {
        ret = LDAP_OPERATIONS_ERROR;
        goto done;
    }

    if (response_type == RESP_GROUP_MEMBERS) {
        ret = ber_printf(ber,"STR");
        if (ret == -1) {
            ret = LDAP_OPERATIONS_ERROR;
            goto done;
        }

        for (c = 0; members[c] != NULL; c++) {
            ret = ber_printf(ber, "STR", members[c]);
            if (ret == -1) {
                ret = LDAP_OPERATIONS_ERROR;
                goto done;
            }
        }

        ret = ber_printf(ber,"STR");
        if (ret == -1) {
            ret = LDAP_OPERATIONS_ERROR;
            goto done;
        }

        if (kv_list != NULL) {
            ret = add_kv_list(ber, kv_list);
            if (ret != LDAP_SUCCESS) {
                goto done;
            }
        }

    }

    ret = ber_printf(ber,"STR");
    if (ret == -1) {
        ret = LDAP_OPERATIONS_ERROR;
        goto done;
    }

    ret = ber_flatten(ber, berval);
    if (ret == -1) {
        ret = LDAP_OPERATIONS_ERROR;
        goto done;
    }

    ret = LDAP_SUCCESS;

done:
    free(short_group_name);
    ber_free(ber, 1);
    return ret;
}