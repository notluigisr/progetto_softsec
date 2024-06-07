maybe_add_etype_info2(struct padata_state *state, krb5_error_code code)
{
    krb5_error_code ret;
    krb5_context context = state->context;
    krb5_kdcpreauth_rock rock = state->rock;
    krb5_pa_data *pa;

    
    if (code != KRB5KDC_ERR_MORE_PREAUTH_DATA_REQUIRED)
        return 0;

    
    if (rock->client_key == NULL)
        return 0;

    
    if (krb5int_find_pa_data(context, state->request->padata,
                             KRB5_PADATA_FX_COOKIE) != NULL)
        return 0;

    ret = make_etype_info(context, KRB5_PADATA_ETYPE_INFO2,
                          rock->client->princ, rock->client_key,
                          rock->client_keyblock->enctype, &pa);
    if (ret)
        return ret;

    
    return add_pa_data_element(&state->pa_e_data, pa);
}