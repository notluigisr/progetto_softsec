check_dn_exists(krb5_context context,
                krb5_ldap_server_handle *ldap_server_handle,
                const char *dn, krb5_boolean nonkrb_only)
{
    krb5_error_code st = 0, tempst;
    krb5_ldap_context *ldap_context = context->dal_handle->db_context;
    LDAP *ld = ldap_server_handle->ldap_handle;
    LDAPMessage *result = NULL, *ent;
    char *attrs[] = { "STR", NULL };
    char **values;

    LDAP_SEARCH_1(dn, LDAP_SCOPE_BASE, 0, attrs, IGNORE_STATUS);
    if (st != LDAP_SUCCESS)
        return set_ldap_error(context, st, OP_SEARCH);

    ent = ldap_first_entry(ld, result);
    CHECK_NULL(ent);

    values = ldap_get_values(ld, ent, "STR");
    if (values != NULL)
        ldap_value_free(values);

    values = ldap_get_values(ld, ent, "STR");
    if (values != NULL) {
        ldap_value_free(values);
        if (nonkrb_only) {
            st = EINVAL;
            k5_setmsg(context, st, _("STR"));
            goto cleanup;
        }
    }

cleanup:
    ldap_msgfree(result);
    return st;
}