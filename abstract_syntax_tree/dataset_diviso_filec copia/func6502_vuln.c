return_enc_padata(krb5_context context, krb5_data *req_pkt,
                  krb5_kdc_req *request, krb5_keyblock *reply_key,
                  krb5_db_entry *server, krb5_enc_kdc_rep_part *reply_encpart,
                  krb5_boolean is_referral)
{
    krb5_error_code code = 0;
    
    assert(reply_encpart->enc_padata == NULL);
    if (is_referral) {
        code = return_referral_enc_padata(context, reply_encpart, server);
        if (code)
            return code;
    }
    code = kdc_handle_protected_negotiation(context, req_pkt, request, reply_key,
                                            &reply_encpart->enc_padata);
    if (code)
        goto cleanup;
    
cleanup:
    return code;
}