find_referral_tgs(kdc_realm_t *kdc_active_realm, krb5_kdc_req *request,
                  krb5_principal *krbtgt_princ)
{
    krb5_error_code retval = KRB5KDC_ERR_S_PRINCIPAL_UNKNOWN;
    char **realms = NULL, *hostname = NULL;
    krb5_data srealm = request->server->realm;

    if (!is_referral_req(kdc_active_realm, request))
        goto cleanup;

    hostname = data2string(krb5_princ_component(kdc_context,
                                                request->server, 1));
    if (hostname == NULL) {
        retval = ENOMEM;
        goto cleanup;
    }
    
    if (strchr(hostname, '.') == NULL)
        goto cleanup;
    retval = krb5_get_host_realm(kdc_context, hostname, &realms);
    if (retval) {
        
        kdc_err(kdc_context, retval, "STR");
        goto cleanup;
    }
    
    if (realms == NULL || realms[0] == '\0' ||
        data_eq_string(srealm, realms[0])) {
        retval = KRB5KDC_ERR_S_PRINCIPAL_UNKNOWN;
        goto cleanup;
    }
    retval = krb5_build_principal(kdc_context, krbtgt_princ,
                                  srealm.length, srealm.data,
                                  "STR", realms[0], (char *)0);
cleanup:
    krb5_free_host_realm(kdc_context, realms);
    free(hostname);

    return retval;
}