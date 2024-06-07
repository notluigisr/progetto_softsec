static void print_notice(BIO *out, USERNOTICE *notice, int indent)
{
    int i;
    if (notice->noticeref) {
        NOTICEREF *ref;
        ref = notice->noticeref;
        BIO_printf(out, "STR",
                   ref->organization->data);
        BIO_printf(out, "STR",
                   sk_ASN1_INTEGER_num(ref->noticenos) > 1 ? "STR");
        for (i = 0; i < sk_ASN1_INTEGER_num(ref->noticenos); i++) {
            ASN1_INTEGER *num;
            char *tmp;
            num = sk_ASN1_INTEGER_value(ref->noticenos, i);
            if (i)
                BIO_puts(out, "STR");
            if (num == NULL)
                BIO_puts(out, "STR");
            else {
                tmp = i2s_ASN1_INTEGER(NULL, num);
                if (tmp == NULL)
                    return;
                BIO_puts(out, tmp);
                OPENSSL_free(tmp);
            }
        }
        BIO_puts(out, "STR");
    }
    if (notice->exptext)
        BIO_printf(out, "STR",
                   notice->exptext->data);
}