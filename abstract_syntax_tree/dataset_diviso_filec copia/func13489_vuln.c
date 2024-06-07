int X509_aux_print(BIO *out, X509 *x, int indent)
{
    char oidstr[80], first;
    STACK_OF(ASN1_OBJECT) *trust, *reject;
    const unsigned char *alias, *keyid;
    int keyidlen;
    int i;
    if (X509_trusted(x) == 0)
        return 1;
    trust = X509_get0_trust_objects(x);
    reject = X509_get0_reject_objects(x);
    if (trust) {
        first = 1;
        BIO_printf(out, "STR");
        for (i = 0; i < sk_ASN1_OBJECT_num(trust); i++) {
            if (!first)
                BIO_puts(out, "STR");
            else
                first = 0;
            OBJ_obj2txt(oidstr, sizeof(oidstr),
                        sk_ASN1_OBJECT_value(trust, i), 0);
            BIO_puts(out, oidstr);
        }
        BIO_puts(out, "STR");
    } else
        BIO_printf(out, "STR");
    if (reject) {
        first = 1;
        BIO_printf(out, "STR");
        for (i = 0; i < sk_ASN1_OBJECT_num(reject); i++) {
            if (!first)
                BIO_puts(out, "STR");
            else
                first = 0;
            OBJ_obj2txt(oidstr, sizeof(oidstr),
                        sk_ASN1_OBJECT_value(reject, i), 0);
            BIO_puts(out, oidstr);
        }
        BIO_puts(out, "STR");
    } else
        BIO_printf(out, "STR");
    alias = X509_alias_get0(x, NULL);
    if (alias)
        BIO_printf(out, "STR", alias);
    keyid = X509_keyid_get0(x, &keyidlen);
    if (keyid) {
        BIO_printf(out, "STR");
        for (i = 0; i < keyidlen; i++)
            BIO_printf(out, "STR", keyid[i]);
        BIO_write(out, "STR", 1);
    }
    return 1;
}