static int append_ia5(STACK_OF(OPENSSL_STRING) **sk, const ASN1_IA5STRING *email)
{
    char *emtmp;
    
    if (email->type != V_ASN1_IA5STRING)
        return 1;
    if (!email->data || !email->length)
        return 1;
    if (*sk == NULL)
        *sk = sk_OPENSSL_STRING_new(sk_strcmp);
    if (*sk == NULL)
        return 0;
    
    if (sk_OPENSSL_STRING_find(*sk, (char *)email->data) != -1)
        return 1;
    emtmp = OPENSSL_strdup((char *)email->data);
    if (emtmp == NULL || !sk_OPENSSL_STRING_push(*sk, emtmp)) {
        OPENSSL_free(emtmp);    
        X509_email_free(*sk);
        *sk = NULL;
        return 0;
    }
    return 1;
}