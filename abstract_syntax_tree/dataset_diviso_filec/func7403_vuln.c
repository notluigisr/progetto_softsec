kdc_process_s4u2proxy_req(kdc_realm_t *kdc_active_realm,
                          krb5_kdc_req *request,
                          const krb5_enc_tkt_part *t2enc,
                          const krb5_db_entry *server,
                          krb5_const_principal server_princ,
                          krb5_const_principal proxy_princ,
                          const char **status)
{
    krb5_error_code errcode;

    
    if (request->kdc_options & (NON_TGT_OPTION | KDC_OPT_ENC_TKT_IN_SKEY)) {
        return KRB5KDC_ERR_BADOPTION;
    }

    
    if (!krb5_principal_compare(kdc_context,
                                server->princ, 
                                server_princ)) {
        return KRB5KDC_ERR_SERVER_NOMATCH;
    }

    if (!isflagset(t2enc->flags, TKT_FLG_FORWARDABLE)) {
        *status = "STR";
        return KRB5_TKT_NOT_FORWARDABLE;
    }

    
    errcode = check_allowed_to_delegate_to(kdc_context,
                                           t2enc->client,
                                           server,
                                           proxy_princ);
    if (errcode) {
        *status = "STR";
        return errcode;
    }

    return 0;
}