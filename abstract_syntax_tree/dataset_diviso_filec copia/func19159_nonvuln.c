encode_sequence_of(asn1buf *buf, size_t seqlen, const void *val,
                   const struct atype_info *eltinfo)
{
    krb5_error_code ret;
    size_t i;
    const void *eltptr;

    assert(eltinfo->size != 0);
    for (i = seqlen; i > 0; i--) {
        eltptr = (const char *)val + (i - 1) * eltinfo->size;
        ret = encode_atype_and_tag(buf, eltptr, eltinfo);
        if (ret)
            return ret;
    }
    return 0;
}