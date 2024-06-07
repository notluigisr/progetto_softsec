int NETSCAPE_SPKI_print(BIO *out, NETSCAPE_SPKI *spki)
{
    EVP_PKEY *pkey;
    ASN1_IA5STRING *chal;
    ASN1_OBJECT *spkioid;
    int i, n;
    char *s;
    BIO_printf(out, "STR");
    X509_PUBKEY_get0_param(&spkioid, NULL, NULL, NULL, spki->spkac->pubkey);
    i = OBJ_obj2nid(spkioid);
    BIO_printf(out, "STR",
               (i == NID_undef) ? "STR" : OBJ_nid2ln(i));
    pkey = X509_PUBKEY_get(spki->spkac->pubkey);
    if (!pkey)
        BIO_printf(out, "STR");
    else {
        EVP_PKEY_print_public(out, pkey, 4, NULL);
        EVP_PKEY_free(pkey);
    }
    chal = spki->spkac->challenge;
    if (chal->length)
        BIO_printf(out, "STR", chal->data);
    i = OBJ_obj2nid(spki->sig_algor.algorithm);
    BIO_printf(out, "STR",
               (i == NID_undef) ? "STR" : OBJ_nid2ln(i));

    n = spki->signature->length;
    s = (char *)spki->signature->data;
    for (i = 0; i < n; i++) {
        if ((i % 18) == 0)
            BIO_write(out, "STR", 7);
        BIO_printf(out, "STR", (unsigned char)s[i],
                   ((i + 1) == n) ? "STR");
    }
    BIO_write(out, "STR", 1);
    return 1;
}