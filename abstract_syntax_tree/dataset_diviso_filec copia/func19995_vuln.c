decode_sequence_of(const uint8_t *asn1, size_t len,
                   const struct atype_info *elemtype, void **seq_out,
                   size_t *count_out)
{
    krb5_error_code ret;
    void *seq = NULL, *elem, *newseq;
    const uint8_t *contents;
    size_t clen, count = 0;
    taginfo t;

    *seq_out = NULL;
    *count_out = 0;
    while (len > 0) {
        ret = get_tag(asn1, len, &t, &contents, &clen, &asn1, &len);
        if (ret)
            goto error;
        if (!check_atype_tag(elemtype, &t)) {
            ret = ASN1_BAD_ID;
            goto error;
        }
        newseq = realloc(seq, (count + 1) * elemtype->size);
        if (newseq == NULL) {
            ret = ENOMEM;
            goto error;
        }
        seq = newseq;
        elem = (char *)seq + count * elemtype->size;
        memset(elem, 0, elemtype->size);
        ret = decode_atype(&t, contents, clen, elemtype, elem);
        if (ret)
            goto error;
        count++;
    }
    *seq_out = seq;
    *count_out = count;
    return 0;

error:
    free_sequence_of(elemtype, seq, count);
    free(seq);
    return ret;
}